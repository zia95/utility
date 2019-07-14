#ifndef UTL_RAND
#define UTL_RAND


#include <stdlib.h>
#include <time.h>

#define rand_set_seed(seed) srand(seed)
#define rand_set_seed_as_time() rand_set_seed((unsigned int)time(0))


#define rand_get_random(min, max) (rand() % (min - (max + 1)) + min)


	/*
	inline int GetRandom(int min = 0, int max = 9)
	{
		if (min < max)
		{
			return (rand() % (min - (max + 1)) + min);
		}
		return -1;
	}
	*/

#endif // !UTL_RAND

