#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

class __declspec(novtable) c_allocation_interface
{
public:
	virtual void *allocate(ulonglong size, char const *file, long line) = 0;
	virtual void deallocate(void *address, char const *file, long line) = 0;
};

class c_heap_allocation : public c_allocation_interface
{
public:
	c_heap_allocation() {}

	void *allocate(ulonglong size, char const *file, long line);
	void deallocate(void *address, char const *file, long line);
};

class c_null_allocation : public c_allocation_interface
{
public:
	c_null_allocation() {}

	void *allocate(ulonglong size, char const *file, long line);
	void deallocate(void *address, char const *file, long line);
};

/* ---------- globals */

extern c_heap_allocation *const g_heap_allocation;
extern c_null_allocation *const g_null_allocation;
