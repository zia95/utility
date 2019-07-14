#include "utl_mem.h"

void* mem_alloc_zero(size_t size)
{
	void* p = mem_alloc(size);
	return p ? mem_zero(p, size) : NULL;
}
void* mem_calloc_zero(size_t count, size_t size)
{
	void* p = mem_calloc(count, size);
	return p ? mem_zero(p, size) : NULL;
}


void* mem_dup(void* mem, size_t size)
{
	void* dpt = mem_alloc(size);
	return dpt ? mem_cpy(dpt, mem, size) : NULL;
}
void* mem_cdup(void* mem, size_t count, size_t size)
{
	void* dpt = mem_calloc(count, size);
	return dpt ? mem_cpy(dpt, mem, (count * size)) : NULL;
}