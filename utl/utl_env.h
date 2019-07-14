#ifndef UTL_ENV
#define UTL_ENV


#if _WIN32 || _WIN64
#define WIN
#if _WIN64
#define ENV64
#else
#define ENV32
#endif
#endif


#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENV64
#else
#define ENV32
#endif
#endif

#endif //!UTL_ENV