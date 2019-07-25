#include "utl_str.h"

/*
char* str_substrr(const char* str, const char* substr)
{
	char* ptr, * last = NULL;
	ptr = (char*)str;
	while ((ptr = str_substr(ptr, substr))) last = ptr++;
	return last;
}
*/
char* str_substrr(const char* str, const char* substr)
{
	char* last = NULL;
	while ((str = str_substr(str, substr))) last = str++;
	return last;
}
wchar_t* strw_substrr(const wchar_t* str, const wchar_t* substr)
{
	wchar_t* last = NULL;
	while ((str = strw_substr(str, substr))) last = str++;
	return last;
}

char* str_subchrsr(const char* str, const char* subchrs)
{
	char* last = NULL;
	while ((str = str_subchrs(str, subchrs))) last = str++;
	return last;
}

wchar_t* strw_subchrsr(const wchar_t* str, const wchar_t* subchrs)
{
	wchar_t* last = NULL;
	while ((str = strw_subchrs(str, subchrs))) last = str++;
	return last;
}

size_t str_towcsn(pstrw* dest, pcstr src, size_t max_count)
{
	size_t converted = 0;
	if (dest != NULL && *dest == NULL && src != NULL && max_count > 0)
	{
		mbstate_t mbst = { 0 };

		if (!mbsinit(&mbst))
			memset(&mbst, 0, sizeof(mbst));


		*dest = strw_new_zero(max_count);

		converted = str_towcs_state(*dest, src, max_count, &mbst);
		if (converted <= 0)
			free(*dest);
	}
	return converted;
}
size_t strw_tombsn(pstr * dest, pcstrw src, size_t max_count)
{
	size_t converted = 0;
	if (dest != NULL && *dest == NULL && src != NULL && max_count > 0)
	{
		mbstate_t mbst = { 0 };

		if (!mbsinit(&mbst))
			memset(&mbst, 0, sizeof(mbst));

		*dest = str_new_zero(max_count);


		converted = strw_tombs_state(*dest, src, max_count, &mbst);
		if (converted <= 0)
			free(*dest);
	}
	return converted;
}

size_t str_towcs(pstrw * dest, pcstr src)
{
	mbstate_t mbst = { 0 };

	if (!mbsinit(&mbst))
		memset(&mbst, 0, sizeof(mbst));


	size_t len = 1 + str_towcs_state(NULL, src, 0, &mbst);

	return (len > 1) ? str_towcsn(dest, src, len) : 0;
}
size_t strw_tombs(pstr * dest, pcstrw src)
{
	mbstate_t mbst = { 0 };

	if (!mbsinit(&mbst))
		memset(&mbst, 0, sizeof(mbst));


	size_t len = 1 + strw_tombs_state(NULL, src, 0, &mbst);

	return (len > 1) ? strw_tombsn(dest, src, len) : 0;
}


pstr str_end(pstr begin)
{
	for (; *begin; begin++) {}
	return begin;
	//return --begin;
}
pstrw strw_end(pstrw begin)
{
	for (; *begin; begin++) {}
	return begin;
	//return --begin;
}

//find char(s) from string

pstrw strw_find(pstrw begin, pstrw end, pcstrw mtchchars, byte sfflags)
{
	if (begin == NULL || end == NULL || mtchchars == NULL)
		return NULL;

	size_t len = 0;
	size_t lenofmtch = strw_len(mtchchars);



	int _cmp;
	bool rev = sfflags & SF_REVERSE;
	for (
		pstrw s = (rev ? end : begin);
		s != (rev ? begin : end);
		rev ? s-- : s++
		)
	{
		if (sfflags & SF_MATCH_AS_WHOLE)
		{
			if (rev)
			{
				len = strw_len(s);// make sure total len is same match-str len; otherwise it will just compare the end char.
				if (len < lenofmtch)
				{
					len = strw_len(begin);
					if (len < lenofmtch)
						return NULL;
					s = s - lenofmtch + 1;
					//len = strw_len(s);
				}
			}

			_cmp = (sfflags & SF_NO_CASE_SENSITIVE ? strw_cmpni(s, mtchchars, lenofmtch) : strw_cmpn(s, mtchchars, lenofmtch));
			if (sfflags & SF_NOT)
			{
				if (_cmp != 0)
					return s;
			}
			else if (_cmp == 0)
				return s;
		}
		else
		{
			for (const wchar_t* c = mtchchars; *c; c++)
			{
				_cmp = (sfflags & SF_NO_CASE_SENSITIVE ? strw_cmpni(s, c, 1) : *s - *c);
				if (sfflags & SF_NOT)
				{
					if (_cmp != 0)
						return s;
				}
				else if (_cmp == 0)
					return s;
			}
		}
	}
	return NULL;
}

pstr str_find(pstr begin, pstr end, pcstr mtchchars, byte sfflags)
{
	if (begin == NULL || end == NULL || mtchchars == NULL)
		return NULL;

	size_t len = 0;
	size_t lenofmtch = str_len(mtchchars);



	int _cmp;
	bool rev = sfflags & SF_REVERSE;
	for (
		pstr s = (rev ? end : begin);
		s != (rev ? begin : end);
		rev ? s-- : s++
		)
	{
		if (sfflags & SF_MATCH_AS_WHOLE)
		{
			if (rev)
			{
				len = str_len(s);// make sure total len is same match-str len; otherwise it will just compare the end char.
				if (len < lenofmtch)
				{
					len = str_len(begin);
					if (len < lenofmtch)
						return NULL;
					s = s - lenofmtch + 1;
					//len = str_len(s);
				}
			}

			_cmp = (sfflags & SF_NO_CASE_SENSITIVE ? str_cmpni(s, mtchchars, lenofmtch) : str_cmpn(s, mtchchars, lenofmtch));
			if (sfflags & SF_NOT)
			{
				if (_cmp != 0)
					return s;
			}
			else if (_cmp == 0)
				return s;
		}
		else
		{
			for (const char* c = mtchchars; *c; c++)
			{
				_cmp = (sfflags & SF_NO_CASE_SENSITIVE ? str_cmpni(s, c, 1) : *s - *c);
				if (sfflags & SF_NOT)
				{
					if (_cmp != 0)
						return s;
				}
				else if (_cmp == 0)
					return s;
			}
		}
	}
	return NULL;
}

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

pstr str_remove_ch(pstr begin, pstr end, const char c)
{
	for (char* i = begin; i != end; i++, begin++)
	{
		if (*i != c)
			* begin = *i;
		else
			begin--;

	}


	return begin;
}
pstrw strw_remove_ch(pstrw begin, pstrw end, const wchar_t c)
{
	for (wchar_t* i = begin; i != end; i++, begin++)
	{
		if (*i != c)
			* begin = *i;
		else
			begin--;

	}


	return begin;
}


pstr str_remove_range(pstr begin, pstr end, pstr sub_begin, pstr sub_end)
{
	for (char* i = begin; i != end; i++, begin++)
	{
		if (i == sub_begin)
			i = sub_end;
		*begin = *i;
	}


	return begin;
}
pstrw strw_remove_range(pstrw begin, pstrw end, pstrw sub_begin, pstrw sub_end)
{
	for (wchar_t* i = begin; i != end; i++, begin++)
	{
		if (i == sub_begin)
			i = sub_end;
		*begin = *i;
	}


	return begin;
}

pstr str_remove(pstr begin, pstr end, pcstr str, byte sfflags)
{
	pstr sub_begin = str_find(begin, end, str, sfflags);
	pstr sub_end = sub_begin + str_len(str);

	return str_remove_range(begin, end, sub_begin, sub_end);
}
pstrw strw_remove(pstrw begin, pstrw end, pcstrw strw, byte sfflags)
{
	pstrw sub_begin = strw_find(begin, end, strw, sfflags);
	pstrw sub_end = sub_begin + strw_len(strw);

	return strw_remove_range(begin, end, sub_begin, sub_end);
}