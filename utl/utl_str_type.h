#ifndef UTL_STR_TYPE
#define UTL_STR_TYPE




#ifndef UTL_STR
#include <stdlib.h>
#include <stdbool.h>

typedef char* pstr;
typedef wchar_t* pstrw;

typedef const char* pcstr;
typedef const wchar_t* pcstrw;
#endif



typedef long long			llong;
typedef unsigned long		ulong;
typedef unsigned long long	ullong;

//parse
double str_try_todouble	(pcstr str, bool* successful);
float str_try_tofloat	(pcstr str, bool* successful);
long str_try_tolong		(pcstr str, int base, bool* successful);
llong str_try_tollong	(pcstr str, int base, bool* successful);
ulong str_try_toulong	(pcstr str, int base, bool* successful);
ullong str_try_toullong	(pcstr str, int base, bool* successful);

//wide
double strw_try_todouble(pcstrw str, bool* successful);
float strw_try_tofloat	(pcstrw str, bool* successful);
long strw_try_tolong	(pcstrw str, int base, bool* successful);
llong strw_try_tollong	(pcstrw str, int base, bool* successful);
ulong strw_try_toulong	(pcstrw str, int base, bool* successful);
ullong strw_try_toullong(pcstrw str, int base, bool* successful);


#define str_todouble	(str)		str_try_todouble(str, NULL)
#define str_tofloat		(str)		str_try_tofloat(str, NULL)
#define str_tolong		(str, base) str_try_tolong(str, base, NULL)
#define str_tollong		(str, base) str_try_tollong(str, base, NULL)
#define str_toulong		(str, base) str_try_toulong(str, base, NULL)
#define str_toullong	(str, base) str_try_toullong(str, base, NULL)

#define strw_todouble	(str)		strw_try_todouble(str, NULL)
#define strw_tofloat	(str)		strw_try_tofloat(str, NULL)
#define strw_tolong		(str, base) strw_try_tolong(str, base, NULL)
#define strw_tollong	(str, base) strw_try_tollong(str, base, NULL)
#define strw_toulong	(str, base) strw_try_toulong(str, base, NULL)
#define strw_toullong	(str, base) strw_try_toullong(str, base, NULL)

#ifdef UTL_STR

// string to type x
#define str_tostr_float		(str, len, f)	str_format(str, len, "%f", f)
#define str_tostr_decimal	(str, len, d)	str_format(str, len, "%d", d)
#define str_tostr_hex		(str, len, x)	str_format(str, len, "%x", x)
#define str_tostr_octate	(str, len, o)	str_format(str, len, "%o", o)

#define strw_tostr_float	(str, len, f)	strw_format(str, len, L"%f", f)
#define strw_tostr_decimal	(str, len, d)	strw_format(str, len, L"%d", d)
#define strw_tostr_hex		(str, len, x)	strw_format(str, len, L"%x", x)
#define strw_tostr_octate	(str, len, o)	strw_format(str, len, L"%o", o)
#endif



#endif // !UTL_STR_TYPE
