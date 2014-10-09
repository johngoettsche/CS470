/***************************************************************************************************************
*
* Copyright (c) 2012, Eccam s.r.o.
*
* All rights reserved.
*
*/

#include <stdio.h>

#include "IntContainer.h"

/**************************************************************************************************************/

bool LessThan(int lhs, int rhs)
{
    return lhs < rhs;
}

/**************************************************************************************************************/

bool GreaterThan(int lhs, int rhs)
{
    return lhs > rhs;
}

/**************************************************************************************************************/

// note passing container by value - copy constructor will be included in the profiler log
int SearchBest(IntContainer container, bool (*Comparator) (int, int))
{
    int best = container.At(0);

    for (unsigned int i = 1; i < container.Size(); ++i)
    {
        if (Comparator(container.At(i), best))
        {
            best = container.At(i);
        }
    }

    return best;
}

/**************************************************************************************************************/

int main(int /*argc*/, char* /*argv*/[])
{
    int arr[] = { 6, 7, 43, 17, 28, 30, 3, 144, 142, 130 };
    IntContainer container;
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
        container.Add(arr[i]);

    printf("Lower item: %d\n", SearchBest(container, LessThan));
    printf("Higher item: %d\n", SearchBest(container, GreaterThan));

    return 0;
}

/**************************************************************************************************************/
