//The following program allows you to calculate from up to 99!
2432902008176640000
/*
The greater N! that you can calculate in an average computer using C (and most of languages) is 20!. This
is because: 21! > 18,446,774,073,709,551,615 which is 2^64 (unsigned long long).

The following snippet allows you to calculate from 21! to 99! by doing long multiplication (yes, like in elementary school). Here is an
example if you don't remember what I'm talking about:
2432902008176640000     = 20!
x 21
-------------------------
02432902008176640000    = 2432902008176640000*1
4865804016353280000     = 2432902008176640000*2 
-------------------------
51090942171709440000    = 2432902008176640000 + 4865804016353280000 = 21! 

The first parameter should be "1" and the second the factorial number we need, for example, 88.

Please note that this is only for positive integer numbers. 

This could also be achieved using integers instead of chars but a char is most of the times 4 times smaller than an integer.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void incrementStringNumber(char* numberPlusPlus);
char* moreThan20Factorial( char *n);
char* longMultiplication( char* factor1,  char* factor2);
char* formatNumber(char *n, int slice, char separator);

int main(int argc, char* argv[])
{
	char *result; 

	result = moreThan20Factorial(argv[1]);
	result = formatNumber(result, 100, '\n');

	printf("%s! = %s\n", argv[1], result);
}

char* formatNumber(char *n, int slice, char separator)
{
	char *newNumber, sep[2];
	unsigned long long nLength = strlen(n);
	if(nLength > slice)
	{
		unsigned long long index, groups, newLength, skip;
		
		newLength = nLength%slice == 0 ? nLength + nLength/slice - 1 : nLength + nLength/slice;
		groups = nLength%slice == 0 ? nLength/slice-1: nLength/slice;
		skip = nLength%slice == 0 ? slice: nLength%slice;
		index = 0;

		newNumber = calloc( newLength+1, sizeof(char) );

		strncat( newNumber, n, skip*sizeof(char) );
		sep[0] = separator;
		sep[1] = '\0';
		while( index < groups )
		{
			strcat( newNumber, sep);
			strncat( newNumber, n+skip+index*slice, slice*sizeof(char) );
			index++;
		}

		return newNumber;
	}	
	return n;
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
		incrementStringNumber(maxInteger);
		result = longMultiplication(maxInteger, result);
		
	}while( strcmp(n, maxInteger) != 0);
		
	return result;
}

void incrementStringNumber(char* numberPlusPlus)
{
	unsigned long long index = strlen(numberPlusPlus);
	bool added = false;
	do
	{
		index--;
		if(numberPlusPlus[index] < '9')
		{
			numberPlusPlus[index]++;
			added = true;
		}
		else if( index > 0)
			numberPlusPlus[index] = '0';

	}while( index > 0 && !added );

	return; 
}

char* longMultiplication( char* factor1,  char* factor2)
{	
	unsigned long long f1Size = strlen(factor1), f2Size = strlen(factor2);
	unsigned long long resultSize = f1Size + f2Size;
	
	char *result; 
	unsigned int product = 0, prevCarry = 0, sumCarry = 0, carry = 0;
	

	if( f1Size == 0 || f2Size == 0 )
		return "0";

	// We need to prepare the space for normalized summands and the result... 
	result = calloc( resultSize+1, sizeof(char) );

	for(unsigned long long i = 0; i<resultSize; i++)
			result[i] = '0';
	result[resultSize] = '\0';
	
	unsigned long long longest, shortest, resultIndex, units;
	longest = f1Size >= f2Size ? f1Size : f2Size ;
	shortest = f2Size <= f1Size ? f2Size : f1Size ;
	units = 0;

	do
	{
		shortest--;
		resultIndex = (resultSize-1) - units;		
		do
		{
			// we get the product of the multiplication of two factors and its carry
			longest--;
			if( f1Size >= f2Size )
				product = (factor1[longest]-'0') * (factor2[shortest]-'0');
			else
				product = (factor1[shortest]-'0') * (factor2[longest]-'0');

			carry = (product > 9) ? product/10 : 0;
			product -= carry*10;

			// we add the previous carry to the current product
			product += prevCarry;
			prevCarry = (product > 9) ? product/10 : 0;
			product -= prevCarry*10;
			// we add the previous result to the current one
			product += (result[resultIndex] - '0');
			sumCarry = (product > 9) ? product/10 : 0;
			product -= sumCarry*10;
			//We get the carry for the next operation
			prevCarry += (carry + sumCarry); 
			// we get the product of the multiplication of two factors and its carry
			result[resultIndex] = (char)(product + '0');
			resultIndex--; 
		}while( longest >=1 );
		result[resultIndex] = (char)(prevCarry + '0');
		prevCarry = 0;
		units++;
		longest = f1Size >= f2Size ? f1Size : f2Size ;

	}while( shortest >= 1 );
	//most of the times you'll have spare zeros in the left, so we rotate 
	while(result[0] == '0' && strlen(result) > 1)
		memmove(result, result+1, resultSize*sizeof(char)+1);

	return result;
}
