# MoreThan20Factorial
The greater N! that you can calculate in an average computer using C (and most of languages) is 20!. This
is because: 21! > 18,446,774,073,709,551,615 which is 2^64 (unsigned long long).

The following program allows you to calculate the facorial of ANY number, you can for example calculate 3000!

There are two ways for this program to work:

1. Simply pass an unsigned integer and you'll get its factorial.
2. You can also pass an unsigned integer, followed by an integer greater than zero to indicate the size of each group of digits (default is 3) and fanally one quoted character as separator of each group (default is ','). (e.g. ./moreThan20Factorial 3000! 100 '#' )

Notice: this is the first successful impementation of bignums.h 
