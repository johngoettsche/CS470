/***************************************************************************************************************
 *
 * Copyright (c) 2012, Eccam s.r.o.
 *
 * All rights reserved.
 *
 */

#include <stddef.h>

#include "IntContainer.h"

/**************************************************************************************************************/

IntContainer::IntContainer()
: m_pContainer(NULL), m_AllocSize(0), m_Size(0)
{
}

/**************************************************************************************************************/

IntContainer::~IntContainer()
{
    if (m_pContainer != NULL)
    {
        delete[] m_pContainer;
        m_pContainer = NULL;
    }
}

/**************************************************************************************************************/

IntContainer::IntContainer(const IntContainer& other)
: m_pContainer(NULL), m_AllocSize(0), m_Size(0)
{
    *this = other;
}

/**************************************************************************************************************/

IntContainer& IntContainer::operator=(const IntContainer& other)
{
    Clear();
    for (unsigned int i = 0; i < other.Size(); ++i)
    {
        this->Add(other.At(i));
    }

    return *this;
}

/**************************************************************************************************************/

void IntContainer::Add(int item)
{
    if (m_AllocSize == m_Size)
        Realloc(m_AllocSize * 2 + 1);

    m_pContainer[m_Size] = item;
    m_Size++;
}

/**************************************************************************************************************/

void IntContainer::Clear()
{
    m_Size = 0;
}

/**************************************************************************************************************/

int IntContainer::At(unsigned int index) const
{
    if (index >= m_Size)
        return 0;

    return m_pContainer[index];
}

/**************************************************************************************************************/

unsigned int IntContainer::Size() const
{
    return m_Size;
}

/**************************************************************************************************************/

void IntContainer::Realloc(unsigned int new_alloc_size)
{
    int* p_new_data = new int [new_alloc_size];

    if (m_pContainer != NULL)
    {
        int* p_src = m_pContainer;
        int* p_dest = p_new_data;
        for (unsigned int i = 0; i < m_Size; ++i)
            *p_dest++ = *p_src++;

        delete [] m_pContainer;
    }

    m_pContainer = p_new_data;
    m_AllocSize = new_alloc_size;
}

/**************************************************************************************************************/
