#include <cseries/cseries_asserts.h>
#include <cseries/cseries_memory.h>
#include <cstring>

void *csmemcpy(void *destination, void const *source, unsigned long length)
{
	assert(destination && source);

	errno_t memcpy_result = memcpy_s(destination, length, source, length);
	assert(memcpy_result == 0);

	return destination;
}

void *csmemmove(void *destination, void const *source, unsigned long length)
{
	assert(destination && source);

	errno_t memmove_result = memmove_s(destination, length, source, length);
	assert(memmove_result == 0);

	return destination;
}

void *csmemset(void *address, int m_value, unsigned long length)
{
	assert(address);

	void *memset_result = memset(address, m_value, length);
	assert(memset_result);

	return memset_result;
}

int csmemcmp(void *p1, void *p2, unsigned long length)
{
	assert(p1 && p2);
	return memcmp(p1, p2, length);
}
