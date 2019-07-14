#ifndef UTL_LOCALE
#define UTL_LOCALE

#include <locale.h>

#define locale_set(category, locale) setlocale(category, locale)


#define locale_set_default() locale_set(LC_ALL, "")

#define locale_get_finfo() localeconv();


#endif //!UTL_LOCALE