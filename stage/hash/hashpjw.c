/* hashpjw.c */

/* includes */
#include "hashpjw.h"

/* definitions */
int hashpjw( const void *key, int tablesize ) {
	const char *ptr = key;
	int val = 0;

	while( *ptr != '\0' ) {
		int tmp;
		val = ( ( val << 4 ) + ( *ptr ) );
		if( ( tmp = ( val & 0xf0000000 ) ) ) {
			val = val ^ ( tmp >> 24 );
			val = val ^ tmp;
		}
		ptr++;
	}
	return val % tablesize;
}
