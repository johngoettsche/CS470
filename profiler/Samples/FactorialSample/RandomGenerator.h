/***************************************************************************************************************
*
* Copyright (c) 2012, Eccam s.r.o.
*
* All rights reserved.
*
*/

/**
 * Simple generator of random numbers.
 */
class RandomGenerator
{
public:
    /**
     * Constructor.
     *
     * \param[in] min Minimum value to generate.
     * \param[in] max Maximum value to generate.
     */
    RandomGenerator(int min, int max);

    /** Destructor. */
    ~RandomGenerator();
    
    /** Returns randomly generated value. */
    int GetRandomValue();

private:
    // disable copy constructor and copy assignment operator
    RandomGenerator(const RandomGenerator&);
    RandomGenerator& operator=(const RandomGenerator&);
    
    int             m_Min;          /**< Minimum value to generate. */
    int             m_Modulo;       /**< Calculate modulo value from minimum and maximum values. */
    unsigned int    m_RandValue;    /**< Value to initialize rand() function. */
};
