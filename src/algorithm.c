#include "algorithm.h"

static int32_t getPivot(int32_t* array,int32_t i,int32_t j);

static int32_t getPivot(int32_t* array,int32_t i,int32_t j)
{
    int k = i + 1;
    while(k <= j && array[i]==array[k])
    {
        k++;
    }
    if(k > j)
    {
        return -1;
    }
    if(array[i] >= array[k])
    {
        return i;
    }
    return k;
}

void quick_sort(int32_t* array,int32_t left,int32_t right)
{
    if(right > left)
    {
        int32_t pivot = getPivot(array,left,right);
        int32_t i     = left;
        int32_t j     = right;

        if(pivot != -1)
        {
            while(1)
            {
                while(array[i] < pivot) i++;
                while(array[j] > pivot) j--;
                if(i >= j) break;
                SWAP(int32_t,array[i],array[j]);
                i++;
                j--;
            }
        }
        if(left < i - 1) quick_sort(array,left,i -1);
        if(j+1 < right) quick_sort(array,j+1,right);
    }
}
