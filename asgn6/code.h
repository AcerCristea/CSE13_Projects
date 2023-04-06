#ifndef __CODE_H__
#define __CODE_H__

#include <inttypes.h>

#define STOP_CODE  0 // signals end of decoding/decoding
#define EMPTY_CODE 1 // code denoting the empty Word
#define START_CODE 2 // Starting code of the new Words
#define MAX_CODE   UINT16_MAX // Maximum code

#endif
