#ifndef UTL_STR
#define UTL_STR

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>


#include "utl_mem.h"



typedef char* 			pstr;
typedef wchar_t* 		pstrw;

typedef const char* 	pcstr;
typedef const wchar_t* 	pcstrw;

#ifndef byte
#define byte unsigned char

#ifndef pbyte
#define pbyte byte*
#endif // !pbyte

#endif // !byte


#if _WIN32 || _WIN64
//winh
#else
//unixh
#include <strings.h>
#include <unistd.h>
#endif

#define SIZE_OF_WCHAR sizeof(wchar_t) 

//str new
#define str_new(len) (char*)mem_alloc(len);
#define strw_new(len) (wchar_t*)mem_calloc(len, SIZE_OF_WCHAR)

#define str_new_zero(len) (char*)mem_alloc_zero(len);
#define strw_new_zero(len) (wchar_t*)mem_calloc_zero(len, SIZE_OF_WCHAR)

//reloc
#define str_realloc(str, size) (char*)mem_realloc(str, size)
#define strw_realloc(str, size) (wchar_t*)mem_recalloc(str, size, SIZE_OF_WCHAR)

//str free
#define str_free(str) mem_free(str)
#define strw_free(str) mem_free(str)

//str set
#define str_set(str, c, size) mem_set(str, c, size)
#define strw_set str_set

//duplicate
#define str_dup(str, len) (char*)mem_dup(str, len);
#define strw_dup(str, len) (wchar_t*)mem_cdup(str, len, SIZE_OF_WCHAR)

//copy
#define str_cpy(dest, src) strcpy(dest, src)
#define strw_cpy(dest, src) wcscpy(dest, src)

#define str_cpyn(dest, src, len) strncpy(dest, src, len)
#define strw_cpyn(dest, src, len) wcsncpy(dest, src, len) //mem_cpy(dest, src, len*SIZE_OF_WCHAR)

/*
//move
#define str_movn(dest, src, len) mem_mov(dest, src, len)
#define strw_movn(dest, src, len) mem_mov(dest, src, len*SIZE_OF_WCHAR)
*/
//append
#define str_cat(dest, src) strcat(dest, src)
#define strw_cat(dest, src) wcscat(dest, src)

#define str_catn(dest, src, len) strncat(dest, src, len)
#define strw_catn(dest, src, len) wcsncat(dest, src, len)


//str compare
#define str_cmpn(str1, str2, len) strncmp(str1, str2, len)
#define strw_cmpn(str1, str2, len) wcsncmp(str1, str2, len)

#define str_cmp(str1, str2) strcmp(str1, str2)
#define strw_cmp(str1, str2) wcscmp(str1, str2)



#if _WIN32 || _WIN64
#define str_cmpni(str1, str2, len) _strnicmp(str1, str2, len)
#define strw_cmpni(str1, str2, len) _wcsnicmp(str1, str2, len)

#define str_cmpi(str1, str2) _stricmp(str1, str2)
#define strw_cmpi(str1, str2) _wcsicmp(str1, str2)
#else

#define str_cmpni(str1, str2, len) strncasecmp(str1, str2, len)
#define strw_cmpni(str1, str2, len) wcsncasecmp(str1, str2, len)

#define str_cmpi(str1, str2)  strcasecmp(str1, str2)
#define strw_cmpi(str1, str2) wcscasecmp(str1, str2)
#endif

//str is equal?
#define str_equ(x,y) (str_cmp(x,y) == 0)
#define strw_equ(x,y) (strw_cmp(x,y) == 0)

#define str_equi(x,y) (str_cmpi(x,y) == 0)
#define strw_equi(x,y) (strw_cmpi(x,y) == 0)

//str get length
#define str_len(str) strlen(str)
#define strw_len(str) wcslen(str)



//conversion
// returns number of char's converted sucessfully

#define str_towcs_state(dest, src, max_count, pstate) mbsrtowcs(dest, &src, max_count, pstate)
#define strw_tombs_state(dest, src, max_count, pstate) wcsrtombs(dest, &src, max_count, pstate)


size_t str_towcsn(pstrw* dest, pcstr src, size_t max_count);
size_t strw_tombsn(pstr* dest, pcstrw src, size_t max_count);

size_t str_towcs(pstrw* dest, pcstr src);
size_t strw_tombs(pstr* dest, pcstrw src);


//#define str_tostrw_state str_towcs_state
//#define strw_tostr_state strw_tombs_state

#define str_tostrwn str_towcsn
#define strw_tostrn strw_tombsn

#define str_tostrw str_towcs
#define strw_tostr strw_tombs

pstr str_end(pstr begin);
pstrw strw_end(pstrw begin);






// find string_chars flags

//sf_none = normal search i.e. case sensitive, forward search, char by char match not whole string
#define SF_NONE 0
#define SF_NORMAL SF_NONE
// turn off case sensitivity
#define SF_NO_CASE_SENSITIVE 1 << 0
//match whole string i.e. return sucessful if whole sequence of char matches
#define SF_MATCH_AS_WHOLE 1 << 1
// return if does NOT matches
#define SF_NOT 1 << 2
// reverse search
#define SF_REVERSE 1 << 3


//find char(s) from string

pstrw strw_find(pstrw begin, pstrw end, pcstrw mtchchars, byte sfflags);

pstr str_find(pstr begin, pstr end, pcstr mtchchars, byte sfflags);

/*
pstrw strw_find_not_of(pstrw begin, pstrw end, pcstrw mtchchars)
{
	for (wchar_t* s = begin; s != end; s++)
		for (const wchar_t* c = mtchchars; *c; c++)
			if (*s != *c)
				return s;
	return NULL;
}
pstrw strw_find_rev(pstrw begin, pstrw end, pcstrw mtchchars)
{
	for (wchar_t* s = end; s != begin; s--)
		for (const wchar_t* c = mtchchars; *c; c++)
			if (*s == *c)
				return s;
	return NULL;
}
pstrw strw_find_rev_not_of(pstrw begin, pstrw end, pcstrw mtchchars)
{
	for (wchar_t* s = end; s != begin; s--)
		for (const wchar_t* c = mtchchars; *c; c++)
			if (*s != *c)
				return s;
	return NULL;
}
*/
/*
pstr str_find(pstr begin, pstr end, pcstr mtchchars)
{
	for (char* s = begin; s != end; s++)
		for (const char* c = mtchchars; *c; c++)
			if (*s == *c)
				return s;
	return NULL;
}
pstr str_find_not_of(pstr begin, pstr end, pcstr mtchchars)
{
	for (char* s = begin; s != end; s++)
		for (const char* c = mtchchars; *c; c++)
			if (*s != *c)
				return s;
	return NULL;
}
pstr str_find_rev(pstr begin, pstr end, pcstr mtchchars)
{
	for (char* s = end; s != begin; s--)
		for (const char* c = mtchchars; *c; c++)
			if (*s == *c)
				return s;
	return NULL;
}
pstr str_find_rev_not_of(pstr begin, pstr end, pcstr mtchchars)
{
	for (char* s = end; s != begin; s--)
		for (const char* c = mtchchars; *c; c++)
			if (*s != *c)
				return s;
	return NULL;
}
*/




//remove a char or char range from whole string

pstr str_remove_ch(pstr begin, pstr end, const char c);
pstrw strw_remove_ch(pstrw begin, pstrw end, const wchar_t c);


pstr str_remove_range(pstr begin, pstr end, pstr sub_begin, pstr sub_end);
pstrw strw_remove_range(pstrw begin, pstrw end, pstrw sub_begin, pstrw sub_end);

pstr str_remove(pstr begin, pstr end, pcstr str, byte sfflags);
pstrw strw_remove(pstrw begin, pstrw end, pcstrw strw, byte sfflags);







#define str_gets(str, count, stream) file_getsa(buffer, count, stream)
#define strw_gets(str, count, stream) file_getsw(buffer, count, stream)

#ifdef UTL_FILE
//get line
#define str_getline(stream)					file_readlinea(stream)
#define strw_getline(stream)				file_readlinew(stream)
#endif

//scan string
#define str_scan(str, format, ...)			sscanf(str, format, ...)
#define strw_scan(str, format, ...)			swscanf(str, format, ...)

//format string
#define str_format(str, len, format, ...)	snprintf(str, len, format, ...)
#define strw_format(str, len, format, ...)	swprintf(str, len, format, ...)

#endif // !UTL_STR
