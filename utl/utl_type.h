#ifndef UTL_TYPE
#define UTL_TYPE


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <wchar.h>


#define type_charisnum(c) isdigit(c)
#define type_charisalpha(c) isalpha(c)

#define type_charislower(c) islower(c)
#define type_charisupper(c) isupper(c)

#define type_charisspecial(c) !(type_charisnum(c) && type_charisalpha(c))





#define type_wcharisnum(c) iswdigit(c)
#define type_wcharisalpha(c) iswalpha(c)

#define type_wcharislower(c) iswlower(c)
#define type_wcharisupper(c) iswupper(c)

#define type_wcharisspecial(c) !(type_wcharisnum(c) && type_wcharisalpha(c))





#define type_chartolower(c) tolower(c)
#define type_chartoupper(c) toupper(c)



#define type_wchartolower(c) towlower(c)
#define type_wchartoupper(c) towupper(c)


#define type_chartowchar(c) btowc(c)
#define type_wchartochar(wc) wctob(wc)





#endif //!UTL_TYPE