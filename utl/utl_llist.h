#ifndef UTL_LLIST
#define UTL_LLIST

#include "utl_mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


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


void llist_clear(PLList pl)
{
	if (pl)
	{
		pl->count = 0;
		PLLElement pelm1 = pl->head;
		PLLElement pelm2 = NULL;

		while (pelm1)
		{
			pelm2 = (PLLElement)pelm1->nxt;
			llist_element_free(pelm1);
			pelm1 = pelm2;
		}
	}
}

void llist_free(PLList pl)
{
	if (pl)
	{
		llist_clear(pl);
		mem_free(pl);
	}
}

PLLElement llist_add(PLList pl, void* pdata)
{
	PLLElement pelm = llist_element_new();

	pelm->pdata = pdata;

	if (pl->head != NULL)
	{
		pl->tail->nxt = pelm;
		pl->tail = pl->tail->nxt;
	}
	else
	{
		pl->head = pelm;
		pl->tail = pelm;
	}
	
	pl->count++;
	return pelm;
}
void llist_add_range(PLList pl, size_t range, void* pfirst, ...)
{
	va_list vl;

	//void* pd = pfirst;


	va_start(vl, range);

	size_t max_count = pl->count + range;
	
	while (pl->count != max_count)
		llist_add(pl, va_arg(vl, void*));


	va_end(vl);
}

PLLElement llist_get(PLList pl, size_t idx)
{
	if (pl->count < idx)
		return NULL;

	PLLElement curr = pl->head;
	for (size_t i = 0; i < pl->count; i++)
	{
		if (i == idx)
			return curr;

		curr = curr->nxt;
	}

	return NULL;
}

#define llist_set_data(pelm, pdata) pelm->pdata = pdata;

void* llist_remove(PLList pl, size_t idx)
{
	if (idx == 0)
	{
		//first elm
		PLLElement curr = pl->head;
		pl->head = curr->nxt;
		void* pd = curr->pdata;
		llist_element_free(curr);
		pl->count--;
		return pd;
	}
	else
	{
		//middle

		if (!pl)
			return NULL;
		PLLElement prev = llist_get(pl, (idx-1));
		if (!prev)
			return NULL;
		PLLElement curr = prev->nxt;

		if (prev && curr)
		{
			prev->nxt = curr->nxt;

			void* pd = curr->pdata;
			llist_element_free(curr);
			pl->count--;
			if (pl->count == idx)
				pl->tail = prev;
			return pd;
		}
	}
	
	return NULL;
}
void* llist_remove_elm(PLList pl, PLLElement pelm)
{
	if (!pelm || !pl)
		return NULL;

	PLLElement curr = pl->head;

	for (size_t i = 0; i < pl->count; i++)
	{
		if (curr == pelm)
			return llist_remove(pl, i);

		curr = curr->nxt;
	}

	return NULL;
}

typedef void (__cdecl* llist_iter_cb)(PLList pl, size_t idx, PLLElement pelm);

void llist_iter(PLList pl, llist_iter_cb iter)
{
	if (pl && iter)
	{
		PLLElement curr = pl->head;
		for (size_t i = 0; i < pl->count; i++)
		{
			iter(pl, i, curr);

			curr = curr->nxt;
		}
	}
}

#endif //!UTL_LLIST