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

	auto alignment = alignment_bits ? (1 << alignment_bits) - 1 : 0;

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

	auto allocation_size = data_allocation_size(maximum_count, size, alignment_bits);
	auto data = reinterpret_cast<s_data_array *>(allocation->allocate(allocation_size, file, line));

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

	auto allocation_size = data_allocation_size(maximum_count, size, alignment_bits);
	auto data = reinterpret_cast<s_data_array *>(allocation->allocate(allocation_size, file, line));

	assert(data);

	auto in_use_bit_vector = reinterpret_cast<ulong *>(offset_pointer(data, sizeof(s_data_array)));
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

	auto base_address = align_pointer(data + 1, alignment_bits);
	auto in_use_bit_vector = reinterpret_cast<ulong *>(offset_pointer(base_address, maximum_count * size));

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

	auto result = static_cast<long>(NONE);

	while (true)
	{
		auto next_index = data_next_index(data, result);

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

	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index + 1);
	auto next_absolute_index = data_next_absolute_index(data, absolute_index);
	auto next_index = datum_absolute_index_to_index(data, next_absolute_index);

	return next_index;
}

long data_next_absolute_index(
	s_data_array *data,
	long index)
{
	assert(data);
	assert(data->valid);

	data_verify(data);

	auto first_unallocated = data->first_unallocated;
	auto in_use_bit_vector = data->in_use_bit_vector;

	if (index > NONE && index < first_unallocated)
		for (auto i = index + 1; i < first_unallocated; i++)
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

	auto in_use_bit_vector = data->in_use_bit_vector;
	auto datum_size = data->size;
	auto datums = data->data;

	if (index <= 0)
		return NONE;

	for (auto i = index; i > 0; i--)
	{
		auto datum = reinterpret_cast<s_datum_header *>(
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

	auto name = data->name.get_string();

	return (ushort)name[0] | ((ushort)name[1] << 8) | k_datum_base_identifier;
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

	auto next_identifier = data_make_first_identifier(data);
	data->next_identifier = next_identifier;
	data->isolated_next_identifier = ~next_identifier | k_datum_base_identifier;

	auto datum_size = data->size;
	auto in_use_bit_vector = data->in_use_bit_vector;
	auto should_verify = data_should_verify_data_pattern(data);

	for (auto i = 0; i < maximum_count; i++)
	{
		auto datum = reinterpret_cast<s_datum_header *>(
			offset_pointer(datums, i * datum_size));

		if (should_verify && !datum->identifier)
		{
			if (datum_size > 32 || !pointer_is_aligned(datum, 2) || datum_size & 3)
			{
				csmemset(datum, 0xBA, datum_size);
			}
			else
			{
				for (int x = 0; x < datum_size / sizeof(ulong); x++)
					*reinterpret_cast<ulong *>(offset_pointer(datum, x * sizeof(ulong))) = 0xBABABABA;
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

	auto next_identifier = data_make_first_identifier(data);
	data->next_identifier = next_identifier;
	data->isolated_next_identifier = ~next_identifier | k_datum_base_identifier;

	assert(data->next_identifier < k_datum_base_identifier);
	assert(data->isolated_next_identifier < k_datum_base_identifier);

	if (data_should_verify_data_pattern(data))
	{
		auto total_size = data->maximum_count * data->size;

		if (total_size > 32 || !pointer_is_aligned(data, 2) || total_size & 3)
		{
			csmemset(data, 0xBA, total_size);
		}
		else
		{
			for (auto x = 0; x < total_size / sizeof(ulong); x++)
				*reinterpret_cast<ulong *>(offset_pointer(data, x * sizeof(ulong))) = 0xBABABABA;
		}
	}

	auto datum_size = data->size;

	for (long i = 0; i < data->maximum_count; i++)
	{
		auto datum = reinterpret_cast<s_datum_header *>(
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
			destination->data = nullptr;
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
			auto in_use_bit_vector = reinterpret_cast<ulong *>(
				offset_pointer(destination, destination->offset_to_bit_vector));

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

	auto data = iterator->data;

	assert(data);
	assert(data->valid);

	vassert(iterator->signature == (reinterpret_cast<ulong>(data) ^ k_data_iterator_signature),
		csnzprintf(temporary, 256, "uninitialized iterator passed to %s", __FUNCTION__));

	data_verify(data);

	auto absolute_index = data_next_absolute_index(data, iterator->index + 1);
	auto datum_index = static_cast<long>(NONE);
	
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

	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
	auto identifier = DATUM_INDEX_TO_IDENTIFIER(index);

	assert(identifier != 0);

	if (absolute_index > NONE && absolute_index < data->maximum_count)
	{
		auto datum = reinterpret_cast<s_datum_header *>(
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

	auto datum = reinterpret_cast<s_datum_header *>(
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

	auto maximum_count = data->maximum_count;
	auto datum_size = data->size;
	auto next_index = data->next_index;
	auto datum_index = static_cast<long>(NONE);
	auto absolute_index = static_cast<long>(NONE);

	auto in_use_bit_vector = data->in_use_bit_vector;

	do
	{
		if (absolute_index > data->first_unallocated)
		{
		$datum_new_start:
			if ((absolute_index == NONE) && (data->first_unallocated < data->maximum_count))
				absolute_index = data->first_unallocated;

			if (absolute_index != NONE)
			{
				auto datum = reinterpret_cast<s_datum_header *>(
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

	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(requested_index);
	auto identifier = DATUM_INDEX_TO_IDENTIFIER(requested_index);

	assert(identifier != 0);

	auto index = static_cast<long>(NONE);

	if (absolute_index > NONE && absolute_index < data->maximum_count)
	{
		auto datum = reinterpret_cast<s_datum_header *>(
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

	auto index = static_cast<long>(NONE);

	if (absolute_index > NONE && absolute_index < data->maximum_count)
	{
		auto datum = reinterpret_cast<s_datum_header *>(
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

	auto in_use_bit_vector = data->in_use_bit_vector;
	
	auto next_index = minimum_index;

	auto last_index = (minimum_index + count_indices < data->first_unallocated) ?
		minimum_index + count_indices :
		data->first_unallocated;

	auto absolute_index = static_cast<long>(NONE);
	auto datum_index = static_cast<long>(NONE);

	do
	{
		if (last_index <= next_index)
		{
		$datum_new_start:
			if (absolute_index == NONE && next_index < minimum_index + count_indices)
				absolute_index = next_index;

			if (absolute_index != NONE)
			{
				auto datum = reinterpret_cast<s_datum_header *>(
					offset_pointer(data->data, absolute_index * data->size));

				BIT_VECTOR_SET_FLAG(in_use_bit_vector, absolute_index, true);
				data->actual_count++;

				if (data->first_unallocated <= absolute_index)
					data->first_unallocated = absolute_index + 1;

				assert(datum->identifier == 0);

				auto salt = (salt_type == _datum_salt_isolated_identifier) ?
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
	s_datum_header *header,
	ushort *out_identifier)
{
	static char temporary[256];

	assert(data);
	assert(header);
	assert(out_identifier);

	auto datum_size = data->size;
	auto datum_offset = pointer_distance(data->data, header);
	auto absolute_index = datum_offset / datum_size;

	if (data_should_verify_data_pattern(data))
	{
		for (auto offset = sizeof(s_datum_header);
			offset < datum_size;
			offset++)
		{
			auto current = reinterpret_cast<uchar *>(offset_pointer(header, offset));

			vassert(*current == 0xBA,
				csnzprintf(temporary, 256,
					"%s index #%d byte#%d @%p isn\'t as free as it should be (something is writing to an unused datum)",
					data->name, absolute_index, offset, current));
		}
	}

	if (datum_size > 32 || !pointer_is_aligned(header, 2) || datum_size & 3)
	{
		csmemset(header, 0, datum_size);
	}
	else
	{
		for (int x = 0; x < datum_size / sizeof(ulong); x++)
			*reinterpret_cast<ulong *>(offset_pointer(header, x * sizeof(ulong))) = 0;
	}

	ushort identifier = *out_identifier;

	if (identifier == NONE)
		identifier = k_datum_base_identifier;

	header->identifier = identifier;

	assert(header->identifier != 0 && header->identifier != NONE);

	*out_identifier = identifier + 1;
}

void *datum_try_and_get(
	s_data_array *data,
	long index)
{
	static char temporary[256];

	assert(data);
	assert(data->valid);

	s_datum_header *result = nullptr;

	if (index != NONE)
	{
		auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
		auto identifier = DATUM_INDEX_TO_IDENTIFIER(index);

		vassert(identifier != 0,
			csnzprintf(temporary, 256,
				"tried to access %s using datum_try_and_get() with an absolute index #%d",
				data->name, index));

		vassert(absolute_index >= 0 && absolute_index < data->maximum_count,
			csnzprintf(temporary, 256,
				"tried to access %s using datum_try_and_get() with an index 0x%08X outside maximum range [0, %d)",
				data->name, index, data->maximum_count));

		if (absolute_index < data->first_unallocated)
		{
			auto datum = reinterpret_cast<s_datum_header *>(
				offset_pointer(data->data, absolute_index * data->size));

			if (datum->identifier != 0 && datum->identifier == identifier)
				result = datum;
		}
	}

	assert(result == align_pointer(result, data->alignment_bits));

	return result;
}

void *datum_try_and_get_unsafe(
	s_data_array *data,
	long index)
{
	assert(data);
	assert(data->valid);

	s_datum_header *result = nullptr;

	if (index != NONE)
	{
		auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
		auto identifier = DATUM_INDEX_TO_IDENTIFIER(index);

		if (absolute_index > NONE && absolute_index < data->first_unallocated)
		{
			auto datum = reinterpret_cast<s_datum_header *>(
				offset_pointer(data->data, absolute_index * data->size));

			if (datum->identifier != 0 && datum->identifier == identifier)
				result = datum;
		}
	}

	assert(result == align_pointer(result, data->alignment_bits));

	return result;
}

void *datum_try_and_get_absolute(
	s_data_array *data,
	long absolute_index)
{
	static char temporary[256];

	assert(data);
	assert(data->valid);

	s_datum_header *result = nullptr;

	if (absolute_index != NONE)
	{
		auto identifier = DATUM_INDEX_TO_IDENTIFIER(absolute_index);

		vassert(DATUM_INDEX_TO_IDENTIFIER(absolute_index) == 0,
			csnzprintf(temporary, 256,
				"tried to access %s using datum_try_and_get_absolute() with a non absolute index #%d (0x%x)",
				data->name, DATUM_INDEX_TO_ABSOLUTE_INDEX(absolute_index), absolute_index));

		vassert(absolute_index >= 0 && absolute_index < data->maximum_count,
			csnzprintf(temporary, 256,
				"tried to access %s using datum_try_and_get_absolute() with an absolute index 0x%04X outside maximum range [0, %d]",
				data->name, DATUM_INDEX_TO_ABSOLUTE_INDEX(absolute_index), data->maximum_count));

		if (absolute_index > NONE && absolute_index < data->first_unallocated)
		{
			auto datum = reinterpret_cast<s_datum_header *>(
				offset_pointer(data->data, absolute_index * data->size));

			if (datum->identifier != 0)
				result = datum;
		}
	}

	assert(result == align_pointer(result, data->alignment_bits));

	return result;
}

void *datum_get(
	s_data_array *data,
	long index)
{
	static char temporary[256];

	assert(data);
	assert(data->valid);

	vassert(index != NONE,
		csnzprintf(temporary, 256,
			"tried to access %s index NONE",
			data->name));

	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
	auto identifier = DATUM_INDEX_TO_IDENTIFIER(index);

	vassert(identifier != 0,
		csnzprintf(temporary, 256,
			"tried to access %s using datum_get() with an absolute index #%d",
			data->name, index));

	vassert(absolute_index >= 0 && absolute_index < data->first_unallocated,
		csnzprintf(temporary, 256,
			"%s index #%d (0x%x) is out of range (%d)",
			data->name, absolute_index, index, data->first_unallocated));

	auto header = reinterpret_cast<s_datum_header *>(
		offset_pointer(data->data, absolute_index * data->size));

	vassert(header->identifier != 0,
		csnzprintf(temporary, 256,
			"%s index #%d (0x%x) is unused",
			data->name, absolute_index, index));

	auto datum_index = BUILD_DATUM_INDEX(header->identifier, absolute_index);

	vassert(header->identifier == identifier,
		csnzprintf(temporary, 256,
			"%s index #%d (0x%x) is changed, should be 0x%x",
			data->name, absolute_index, index, datum_index));

	assert(data->alignment_bits == 0 || header == align_pointer(header, data->alignment_bits));

	return header;
}

void *datum_get_absolute(
	s_data_array *data,
	long index)
{
	static char temporary[256];

	assert(data);
	assert(data->valid);

	vassert(index != NONE,
		csnzprintf(temporary, 256,
			"tried to access %s index NONE",
			data->name));

	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
	auto identifier = DATUM_INDEX_TO_IDENTIFIER(index);

	vassert(identifier == 0,
		csnzprintf(temporary, 256,
			"tried to access %s using datum_get_absolute() with a non absolute index #%d",
			data->name, index));

	vassert(absolute_index >= 0 && absolute_index < data->first_unallocated,
		csnzprintf(temporary, 256,
			"%s absolute index #%d (0x%x) is out of range (%d)",
			data->name, absolute_index, index, data->first_unallocated));

	auto header = reinterpret_cast<s_datum_header *>(
		offset_pointer(data->data, absolute_index * data->size));

	vassert(header->identifier != 0,
		csnzprintf(temporary, 256,
			"%s absolute index #%d (0x%x) is unused",
			data->name, absolute_index, index));

	assert(data->alignment_bits == 0 || header == align_pointer(header, data->alignment_bits));

	return header;
}

void datum_delete(
	s_data_array *data,
	long index)
{
	assert(data);

	auto datum_size = data->size;
	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
	auto datum = reinterpret_cast<s_datum_header *>(datum_get(data, index));

	if (data_should_verify_data_pattern(data))
	{
		if (datum_size > 32 || !pointer_is_aligned(datum, 2) || datum_size & 3)
		{
			csmemset(datum, 0xBA, datum_size);
		}
		else
		{
			for (int x = 0; x < datum_size / sizeof(ulong); x++)
				*reinterpret_cast<ulong *>(offset_pointer(datum, x * sizeof(ulong))) = 0xBABABABA;
		}
	}

	BIT_VECTOR_SET_FLAG(data->in_use_bit_vector, absolute_index, false);

	datum->identifier = 0;

	if (absolute_index < data->next_index)
		data->next_index = absolute_index;

	if (absolute_index + 1 == data->first_unallocated)
	{
		do
		{
			datum = offset_pointer(datum, -static_cast<long>(datum_size));
			data->first_unallocated--;
			if (data->first_unallocated < 1) break;
		} while (datum->identifier == 0);
	}

	data->actual_count--;
}
