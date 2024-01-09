#ifndef _RAND_NUM_H
#define _RAND_NUM_H

/*
 * Function to initialize the seed for the pseudo-random number generator to an
 * arbitrary bit string.
 *
 * Input arguments: none
 * Return value: none
 * Assumes: function will always succeed
 */
void rand_init( void );

/*
 * Function to return the next in a sequence of pseudo-random integer values
 * in the range 0..max.  Note that unless rand_init() is called first, the 
 * same sequence of numbers is produced. 
 *
 * Input arguments: max, the upper bound of the range of possible return values
 * Return value: a random number in the closed interval 0..max.
 * Assumes: function will always succeed
 */
int rand_num( int max );

#endif // _RAND_NUM_H
