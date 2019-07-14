#ifndef UTL
#define UTL

//#define _CRT_SECURE_NO_WARNINGS 1

#pragma warning(disable:4996)

#ifndef _SLIB



#ifndef NDEBUG

#ifndef WIN32
#define _64_32_ "../x64/"
#else
#define _64_32_ "../"
#endif // !WIN32

#define LIB_PATH _64_32_ "Debug/"
#else
#define LIB_PATH ""
#endif // !NDEBUG


#define LIB_NAME "utl.lib"

#define LIB LIB_PATH LIB_NAME

#pragma comment(lib, LIB)
#endif // _SLIB


#endif // !UTL