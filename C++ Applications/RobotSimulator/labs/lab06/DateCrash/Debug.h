#ifndef DEBUG_H
#define DEBUG_H

#include <cstdlib>

#define DEBUG 0

#define assert(e) if (!(e)) {             \
     cout << "Invariant \"" << #e         \
          << "\" on line "                \
          << __LINE__ << " fails.\n"  ;   \
     exit(1) ;} 

#endif /* DEBUG_H */
