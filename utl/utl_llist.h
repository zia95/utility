/*
		Linked list......
*/


#ifndef UTL_LLIST
#define UTL_LLIST

#include "utl_mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "utl_env.h"

typedef struct _LLELEMENT_
{
	void* pdata;

	void* nxt;
} LLElement, * PLLElement;

#define llist_element_new() (PLLElement)mem_alloc_zero(sizeof(LLElement));
#define llist_element_free(pelm) mem_free(pelm);

typedef struct _LLIST_
{
	size_t count;
	PLLElement head;
	PLLElement tail;
} LList, *PLList;

#define llist_new() (PLList)mem_alloc_zero(sizeof(LList));


void llist_clear(PLList pl);

__inline void llist_free(PLList pl)
{
	if (pl)
	{
		llist_clear(pl);
		mem_free(pl);
	}
}

PLLElement llist_add(PLList pl, void* pdata);
void llist_add_range(PLList pl, size_t range, void* pfirst, ...);

PLLElement llist_get(PLList pl, size_t idx);

//#define llist_data(pelm, pdata) pelm->pdata = pdata;

#define llist_count(pl) pl->count

void* llist_remove(PLList pl, size_t idx);
void* llist_remove_elm(PLList pl, PLLElement pelm);







typedef void (__cdecl_call* llist_iter_cb)(PLList pl, size_t idx, PLLElement pelm);

void llist_iter(PLList pl, llist_iter_cb iter);

#endif //!UTL_LLIST