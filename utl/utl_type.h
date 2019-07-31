#ifndef UTL_TYPE
#define UTL_TYPE


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <wchar.h>


#define type_charisdigit isdigit
#define type_charisalpha isalpha

#define type_charislower islower
#define type_charisupper isupper

#define type_charisspecial(c) !(type_charisdigit(c) && type_charisalpha(c))





#define type_wcharisdigit iswdigit
#define type_wcharisalpha iswalpha

#define type_wcharislower iswlower
#define type_wcharisupper iswupper

#define type_wcharisspecial(c) !(type_wcharisdigit(c) && type_wcharisalpha(c))





#define type_chartolower tolower
#define type_chartoupper toupper



#define type_wchartolower towlower
#define type_wchartoupper towupper


#define type_chartowchar btowc
#define type_wchartochar wctob





#endif //!UTL_TYPE