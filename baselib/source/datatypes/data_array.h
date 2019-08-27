#pragma once

#include <cseries/cseries.h>
#include <datatypes/datum_handle.h>
#include <datatypes/flags.h>
#include <datatypes/static_string.h>
#include <datatypes/tag.h>
#include <memory/allocation_interface.h>

/* ---------- constants */

enum
{
	k_data_signature = 'd@t@',
	k_data_iterator_signature = 'iter',

	k_datum_base_identifier = 0x8000,
};

/* ---------- types */

enum e_datum_salt
{
	_datum_salt_identifier,
	_datum_salt_isolated_identifier,
	k_datum_salt_count
};

struct s_datum_header
{
	unsigned short identifier;
};
static_assert(sizeof(s_datum_header) == 0x2);

struct s_datum_header_aligned : s_datum_header
{
	short : 16;
};
static_assert(sizeof(s_datum_header_aligned) == 0x4);

enum e_data_array_flags
{
	_data_array_can_disconnect_bit,
	_data_array_disconnected_bit,
	_data_array_unknown2_bit,
	_data_array_verify_data_pattern_bit,
	k_number_of_data_array_flags
};

struct s_data_array
{
	c_static_string<32> name;
	long maximum_count;
	uint size;
	uchar alignment_bits;
	bool valid;
	c_flags<e_data_array_flags, ushort> flags;
	tag signature;
	c_allocation_interface *allocation;
	long next_index;
	long first_unallocated;
	long actual_count;
	ushort next_identifier;
	ushort isolated_next_identifier;
	void *data;
	ulong *in_use_bit_vector;
	long offset_to_data;
	long offset_to_bit_vector;
};
static_assert(sizeof(s_data_array) == 0x60);

struct s_data_iterator
{
	s_data_array *data;
	long next_index;
	long index;
	tag signature;
	long : 32;
};
static_assert(sizeof(s_data_iterator) == 0x18);

/* ---------- prototypes/DATA_ARRAY.CPP */

uint data_allocation_size(long maximum_count, uint size, long alignment_bits);

bool data_is_empty(s_data_array *data);
bool data_is_full(s_data_array *data);
bool data_should_verify_data_pattern(s_data_array *data);

s_data_array *data_new(
	char const *name,
	long maximum_count,
	uint size,
	long alignment_bits,
	char const *file,
	long line,
	c_allocation_interface *allocation);

s_data_array *data_new_disconnected(
	char const *name,
	long maximum_count,
	uint size,
	long alignment_bits,
	char const *file,
	long line,
	c_allocation_interface *allocation);

void data_initialize(
	s_data_array *data,
	char const *name,
	long maximum_count,
	uint size,
	long alignment_bits,
	c_allocation_interface *allocation);

void data_initialize_disconnected(
	s_data_array *data,
	char const *name,
	long maximum_count,
	uint size,
	long alignment_bits,
	c_allocation_interface *allocation,
	ulong *in_use_bit_vector);

void data_dispose(
	s_data_array *data,
	char const *file,
	long line);

long data_get_count(s_data_array *data);
long data_get_watermark(s_data_array *data);

long data_last_index(s_data_array *data);
long data_next_index(s_data_array *data, long index);
long data_next_absolute_index(s_data_array *data, long index);
long data_previous_index(s_data_array *data, long index);

ushort data_make_first_identifier(s_data_array *data);

void data_connect(s_data_array *data, long maximum_count, void *datums);
void data_disconnect(s_data_array *data);

void data_delete_all(s_data_array *data);

void data_verify(s_data_array *data);
void data_make_valid(s_data_array *data);
void data_make_invalid(s_data_array *data);

void data_set_new_base_address(s_data_array **source, s_data_array *destination);

void data_iterator_begin(s_data_iterator *iterator, s_data_array *data);
void *data_iterator_next(s_data_iterator *iterator);

bool datum_available_at_index(s_data_array *data, long index);

long datum_absolute_index_to_index(s_data_array *data, long index);

long datum_new(s_data_array *data);
long datum_new_at_index(s_data_array *data, long requested_index);
long datum_new_at_absolute_index(s_data_array *data, long absolute_index);
long datum_new_in_range(s_data_array *data, long minimum_index, long count_indices, e_datum_salt salt_type);

void datum_initialize(s_data_array *data, s_datum_header *datum, ushort *out_identifier);

void *datum_try_and_get(s_data_array *data, long index);
void *datum_try_and_get_unsafe(s_data_array *data, long index);
void *datum_try_and_get_absolute(s_data_array *data, long index);

void *datum_get(s_data_array *data, long index);
void *datum_get_absolute(s_data_array *data, long index);

void datum_delete(s_data_array *data, long index);
void datum_clear(void *datum, uint size);

/* ---------- classes */

template <typename t_datum>
class c_data_array final : public s_data_array
{
	static_assert(is_base_of<s_datum_header, t_datum>);

public:
	bool is_empty() const { return data_is_empty(this); }
	bool is_full() const { return data_is_full(this); }
	bool should_verify_pattern() const { return data_should_verify_data_pattern(this); }

	void initialize(
		char const *name,
		long maximum_count,
		long alignment_bits,
		c_allocation_interface *allocation)
	{
		data_initialize(this, name, maximum_count, sizeof(t_datum), alignment_bits, allocation);
	}

	void initialize_disconnected(
		char const *name,
		long maximum_count,
		long alignment_bits,
		c_allocation_interface *allocation,
		ulong *in_use_bit_vector)
	{
		data_initialize_disconnected(this, name, maximum_count, sizeof(t_datum), alignment_bits, allocation, in_use_bit_vector);
	}

	void dispose(
		char const *file,
		long line)
	{
		data_dispose(this, file, line);
	}

	long get_count() const { return data_get_count(this); }
	long get_watermark() const { return data_get_watermark(this); }

	long last_index() const { return data_last_index(this); }
	long next_index(long index) const { return data_next_index(this, index); }
	long next_absolute_index(long index) { return data_next_absolute_index(this, index); }
	long previous_index(long index) { return data_previous_index(this, index); }

	ushort make_first_identifier() { return data_make_first_identifier(this); }

	void connect(long maximum_count, void *datums) { data_connect(this, maximum_count, datums); }
	void disconnect() { data_disconnect(this); }

	long new_datum() { return datum_new(this); }
	long new_datum_at_index(long index) { return datum_new_at_index(this, index); }
	long new_datum_at_absolute_index(long index) { return datum_new_at_absolute_index(this, index); }
	long new_datum_in_range(long minimum_index, long count_indices, e_datum_salt salt)
	{
		return datum_new_in_range(this, minimum_index, count_indices, salt);
	}

	void delete_all() { data_delete_all(this); }

	void verify() { data_verify(this); }
	void make_valid() { data_make_valid(this); }
	void make_invalid() { data_make_invalid(this); }

	void copy(c_data_array<t_datum> *source) { data_copy(source, this); }
	void set_new_base_address(c_data_array<t_datum> *source) { data_set_new_base_address(source, this); }

	//
	// TODO: finish
	//
};
