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


#if __GNUC__

#define __inline static inline
#define __cdecl_call __attribute__ ((__cdecl__))

#else

#define __inline inline
#define __cdecl_call __cdecl

#endif //__GNUC__



#endif //!UTL_ENV