#pragma once

/* ---------- prototypes/CSERIES_MEMORY.CPP */

void *csmemcpy(void *destination, void const *source, unsigned long long length);
void *csmemmove(void *destination, void const *source, unsigned long long length);
void *csmemset(void *address, int m_value, unsigned long long length);
int csmemcmp(void *p1, void *p2, unsigned long long length);
