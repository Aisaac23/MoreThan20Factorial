/*
The greater N! that you can calculate in an average computer using C (and most of languages) is 20!. This
is because: 21! > 18,446,774,073,709,551,615 which is 2^64 (unsigned long long).

The following program allows you to calculate the facorial of ANY number, you can for example calculate 3000!

There are two ways for this program to work:

1. Simply pass an unsigned integer and you'll get its factorial.
2. You can also pass an unsigned integer, followed by an integer greater than zero to indicate the size of each group of digits (default is 3) and fanally one quoted character as separator of each group (default is ','). (e.g. ./moreThan20Factorial 3000! 100 '#' )

Notice: this is the first successful impementation of bignums.h 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "chkops.h"
#include "bignums.h"

char* moreThan20Factorial( char *n);

int main(int argc, char* argv[])
{
	char *result, s[2];

	if(argc == 4)
	{
		if( isUnsignedInteger(argv[1]) && isUnsignedInteger(argv[2]) && strlen(argv[3]) <= 2 )
		{
			result = moreThan20Factorial( argv[1] );
			s[0] = isUnsignedInteger(argv[3]) ? atoi(argv[3]) : argv[3][0];
			result = formatNumber( result, atoi(argv[2]) , s[0]);
		}
	}
	else if(argc == 2)
	{
		result = moreThan20Factorial( argv[1] );
		result = formatNumber( result, 3, ',' );
	}
	else
	{
		printf("Thre could be some data missing in: %s\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
		
	printf("%s! = %s\n", argv[1], result);
	return EXIT_SUCCESS;
}


char* moreThan20Factorial( char *n)
{
	char *maxInteger, *result;
	unsigned long long nLength = strlen(n);
	
	maxInteger = calloc( nLength+1, sizeof(char) );	
	result = calloc( 2, sizeof(char) );	

	for(unsigned long long index = 0; index < nLength; index++)
		maxInteger[index] = '0';

	maxInteger[nLength] = '\0';
	maxInteger[nLength-1] = '1';
	
	result[1] = '\0';
	result[0] = '1';
	
	if( strcmp(n, "0") == 0 || strcmp(n, "1") == 0 )
		return result;
	do
	{	
		maxInteger = increment(maxInteger);
		result = longMultiplication(maxInteger, result);
		
	}while( strcmp(n, maxInteger) != 0);
		
	return result;
}

