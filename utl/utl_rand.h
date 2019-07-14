#ifndef UTL_RAND
#define UTL_RAND


#include <stdlib.h>
#include <time.h>

#define rand_set_seed(seed) srand(seed)
#define rand_set_seed_as_time() rand_set_seed((unsigned int)time(0))


#define rand_get_random(min, max) (rand() % (min - (max + 1)) + min)
#endif // !UTL_RAND