#include <memory/allocation_interface.h>

/* ---------- private globals */

static c_heap_allocation g_heap_allocation_instance;
static c_null_allocation g_null_allocation_instance;

/* ---------- globals */

c_heap_allocation *const g_heap_allocation = &g_heap_allocation_instance;
c_null_allocation *const g_null_allocation = &g_null_allocation_instance;

/* ---------- code */

void *c_heap_allocation::allocate(
	ulonglong size,
	[[maybe_unused]] char const *file,
	[[maybe_unused]] long line)
{
	return new char[size];
}

void c_heap_allocation::deallocate(
	void *address,
	[[maybe_unused]] char const *file,
	[[maybe_unused]] long line)
{
	delete address;
}

void *c_null_allocation::allocate(
	[[maybe_unused]] ulonglong size,
	[[maybe_unused]] char const *file,
	[[maybe_unused]] long line)
{
	vassert(false, "g_null_allocation->allocate");
}

void c_null_allocation::deallocate(
	[[maybe_unused]] void *address,
	[[maybe_unused]] char const *file,
	[[maybe_unused]] long line)
{
}
