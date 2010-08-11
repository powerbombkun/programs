#include "dbconv.h"
#include <math.h>

double linear2db(int32_t pow_a,int32_t pow_b)
{
    return 20*log10((double)pow_a/(double)pow_b);
}

int32_t db2linear(double db,int32_t max_linear)
{
    double y = db / (double)20;
    return (int32_t)((double)max_linear * pow(10,y));
}

