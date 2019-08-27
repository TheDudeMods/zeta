#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

class __declspec(novtable) c_allocation_interface
{
public:
	virtual void *allocate(unsigned long size, char const *file, long line) = 0;
	virtual void deallocate(void *address, char const *file, long line) = 0;
};

class c_base_allocation : public c_allocation_interface
{
public:
	c_base_allocation();

	void *allocate(unsigned long size, char const *file, long line);
	void deallocate(void *address, char const *file, long line);
};

class c_heap_allocation : public c_allocation_interface
{
public:
	c_heap_allocation();

	void *allocate(unsigned long size, char const *file, long line);
	void deallocate(void *address, char const *file, long line);
};

class c_null_allocation : public c_allocation_interface
{
public:
	c_null_allocation();

	void *allocate(unsigned long size, char const *file, long line);
	void deallocate(void *address, char const *file, long line);
};

/* ---------- globals */

extern c_base_allocation *g_base_allocation;
extern c_heap_allocation *g_heap_allocation;
extern c_null_allocation *g_null_allocation;
