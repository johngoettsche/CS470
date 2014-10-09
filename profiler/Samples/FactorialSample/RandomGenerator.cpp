/***************************************************************************************************************
*
* Copyright (c) 2012, Eccam s.r.o.
*
* All rights reserved.
*
*/

#include <stdlib.h>

#include "RandomGenerator.h"

/**************************************************************************************************************/

RandomGenerator::RandomGenerator(int min, int max)
: m_Min(min), m_Modulo(max + 1 - min)
{
    srand(m_RandValue);
} 

/**************************************************************************************************************/

RandomGenerator::~RandomGenerator()
{
}

/**************************************************************************************************************/

int RandomGenerator::GetRandomValue()
{
    return (rand() % m_Modulo) + m_Min;
}

/**************************************************************************************************************/
