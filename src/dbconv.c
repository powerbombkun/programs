#include "dbconv.h"
#include <math.h>

#define MAX_LINEAR 0x7FFF

float linear2db(int16_t linear)
{
    return 20*log10((float)linear/(float)MAX_LINEAR);
}

int16_t db2linear(float db)
{
    float y = db / (float)20;
    return (int16_t)((float)MAX_LINEAR * pow(10,y));
}

