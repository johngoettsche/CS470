/***************************************************************************************************************
 *
 * Copyright (c) 2012, Eccam s.r.o.
 *
 * All rights reserved.
 *
 */

#ifndef __INT_CONTAINER_H__
#define __INT_CONTAINER_H__

/**
 * Simple container class for integers.
 */
class IntContainer
{
public:
    /** Constructor. */
    IntContainer();

    /** Destructor. */
    ~IntContainer();

    /** Copy constructor. */
    IntContainer(const IntContainer& other);

    /** Assignment operator. */
    IntContainer& operator=(const IntContainer& other);

    /**
     * Adds item into the container at the end.
     *
     * \param[in] item Item to add to container.
     */
    void Add(int item);

    /** Clears container. */
    void Clear();

    /**
     * Gets item from the container.
     *
     * \param[in] index Index of the item to get.
     *
     * \return Item which is stored in container at given index.
     */
    int At(unsigned int index) const;

    /** Returns the number of items stored in the container. */
    unsigned int Size() const;

private:
    /** Reallocates memory for the container. */
    void Realloc(unsigned int new_alloc_size);

    int*         m_pContainer;     /**< Pointer to allocated container. */
    unsigned int m_AllocSize;      /**< Allocated size of container in number of items. */
    unsigned int m_Size;           /**< Number of items stored in the container. */
};

#endif // __INT_CONTAINER_H__
