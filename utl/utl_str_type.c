#include"utl_str_type.h"

//parse
double str_try_todouble(pcstr str, bool* successful)
{
	char* pEnd;
	double res = strtod(str, &pEnd);
	if (successful)* successful = !(*pEnd);

	return res;
}
float str_try_tofloat(pcstr str, bool* successful)
{
	char* pEnd;
	float res = strtof(str, &pEnd);
	if (successful)* successful = !(*pEnd);

	return res;
}
long str_try_tolong(pcstr str, int base, bool* successful)
{
	char* pEnd;
	long res = strtol(str, &pEnd, base);
	if (successful)* successful = !(*pEnd);

	return res;
}
llong str_try_tollong(pcstr str, int base, bool* successful)
{
	char* pEnd;
	long long res = strtoll(str, &pEnd, base);
	if (successful)* successful = !(*pEnd);

	return res;
}
ulong str_try_toulong(pcstr str, int base, bool* successful)
{
	char* pEnd;
	unsigned long res = strtoul(str, &pEnd, base);
	if (successful)* successful = !(*pEnd);

	return res;
}
ullong str_try_toullong(pcstr str, int base, bool* successful)
{
	char* pEnd;
	unsigned long long res = strtoull(str, &pEnd, base);
	if (successful)* successful = !(*pEnd);

	return res;
}

//wide
double strw_try_todouble(pcstrw str, bool* successful)
{
	wchar_t* pEnd;
	double res = wcstod(str, &pEnd);
	if (successful)* successful = !(*pEnd);

	return res;
}
float strw_try_tofloat(pcstrw str, bool* successful)
{
	wchar_t* pEnd;
	float res = wcstof(str, &pEnd);
	if (successful)* successful = !(*pEnd);

	return res;
}
long strw_try_tolong(pcstrw str, int base, bool* successful)
{
	wchar_t* pEnd;
	long res = wcstol(str, &pEnd, base);
	if (successful)* successful = !(*pEnd);

	return res;
}
llong strw_try_tollong(pcstrw str, int base, bool* successful)
{
	wchar_t* pEnd;
	long long res = wcstoll(str, &pEnd, base);
	if (successful)* successful = !(*pEnd);

	return res;
}
ulong strw_try_toulong(pcstrw str, int base, bool* successful)
{
	wchar_t* pEnd;
	unsigned long res = wcstoul(str, &pEnd, base);
	if (successful)* successful = !(*pEnd);

	return res;
}
ullong strw_try_toullong(pcstrw str, int base, bool* successful)
{
	wchar_t* pEnd;
	unsigned long long res = wcstoull(str, &pEnd, base);
	if (successful)* successful = !(*pEnd);

	return res;
}