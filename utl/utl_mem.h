#ifndef UTL_MEM
#define UTL_MEM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mem_alloc(size) malloc(size)
#define mem_calloc(count, size) calloc(count, size)
#define mem_free(block) free(block)
#define mem_realloc(block, size) realloc(block, size)

#define mem_set(mem, val, size) memset(mem, val, size)

#define mem_zero(mem, size) mem_set(mem, 0, size)

#define mem_mov(dest, src, size) memmove(dest, src, size)
#define mem_cpy(dest, src, size) memcpy(dest, src, size)

#define mem_cmp(mem1, mem2, size) memcmp(mem1, mem2, size)

#define mem_nsearch(key, base, nbasecount, nbasesize, cbcmp) bsearch(key, base, nbasecount, nbasesize, cbcmp)

#define mem_search(key, base, nbasecount, cbcmp) mem_nsearch(key, base, nbasecount, 1, cbcmp)

#define mem_sort(base, nbasecount, nbasesize, cbcmp) qsort(base, nbasecount, nbasesize, cbcmp)


inline void* mem_recalloc(void* block, size_t count, size_t size);


inline void* mem_alloc_zero(size_t size);
inline void* mem_calloc_zero(size_t count, size_t size);


inline void* mem_dup(void* mem, size_t size);
inline void* mem_cdup(void* mem, size_t count, size_t size);




#define mem_alloc_obj(obj_type) (obj_type*)mem_alloc(sizeof(obj_type));
#define mem_alloc_obj_zero(obj_type) (obj_type*)mem_alloc_zero(sizeof(obj_type));


#endif //!UTL_MEM