#include "algorithm.h"

static int32_t getPivot(int32_t* array,int32_t i,int32_t j);
static void quick_sort(int32_t* array,int32_t left,int32_t right);

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

void q_sort(int32_t* array,int32_t n)
{
    quick_sort(array,0,n-1);
}

static void quick_sort(int32_t* array,int32_t left,int32_t right)
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

void b_sort(int32_t* array,int32_t n)
{
    int i;
    int j;
    for (i = (n - 1); i > 1; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (array[j] > array[j + 1])
            {
                SWAP(int32_t,array[j],array[j+1]);
            }
        }
    }
}

int32_t binary_search(int32_t* array,int32_t n,int32_t val)
{
    int32_t start = 0;
    int32_t end   = n-1;
    while (start <= end)
    {
        int32_t mid = (start + end)/2;
        if (array[mid] < val)
        {
            start = mid + 1;
        }
        else if (array[mid] > val)
        {
            end = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
