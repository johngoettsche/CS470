/***************************************************************************************************************
*
* Copyright (c) 2012, Eccam s.r.o.
*
* All rights reserved.
*
*/

#include <stdio.h>

#include "RandomGenerator.h"
#include "Factorial.h"

/**************************************************************************************************************/

int main(int /*argc*/, char* /*argv*/[])
{
    RandomGenerator generator(1, 10);
    const int iter_count = generator.GetRandomValue();
    printf("Iteration count is %d.\n", iter_count);
    for (int i = 0; i < iter_count; ++i)
    {
        const int value = generator.GetRandomValue();
        printf("Factorial of %d is %d.\n", value, CalculateFactorial(value));
    }

    return 0;
}

/**************************************************************************************************************/
