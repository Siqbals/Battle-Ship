#include <err.h>
#include <stdlib.h>
#include <sys/time.h>

// The seed is an arbitrary bit string derived from the time-of-day clock on the
// CPU. Type suseconds_t is long int on tuxworld.
void rand_init( void ) {
    struct timeval tv;
    
    if( gettimeofday( &tv, NULL ) != 0 ) {
        err( -1, NULL );        // Something is dreadfully wrong.
    }                           // Abort with error message and failing exit

    // srandom() wants an unsigned int as argument.  However, tv_usec is of type
    // suseconds_t which is long int on tuxworld.  Using tv.tv_usec as the
    // argument to srandom() will cause only the low-order 4 bytes of tv.tv_usec
    // to be passed to srandom(). However, this is fine since we simply want an
    // arbitrary bit string to use as the seed for the random number generator.
    srandom( tv.tv_usec );
}

// RAND_MAX is 2147483647 = 0x7fffffff (a 32-bit int) on tuxworld
int rand_num( int max ) {
    
    // random() returns a long int.  Both max and RAND_MAX are of type int.
    // Therefore there should be no overflow in the calculation of the
    // return value.
    return max*random()/RAND_MAX;
}

