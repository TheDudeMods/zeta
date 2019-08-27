#include <datatypes/data_array.h>
#include <memory/memory_interface.h>

/* ---------- code */

uint data_allocation_size(
	long maximum_count,
	uint size,
	long alignment_bits)
{
	assert(maximum_count >= 0 && maximum_count <= k_uint16_max);
	assert(size >= sizeof(s_datum_header));
	assert(alignment_bits >= 0);
	assert(size == align_address(size, alignment_bits));

	uint alignment = alignment_bits ? (1 << (uint)alignment_bits) - 1 : 0;

	return sizeof(s_data_array) + alignment
		+ BIT_VECTOR_SIZE_IN_BYTES((ulonglong)maximum_count)
		+ ((ulonglong)maximum_count * size);
}

bool data_is_empty(
	s_data_array *data)
{
	assert(data);
	assert(data->valid);

	return data->first_unallocated == 0;
}

bool data_is_full(
	s_data_array *data)
{
	assert(data);
	assert(data->valid);

	return (data->maximum_count - data->first_unallocated) == 0;
}

bool data_should_verify_data_pattern(
	s_data_array *data)
{
	assert(data);

	return data->flags.test(_data_array_verify_data_pattern_bit);
}

s_data_array *data_new(
	char const *name,
	long maximum_count,
	uint size,
	long alignment_bits,
	char const *file,
	long line,
	c_allocation_interface *allocation)
{
	assert(name);
	assert(file);
	assert(allocation);

	uint allocation_size = data_allocation_size(maximum_count, size, alignment_bits);
	s_data_array *data = (s_data_array *)allocation->allocate(allocation_size, file, line);

	assert(data);

	data_initialize(data, name, maximum_count, size, alignment_bits, allocation);

	return data;
}

s_data_array *data_new_disconnected(
	char const *name,
	long maximum_count,
	uint size,
	long alignment_bits,
	char const *file,
	long line,
	c_allocation_interface *allocation)
{
	assert(name);
	assert(file);
	assert(allocation);

	uint allocation_size = data_allocation_size(maximum_count, size, alignment_bits);
	s_data_array *data = (s_data_array *)allocation->allocate(allocation_size, file, line);

	assert(data);

	ulong *in_use_bit_vector = reinterpret_cast<ulong *>(offset_pointer(data, sizeof(s_data_array)));
	data_initialize_disconnected(data, name, maximum_count, size, alignment_bits, allocation, in_use_bit_vector);

	return data;
}

void data_initialize(
	s_data_array *data,
	char const *name,
	long maximum_count,
	uint size,
	long alignment_bits,
	c_allocation_interface *allocation)
{
	assert(data);
	assert(name);
	assert(maximum_count >= 0 && maximum_count <= k_uint16_max);
	assert(size > 0);
	assert(alignment_bits >= 0 && alignment_bits <= k_int8_max);
	assert(size == align_address(size, alignment_bits));
	assert(allocation);

	void *base_address = align_pointer(data + 1, alignment_bits);
	ulong *in_use_bit_vector = reinterpret_cast<ulong *>(offset_pointer(base_address, maximum_count * size));

	data_initialize_disconnected(data, name, maximum_count, size, alignment_bits, allocation, in_use_bit_vector);

	data->data = base_address;
	data->offset_to_data = pointer_distance(data, base_address);

	data->flags.set(_data_array_can_disconnect_bit, false);
	data->flags.set(_data_array_disconnected_bit, false);

	csmemset(data->in_use_bit_vector, 0, BIT_VECTOR_SIZE_IN_BYTES((ulonglong)maximum_count * size));
}

void data_initialize_disconnected(
	s_data_array *data,
	char const *name,
	long maximum_count,
	uint size,
	long alignment_bits,
	c_allocation_interface *allocation,
	ulong *in_use_bit_vector)
{
	assert(data);
	assert(name);
	assert(maximum_count >= 0 && maximum_count <= k_uint16_max);
	assert(size > 0);
	assert(alignment_bits >= 0 && alignment_bits <= k_int8_max);
	assert(size == align_address(size, alignment_bits));
	assert(allocation);
	assert(in_use_bit_vector);

	csmemset(data, 0, sizeof(s_data_array));

	data->name.set(name);
	data->maximum_count = maximum_count;
	data->size = size;
	data->alignment_bits = (uchar)alignment_bits;
	data->signature = k_data_signature;
	data->data = nullptr;
	data->offset_to_data = 0;
	data->valid = false;
	data->in_use_bit_vector = in_use_bit_vector;
	data->offset_to_bit_vector = (long)pointer_distance(data, in_use_bit_vector);
	data->allocation = allocation;
	data->flags.set(_data_array_can_disconnect_bit, true);
	data->flags.set(_data_array_disconnected_bit, true);
	data->flags.set(_data_array_verify_data_pattern_bit, true);
}

void data_dispose(
	s_data_array *data,
	char const *file,
	long line)
{
	assert(data);
	assert(data->allocation);

	data_verify(data);

	csmemset(data, 0, sizeof(s_data_array));

	data->allocation->deallocate(data, file, line);
}

long data_get_count(
	s_data_array *data)
{
	assert(data);
	assert(data->valid);

	return data->actual_count;
}

long data_get_watermark(
	s_data_array *data)
{
	assert(data);
	assert(data->valid);

	return data->first_unallocated;
}

long data_last_index(
	s_data_array *data)
{
	assert(data);
	assert(data->valid);

	long result = NONE;

	while (true)
	{
		long next_index = data_next_index(data, result);

		if (next_index == NONE)
			break;

		result = next_index;
	}

	return result;
}

long data_next_index(
	s_data_array *data,
	long index)
{
	assert(data);
	assert(data->valid);

	long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index + 1);
	long next_absolute_index = data_next_absolute_index(data, absolute_index);
	long next_index = datum_absolute_index_to_index(data, next_absolute_index);

	return next_index;
}

long data_next_absolute_index(
	s_data_array *data,
	long index)
{
	assert(data);
	assert(data->valid);

	data_verify(data);

	long first_unallocated = data->first_unallocated;
	ulong *in_use_bit_vector = data->in_use_bit_vector;

	if (index > NONE && index < first_unallocated)
		for (long i = index + 1; i < first_unallocated; i++)
			if (BIT_VECTOR_TEST_FLAG(in_use_bit_vector, i))
				return i;

	return NONE;
}

long data_previous_index(
	s_data_array *data,
	long index)
{
	assert(data);
	assert(data->valid);

	ulong *in_use_bit_vector = data->in_use_bit_vector;
	ulong datum_size = data->size;
	void *datums = data->data;

	if (index <= 0)
		return NONE;

	for (long i = index; i > 0; i--)
	{
		s_datum_header *datum = reinterpret_cast<s_datum_header *>(
			offset_pointer(datums, (i - 1) * datum_size));

		if (datum->identifier)
			return datum_absolute_index_to_index(data, i);
	}

	return NONE;
}

ushort data_make_first_identifier(
	s_data_array *data)
{
	assert(data);

	char const *name = data->name.get_string();

	return (ushort)name[0] | ((ushort)name[1] << 8) | (ushort)k_int16_min;
}

void data_connect(
	s_data_array *data,
	long maximum_count,
	void *datums)
{
	assert(data);
	assert(TEST_BIT(data->flags, _data_array_disconnected_bit));
	assert(datums);
	assert(datums == align_pointer(datums, data->alignment_bits));
	assert(data->offset_to_bit_vector != 0);
	assert(data->in_use_bit_vector != nullptr);

	data->flags.set(_data_array_disconnected_bit, false);
	data->maximum_count = maximum_count;
	data->offset_to_data = (long)pointer_distance(data, datums);
	data->data = datums;
	data->valid = true;
	data->first_unallocated = 0;
	data->actual_count = 0;
	data->next_index = maximum_count;

	ushort next_identifier = data_make_first_identifier(data);
	data->next_identifier = next_identifier;
	data->isolated_next_identifier = ~next_identifier | (ushort)k_int16_min;

	long datum_size = data->size;
	bool should_verify = data_should_verify_data_pattern(data);

	ulong *in_use_bit_vector = data->in_use_bit_vector;

	for (long i = 0; i < maximum_count; i++)
	{
		s_datum_header *datum = reinterpret_cast<s_datum_header *>(
			offset_pointer(datums, i * datum_size));

		if (should_verify && !datum->identifier)
		{
			if (datum_size > 32)
			{
				csmemset(datum, 0xBA, datum_size);
			}
			else
			{
				if (!pointer_is_aligned(datum, 2) || datum_size & 3)
				{
					csmemset(datum, 0xBA, datum_size);
				}
				else
				{
					for (int x = 0; x < datum_size / sizeof(ulong); x++)
						*reinterpret_cast<ulong *>(offset_pointer(datum, x * sizeof(ulong))) = 0xBABABABA;
				}
			}
		}
		
		if (!datum->identifier)
		{
			BIT_VECTOR_SET_FLAG(in_use_bit_vector, i, false);

			if (i < data->next_index)
				data->next_index = i;
		}
		else
		{
			BIT_VECTOR_SET_FLAG(in_use_bit_vector, i, true);

			data->first_unallocated = i + 1;
			data->actual_count++;
		}
	}
}

void data_disconnect(
	s_data_array *data)
{
	assert(data);
	assert(!TEST_BIT(data->flags, _data_array_disconnected_bit));
	assert(TEST_BIT(data->flags, _data_array_can_disconnect_bit));

	data->flags.set(_data_array_disconnected_bit, true);
	data->data = nullptr;
	data->offset_to_data = 0;
	data->valid = false;
}

void data_delete_all(
	s_data_array *data)
{
	assert(data);
	assert(data->offset_to_bit_vector);

	data->first_unallocated = 0;
	data->actual_count = 0;
	data->next_index = 0;

	ushort next_identifier = data_make_first_identifier(data);
	data->next_identifier = next_identifier;
	data->isolated_next_identifier = ~next_identifier | (ushort)k_int16_min;

	assert(data->next_identifier < (ushort)k_int16_min);
	assert(data->isolated_next_identifier < (ushort)k_int16_min);

	if (data_should_verify_data_pattern(data))
	{
		uint total_size = data->maximum_count * data->size;

		if (total_size > 32)
		{
			csmemset(data, 0xBA, total_size);
		}
		else
		{
			if (!pointer_is_aligned(data, 2) || total_size & 3)
			{
				csmemset(data, 0xBA, total_size);
			}
			else
			{
				for (int x = 0; x < total_size / sizeof(ulong); x++)
					*reinterpret_cast<ulong *>(offset_pointer(data, x * sizeof(ulong))) = 0xBABABABA;
			}
		}
	}

	uint datum_size = data->size;

	for (long i = 0; i < data->maximum_count; i++)
	{
		s_datum_header *datum = reinterpret_cast<s_datum_header *>(
			offset_pointer(data->data, i * datum_size));

		datum->identifier = 0;
	}

	csmemset(data->in_use_bit_vector, 0, BIT_VECTOR_SIZE_IN_BYTES(data->maximum_count));

	data_verify(data);
}

void data_verify(
	s_data_array *data)
{
	static char temporary[256];

	vassert(data
		&& (data->signature == k_data_signature)
		&& (data->maximum_count >= 0)
		&& (data->first_unallocated >= 0)
		&& (data->maximum_count >= data->first_unallocated)
		&& (data->next_index >= 0)
		&& (data->maximum_count >= data->next_index)
		&& (data->actual_count >= 0)
		&& (data->first_unallocated >= data->actual_count)
		&& !data->flags.test(_data_array_disconnected_bit)
		&& (data->offset_to_data != 0)
		&& (data->offset_to_bit_vector != 0),
		csnzprintf(temporary, 256, "%s data array @%p is bad or not allocated", data->name, data));
}

void data_make_valid(
	s_data_array *data)
{
	assert(data);

	data->valid = true;
	data_delete_all(data);
	data_verify(data);
}

void data_make_invalid(
	s_data_array *data)
{
	assert(data);

	data_verify(data);
	data->valid = false;
}

void data_set_new_base_address(
	s_data_array **source,
	s_data_array *destination)
{
	assert(source && destination);

	if (destination != nullptr)
	{
		if (destination->offset_to_data == 0)
		{
			destination->data = (void *)0x0;
		}
		else
		{
			void *data = offset_pointer(destination, destination->offset_to_data);

			if (destination->data != data)
				destination->data = data;
		}

		if (destination->offset_to_bit_vector == 0)
		{
			destination->in_use_bit_vector = nullptr;
		}
		else
		{
			ulong *in_use_bit_vector = reinterpret_cast<ulong *>(offset_pointer(destination, destination->offset_to_bit_vector));

			if (destination->in_use_bit_vector != in_use_bit_vector)
				destination->in_use_bit_vector = in_use_bit_vector;
		}
	}

	*source = destination;
}

void data_iterator_begin(
	s_data_iterator *iterator,
	s_data_array *data)
{
	assert(iterator);
	assert(data);
	assert(data->valid);

	data_verify(data);

	iterator->data = data;
	iterator->index = NONE;
	iterator->next_index = NONE;
	iterator->signature = reinterpret_cast<ulong>(data) ^ k_data_iterator_signature;
}

void *data_iterator_next(
	s_data_iterator *iterator)
{
	static char temporary[256];

	assert(iterator);

	s_data_array *data = iterator->data;

	assert(data);
	assert(data->valid);

	vassert(iterator->signature == (reinterpret_cast<ulong>(data) ^ k_data_iterator_signature),
		csnzprintf(temporary, 256, "uninitialized iterator passed to %s", __FUNCTION__));

	data_verify(data);

	long absolute_index = data_next_absolute_index(data, iterator->index + 1);
	long datum_index = NONE;
	s_datum_header *result = nullptr;

	if (absolute_index == NONE)
	{
		iterator->index = data->maximum_count;
		iterator->next_index = NONE;
	}
	else
	{
		result = reinterpret_cast<s_datum_header *>(
			offset_pointer(data->data, absolute_index * data->size));
		iterator->index = absolute_index;
		datum_index = BUILD_DATUM_INDEX(result->identifier, absolute_index);
	}

	assert((result == nullptr && iterator->index == NONE)
		|| (result != nullptr && iterator->index != NONE));

	return result;
}

bool datum_available_at_index(
	s_data_array *data,
	long index)
{
	assert(data);
	assert(data->valid);

	data_verify(data);

	ushort absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
	ushort identifier = DATUM_INDEX_TO_IDENTIFIER(index);

	assert(identifier != 0);

	if (absolute_index > NONE && absolute_index < data->maximum_count)
	{
		s_datum_header *datum = reinterpret_cast<s_datum_header *>(
			offset_pointer(data->data, absolute_index * data->size));

		return datum->identifier != 0;
	}

	return false;
}

long datum_absolute_index_to_index(
	s_data_array *data,
	long index)
{
	assert(data);

	if (index == NONE)
		return NONE;

	s_datum_header *datum = reinterpret_cast<s_datum_header *>(
		datum_get_absolute(data, index));

	return BUILD_DATUM_INDEX(datum->identifier, index);
}

long datum_new(
	s_data_array *data)
{
	assert(data);
	assert(!TEST_BIT(data->flags, _data_array_disconnected_bit));
	assert(data->offset_to_data != 0);
	assert(data->data != nullptr);
	assert(data->valid);

	data_verify(data);

	long maximum_count = data->maximum_count;
	long datum_size = data->size;
	long next_index = data->next_index;
	long datum_index = NONE;
	long absolute_index = NONE;

	ulong *in_use_bit_vector = data->in_use_bit_vector;

	do
	{
		if (absolute_index > data->first_unallocated)
		{
		$datum_new_start:
			if ((absolute_index == NONE) && (data->first_unallocated < data->maximum_count))
				absolute_index = data->first_unallocated;

			if (absolute_index != NONE)
			{
				s_datum_header *datum = reinterpret_cast<s_datum_header *>(
					offset_pointer(data->data, absolute_index * datum_size));
				
				assert(datum->identifier == 0);

				BIT_VECTOR_SET_FLAG(in_use_bit_vector, absolute_index, true);

				data->actual_count++;
				data->next_index = absolute_index + 1;

				if (data->first_unallocated <= absolute_index)
					data->first_unallocated = absolute_index + 1;

				datum_initialize(data, datum, &data->next_identifier);
				
				datum_index = BUILD_DATUM_INDEX(datum->identifier, absolute_index);
			}

			if (datum_index != NONE)
				datum_get(data, datum_index);

			return datum_index;
		}

		if (!BIT_VECTOR_TEST_FLAG(in_use_bit_vector, next_index))
		{
			absolute_index = next_index;
			goto $datum_new_start;
		}

		next_index++;
	} while (true);
}

long datum_new_at_index(
	s_data_array *data,
	long requested_index)
{
	assert(data);
	assert(data->valid);

	data_verify(data);

	ushort absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(requested_index);
	ushort identifier = DATUM_INDEX_TO_IDENTIFIER(requested_index);

	assert(identifier != 0);

	long index = NONE;

	if (absolute_index > NONE && absolute_index < data->maximum_count)
	{
		s_datum_header *datum = reinterpret_cast<s_datum_header *>(
			offset_pointer(data->data, absolute_index * data->size));

		if (datum->identifier == 0)
		{
			BIT_VECTOR_SET_FLAG(data->in_use_bit_vector, absolute_index, true);
			data->actual_count++;

			if (data->first_unallocated <= absolute_index)
				data->first_unallocated = absolute_index + 1;

			datum_initialize(data, datum, &data->next_identifier);

			index = BUILD_DATUM_INDEX(datum->identifier, absolute_index);
		}
	}

	assert(index == NONE || index == requested_index);

	return index;
}

long datum_new_at_absolute_index(
	s_data_array *data,
	long absolute_index)
{
	assert(data);
	assert(data->valid);

	data_verify(data);

	assert(DATUM_INDEX_TO_ABSOLUTE_INDEX(absolute_index) == absolute_index);
	assert(DATUM_INDEX_TO_IDENTIFIER(absolute_index) == 0);

	long index = NONE;

	if (absolute_index > NONE && absolute_index < data->maximum_count)
	{
		s_datum_header *datum = reinterpret_cast<s_datum_header *>(
			offset_pointer(data->data, absolute_index * data->size));

		if (datum->identifier == 0)
		{
			BIT_VECTOR_SET_FLAG(data->in_use_bit_vector, absolute_index, true);
			data->actual_count++;

			if (data->first_unallocated <= absolute_index)
				data->first_unallocated = absolute_index + 1;

			datum_initialize(data, datum, &data->next_identifier);

			index = BUILD_DATUM_INDEX(datum->identifier, absolute_index);
		}
	}

	assert(index == NONE || DATUM_INDEX_TO_ABSOLUTE_INDEX(index) == absolute_index);

	return index;
}

long datum_new_in_range(
	s_data_array *data,
	long minimum_index,
	long count_indices,
	e_datum_salt salt_type)
{
	assert(data);
	assert(!TEST_BIT(data->flags, _data_array_disconnected_bit));
	assert(data->offset_to_data != 0);
	assert(VALID_INDEX(salt_type, k_datum_salt_count));
	assert(data->valid);
	assert(minimum_index + count_indices <= data->maximum_count);

	ulong *in_use_bit_vector = data->in_use_bit_vector;
	
	long next_index = minimum_index;

	long last_index = (minimum_index + count_indices < data->first_unallocated) ?
		minimum_index + count_indices :
		data->first_unallocated;

	long absolute_index = NONE;
	long datum_index = NONE;

	do
	{
		if (last_index <= next_index)
		{
		$datum_new_start:
			if (absolute_index == NONE && next_index < minimum_index + count_indices)
				absolute_index = next_index;

			if (absolute_index != NONE)
			{
				s_datum_header *datum = reinterpret_cast<s_datum_header *>(
					offset_pointer(data->data, absolute_index * data->size));

				BIT_VECTOR_SET_FLAG(in_use_bit_vector, absolute_index, true);
				data->actual_count++;

				if (data->first_unallocated <= absolute_index)
					data->first_unallocated = absolute_index + 1;

				assert(datum->identifier == 0);

				ushort *salt = (salt_type == _datum_salt_isolated_identifier) ?
					&data->next_identifier :
					&data->isolated_next_identifier;

				datum_initialize(data, datum, salt);
				
				datum_index = BUILD_DATUM_INDEX(datum->identifier, absolute_index);
			}

			if (datum_index != NONE)
				datum_get(data, datum_index);

			return datum_index;
		}

		if (!BIT_VECTOR_TEST_FLAG(in_use_bit_vector, next_index))
		{
			absolute_index = next_index;
			goto $datum_new_start;
		}

		next_index++;
	} while (true);
}

void datum_initialize(
	s_data_array *data,
	s_datum_header *datum,
	ushort *out_identifier)
{
	//
	// TODO
	//
}
