/* 
 * CS:APP Data Lab 
 * 
 * <Shreya Agrawal SHA94>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code 
must conform to the following style:

int Funct(arg1, arg2, ...) {
	/* brief description of how your implementation works */
	int var1 = Expr1;
	...
	int varM = ExprM;

	varJ = ExprJ;
	...
		varN = ExprN;
	return ExprR;
}

Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xffffffff.
     However, you are allowed to combine constants to values greater
     than 255 or less than 0. e.g. 250 + 250 = 500, so long as
     the operator you are using to combine the constants is listed as
     "legal" at the top of the method you are writing.
  2. Function arguments and local variables (no global variables).
  3. Any operators listed as "legal" at the top of the method you are writing.
  4. Shorthand versions of "legal" operators (ex. you can use ++ and += if + is legal)

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
       /* exploit ability of shifts to compute powers of 2 */
       return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
       /* exploit ability of shifts to compute powers of 2 */
       int result = (1 << x);
       result += 4;
       return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
  5. Write comments for your functions! These won't be graded, but it's good
     practice to write comments and may help you debug your code. See the
     above example to see what the comments should look like.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 */
#endif

//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */

int bitXor(int x, int y) 
{ 
  int a,b;
    a = x & y;
    x = ~x; 
    y = ~y; 
    b = x & y;  
    return (~(a) & ~(b));
    
}

//2
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */

//tmax is 01111111111....111 
//Shifting left 
int starter = 1; 
int shiftLeft = 31;
int tmax(void) 
{
  return ~(starter << shiftLeft);
}
//3
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */

//The issue is that because this uses arithmetic shift, if the bits start with 1, 
//it will smear 1's on the left when we want it to smear 0 for it to be logical
//Thinking of anding with 0 in empty space, and anding with 1's at the value bits 

//We need to apply a mask where we and with 0 at top N bits, and 1 for the rest 
//Normally, we could figure out how many 1's by using sizeof(), but now need another way to find number of bits(b) taken up by x 
//Find number of bits(b) taken up by x, and with 1 at lowest b bits, and then with 0 at the rest


int logicalShift(int x, int n) 
{
   int result,mask = 0; 
    //Issue is that arithmetic shift smears 1's on the left instead of 0's
    //Need to apply mask to result where we and with 0, at top n bits, and with 1 at rest 
    //In order to obtain this mask, we can shift 1 all the way to the left and right shift by n 
    //But this gives us an extra 1 in the mask 
    //So we shift the resulting mask left by 1 
    //This gives us the complement of the mask
    //So we take the complement of the bits, to get our final mask 
    //We use this mask by Anding it with the result of the arithmetic shift  

    result = x >> n; 
    mask = (1 << 31); 
    mask = mask >> n;  
    mask = mask << 1; 
    mask = ~(mask); 
    result = result & mask; 
    return result;

}

//4
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
 
int allOddBits(int x) 
{  
  int a = 0, b = 0, c = 0, d = 0, mask = 0, result = 0;
  //In order to return 1 if all odd, we need to take the not of the false statement in binary(0000..0000) 
  //In order to get 0 if not all odd, we would take the not of the true statement -opposite of above 
  //We need to use a mask to replace all of the even positions with 0 because they don't matter
  //This mask will be 0 at even spaces, and 1 at odd spaces 
  //By applying this mask, we will get the exact mask as a result if there is a 1 in all odd bits 
  //We can then compare if the result is equal to the mask by using Xor  
  //If it is equal, it will return 0000.0000 
  //We would then take the not of that which would return 1 

  //Creating the mask without using large constant 
  a = 0xAA << 8; 
  b = 0xAA << 16; 
  c = 0xAA << 24;   
  d = 0xAA;
  mask = (a)|(b)|(c)|(d); 

  //Applying the mask 
  result = x & mask;  
  result = result ^ mask; 
  return !(result); 


}

//5
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */ 

//want to turn x into a mask that turns either y or z on 
//If x is 1, return y, else return z
int conditional(int x, int y, int z) 
{ 
   int y_mask = 0; 
   int z_mask = 0;

   //I created two masks, one for y and one for z 

   //Making y mask
   //If x was true, the double nots would return true-do want to return y  
   //If x was false, the double nots would return false-don't want to return y
   //Shifting left and then right creates a mask of all 1's or all 0's based on if it returned true or false
   y_mask = (((!(!(x))) << 31) >> 31);  

   //We apply the mask to y to either give us y or clear y
   y = y & y_mask; 

   //Making z mask
   //If x was true, the not would return false-do not want to return z 
   //If x was false, the not would return true-do want to return z
   //Shifting left and then right creates a mask of all 1's or all 0's based on it it returned true or false
   z_mask = (((!(x)) << 31) >> 31);  

   //We apply the mask to z to either give us z or clear z
   z = z & z_mask; 

   //Final step is to or y and z. Whichever one is not cleared out, is the value that would be returned
   return y | z;

}

//6
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */ 

   //We OR x with tilda x in order to get either all 1's or all 0's 
   //If x is true, 
   //If x is false, ORing it with tilda x would keep it at false 
   //We then apply the mask to f to either get f (000...000) if 
   //f = f & ((~x) | x);  


int logicalNeg(int x) 
{ 
   // When taking 2's complement of 0, the MSB is always 0. 
   //But when taking 2's complement of any other value, the MSB will switch    
   int logNeg = 0; 

   //If x is 1, when we OR x with its two's complement, we always get 1 in MSB bc MSB had to be 1 either in x or after taking 2's comp
   //If x is 0, when we OR x with its two's complement, we always get 0 in MSB bc 2's comp of 0 is always 0
   logNeg = ((~x) +1) | x;  

   //Smearing the MSB to fill in all the bits 
   //If x is 1, logNeg should be 11111...111 
   //If x is 0, logNeg should be 000..0000
   logNeg = (logNeg >> 31) >> 1;   

   //Adding 1 to logNeg negates the bits  
   //Adding 1 to 1111(which is 1 logically), makes it 0
   //Adding 1 to 0, makes it 1  
   logNeg = logNeg + 1;

   return logNeg;   
} 

//7
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) 
{
   int fraction,sign,expBias,exp,expSign,impOne,merged,truncateMask;
   
   //Extract the components from the bitfield by applying a mask
   sign = (uf >> 31);
   fraction = (uf >> 0) & 0x007FFFFF; 
   expBias = (uf >> 23) & 0x000000FF;    

   //Because exponent is in biased representation, we need to do exponent minus 127 to get the true exponent value
   exp = expBias - 0x0000007F;
   
   //expSign = !(!(expBias >> 8));  

   //Checking the edge cases 
   if(expBias == 0xFFFFFFFF) 
   { 
      return 0x80000000u;
   } 
   if(expBias == 0x00000000) 
   { 
      return 0x0;
   } 
   if(exp >= 31) 
   { 
      return 0x80000000u;
   } 
   if(exp < 0) 
   { 
      return 0x0;
   }

   //Adding the implicit 1 to the fraction 
   //In the fraction, the fraction bits take up bit 0 to bit 22. 
   //So we add the 1 exactly at bit 23 which is what we set impOne equal to
   impOne = 0x00800000;   
   fraction = fraction | impOne;  

   //Remember that we currently have the bits set as 1fraction. 
   //But it should have been in the form 1.fraction 
   //In order to account for this, we create this conditional 

   //The equivalent of multiplying fraction by 2^exp is shifting left by exponent  
   //If exp is greater than 22, we cannot shift right at all
   //If exp is greater than 22, we can shift left only by the exponent minus 23. 
   //This takes care of the truncation after applying the decimal
   
   //If exp is less than 22, we shift right by (23-exp) 
   //Shifting right by (23-exp) works the same as adding those extra 0's onto the end of a number 
   //as we move the decimal point to the right (for decimal numbers) and truncates anything after the decimal 

   //Ex: If the exponent is 23, we would simply shift left by 0(no shift) 
   //because the decimal is already perfectly sitting at the end after 23 bits and we have our int
   if(exp > 22) 
   { 
      fraction = fraction << (exp - 23);
   } 
   else 
   { 
      fraction = fraction >> (23 - exp);
   }

   if(sign == 1) 
   { 
         fraction = ~fraction + 1; 
   }
   
   return fraction;
}
