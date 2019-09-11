#ifndef UTL_ASCIIGEN
#define UTL_ASCIIGEN

#include "utl_rand.h"


// functions to be used...
#define ___srand(SEED) rand_set_seed(SEED)
#define ___srand_tm() rand_set_seed_as_time()

#define ___rand(MIN,MAX) rand_get_random(MIN,MAX)



#define CHAR_LOWER_OFF_BEG 97
#define CHAR_LOWER_OFF_END 122

#define CHAR_UPPER_OFF_BEG 65
#define CHAR_UPPER_OFF_END 90

#define CHAR_NUMBER_OFF_BEG 48
#define CHAR_NUMBER_OFF_END 57

#define CHAR_SPECIAL_ONE_OFF_BEG 33
#define CHAR_SPECIAL_ONE_OFF_END 47

#define CHAR_SPECIAL_TWO_OFF_BEG 58
#define CHAR_SPECIAL_TWO_OFF_END 64

#define CHAR_SPECIAL_THREE_OFF_BEG 91
#define CHAR_SPECIAL_THREE_OFF_END 96

#define CHAR_SPECIAL_FOUR_OFF_BEG 123
#define CHAR_SPECIAL_FOUR_OFF_END 126



#define asciigen_seed() ___srand_tm()
 



// return type, char generation failed because no type was specified.
#define RET_ERRNO_GEN_CHAR_ARG_NO_TYPE 0


#define asciigen_gen_char_lower()		___rand(CHAR_LOWER_OFF_BEG,			CHAR_LOWER_OFF_END)
#define asciigen_gen_char_upper()		___rand(CHAR_UPPER_OFF_BEG,			CHAR_UPPER_OFF_END)
#define asciigen_gen_char_number()		___rand(CHAR_NUMBER_OFF_BEG,		CHAR_NUMBER_OFF_END)
#define asciigen_gen_char_special_s1()	___rand(CHAR_SPECIAL_ONE_OFF_BEG,	CHAR_SPECIAL_ONE_OFF_END)
#define asciigen_gen_char_special_s2()	___rand(CHAR_SPECIAL_TWO_OFF_BEG,	CHAR_SPECIAL_TWO_OFF_END)
#define asciigen_gen_char_special_s3()	___rand(CHAR_SPECIAL_THREE_OFF_BEG, CHAR_SPECIAL_THREE_OFF_END)
#define asciigen_gen_char_special_s4()	___rand(CHAR_SPECIAL_FOUR_OFF_BEG,	CHAR_SPECIAL_FOUR_OFF_END)


inline char asciigen_gen_char_special()
{
	switch (___rand(0, 3))
	{
	case 0: return asciigen_gen_char_special_s1();
	case 1: return asciigen_gen_char_special_s2();
	case 2: return asciigen_gen_char_special_s3();
	case 3: return asciigen_gen_char_special_s4();
	}
	return -1;
}

// nothings
#define GC_NONE 0
// generate lower char
#define GC_LOWER 1 << 0
// generate upper char
#define GC_UPPER 1 << 1
// generate number char
#define GC_NUMBER 1 << 2
// generate symbol char
#define GC_SYMBOL 1 << 3


#ifndef byte
#define byte unsigned char

#ifndef pbyte
#define pbyte byte*
#endif // !pbyte

#endif // !byte



inline char ___get_rand_type(byte gc_flags)
{
	char typev[4];
	int typec = -1;


	if (gc_flags & GC_LOWER)
	{
		typec++;
		typev[typec] = 'l';
	}
	if (gc_flags & GC_UPPER)
	{
		typec++;
		typev[typec] = 'u';
	}
	if (gc_flags & GC_NUMBER)
	{
		typec++;
		typev[typec] = 'n';
	}
	if (gc_flags & GC_SYMBOL)
	{
		typec++;
		typev[typec] = 's';
	}
	if (typec >= 1)
		typec = ___rand(0, typec);

	return typec != -1 ? typev[typec] : RET_ERRNO_GEN_CHAR_ARG_NO_TYPE;
}

inline char asciigen_gen_char(byte gc_flags)
{
	switch (___get_rand_type(gc_flags))
	{
	case 'l': return asciigen_gen_char_lower();
	case 'u': return asciigen_gen_char_upper();
	case 'n': return asciigen_gen_char_number();
	case 's': return asciigen_gen_char_special();
	}
	return RET_ERRNO_GEN_CHAR_ARG_NO_TYPE;
}


//#define asciigen_gen_char_seq(bufbeg, bufend, gc_flags) for (; bufbeg != bufend; bufbeg++) { *bufbeg = asciigen_gen_char(gc_flags); if (*bufbeg == RET_ERRNO_GEN_CHAR_ARG_NO_TYPE) break; }
	

inline bool asciigen_gen_char_seq(char* bufbeg, size_t count, byte gc_flags)
{
	char* bufend = bufbeg + count;
	for (; bufbeg != bufend; bufbeg++) 
	{ 
		*bufbeg = asciigen_gen_char(gc_flags); 
		if (*bufbeg == RET_ERRNO_GEN_CHAR_ARG_NO_TYPE) 
			false; 
	}
	return true;
}
/*
inline void asciigen_gen_char_seq(char* buffer, size_t size, byte gc_flags)
{
	for (size_t i = 0; i < size; i++)
	{
		buffer[i] = asciigen_gen_char(gc_flags);
		if (buffer[i] == RET_ERRNO_GEN_CHAR_ARG_NO_TYPE)
			return;
	}
}
*/




#endif // !UTL_ASCIIGEN

