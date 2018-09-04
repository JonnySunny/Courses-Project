/*
 * CS:APP Data Lab
 *
 * Zhongyi Sun sunx0725
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
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
   int result  = (~(~x & ~ y)) & ~(x & y); // (X or y) and (~x or ~y)
   return result;
}
/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
	int temp = 0x55; // 0x55 can be written as 10101010 , and shift this number to fullfile the requirement.
	int result = (temp + (temp << 8) + (temp << 16) + (temp << 24));
	return result;
}
/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x) {
	return (x & (~x + 1)); // x and -x 
}
/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
	int difference = y + (~x + 1);
	int result = !(difference ^ 0);
	return result;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	int sign = (x >> 31);
	int temp = (~x & sign) + (x & ~sign); // if x >= 0, then temp = x; else temp = ~x
	int shift = n + ~0 ;//n - 1 to compare sign bit, because we know if there are only three bits, the range is from [-1, 4]
						// if after shift, a positive number'sign has changed, then we know it will be false. Otherwise true
	int result = !(temp >> shift);
	return result;
}

/*

 * reverseBytes - reverse the bytes of x

 *   Example: reverseBytes(0x01020304) = 0x04030201

 *   Legal ops: ! ~ & ^ | + << >>

 *   Max ops: 25

 *   Rating: 3

 */
int reverseBytes(int x) {
	int firstByte = (x >> 24) & 0xff;
	int mask2 = ((1 << 31 ) >> 23 ^ (1 << 31) >> 15) ; // as 0xff00
	int secondByte = (x >> 8) & mask2;
	int mask3 = ((1 << 31 ) >> 15 ^ (1 << 31) >> 7) ;  // as 0xff0000
	int thirdByte = (x << 8) & mask3;
	int fourthByte = x << 24;
  return firstByte +secondByte+thirdByte+fourthByte;}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	int sign = x >> 31; // keep sign 
	int result = !(x ^ 0) ^ (! sign); // compare with zero and change the logical to output right result
	return result;
}

/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
	int sign = (x >> 31)&1;
    int mul5 = (x << 2)+x ; // equal 5*x
    int round = (sign << 3)+( ~sign+1); // for negative number realsign equals number 7 and if it is a neagetive number we want it to round to 0;
    int div8 = (mul5 + round)>> 3; // equal 5*x / 8 
// if result is a negative, then we should add round to make it round toward 0; else if the resultis a positive, just drop the dicimal part
	return div8; 
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int dif = y+(~x+1); //to make a difference to compare with zero y-x
	int sign_x = (x >> 31)&1 ;
	int sign_y = (y >> 31)&1;
	int sign_dif = !((dif >> 31)&1) ; //the sign of the difference
	int result_Sign = ((!(sign_x ^ sign_y)) & (sign_dif)) + ((!(!(sign_x ^ sign_y)))& sign_x); 
	//when two variables have same sign, 
	//we know there is no overflow cases happened.
	//we also know that if overflow happened, it is always keep the same sign of substractor 
	return result_Sign;
}
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
 
int logicalNeg(int x) {
	
	int temp =  (x | (~x+1)); //-x = ~x + 1; if x = 0 , then temp = 0; otherwise, if x != 0 , because the " | ", 
								//we know that the signbit of temp always is one;
	
	int result = 1^(temp >> 31 & 1);  //
  return result; 
					
}
/*
 * tc2sm - Convert from two's complement to sign-magnitude
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x) {
  int sign = (x >> 31) & 1;
  int lastsign = sign << 31;
  int value = ((((sign^1)<<31 )>>31) & x) + (((sign^0)<<31 >>31)&(~x+1))  ; // x > 0 , value is x. x < 0 , value is -x = (~x+1)
  int result = lastsign + value;
  return result;
}
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
 
int leftBitCount(int x) {
	int basic = 1 << 31;
	int mask16left = basic >> 15 ; // 0xffff0000
	int result16,shift16,checked16;
	int result8,shift8,checked8;
	int result4,shift4,checked4;
	int result2,shift2,checked2;
	int result1,shift1,checked1;
	int result0;
	int sum;
	int mask8left = basic >> 7; //0xff000000; 
	int mask4left = basic >> 3; // 0xf0000000;
	int mask2left = basic >> 1; //0xc0000000;
	int mask1left = basic; //0x80000000;
    result16 = !((x & mask16left)^(((~1+1) ^ (mask16left))<<16));
     // if all 1s then shift continue to check the rest and 
     //if not, don't shift and to check the next 8 bit whether there exists continuous 1s;
    shift16 = result16 << 4;
    checked16 = x << shift16; // after shift or not shift , we already checked in this part whether exists continuous ones.
    
    
    result8 = !((checked16 & mask8left)^(0xff<<24));
    shift8 = result8 << 3;
    checked8 = checked16 << shift8;
    
    result4 = !((checked8 & mask4left)^(0xf<<28));
    shift4 = result4 << 2;
    checked4 = checked8 << shift4;
    
    result2 = !((checked4 & mask2left)^(0x3<<30));
    shift2 = result2 << 1;
    checked2 = checked4 << shift2;
    
    result1 = !((checked2 & mask1left)^(0x1)<<31);
    shift1 = result1;
    checked1 = checked2 << shift1;
    
    result0 = !(!(checked1 & ((0x1<< 31)^0))); // last one just compare with 1
    sum = shift1 + shift2 + shift4 + shift8 + shift16 + result0 ;
    return sum; 

}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	//1. right shift 23 bits and left shift 9 bits
	int exp = (uf >> 23) & 0xff ;
	int expallones = 0xff;// 0 | 11111111 |  
	int fraction = uf <<9;
	int mask = 1 << 31;
	if ( exp == expallones && fraction != 0){
		return uf;
	}
	
	return uf ^ mask; 
}

/*
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
	int r = !((uf & 3)^3); //to decide whether need round upward 
	int sign = ((uf >> 31) & 1) << 31;
	int maskexp = (1<<31>>8)^(1<<31);
	int exp = uf & maskexp ;
	int mask = (1 << 31) >> 8;
	int fraction = uf & (~mask);
	//special values
				
	if ( exp == maskexp){  // 0 | 11111111 |  
		return uf;
	}
	//denomarlized and special case
	if (exp == 0){
		return (sign + r + (fraction >> 1)); 
	}
	//special cases
	if(exp == (8 << 20)){   // 0 | 00000001 | 
		return (sign+((exp + fraction ) >> 1)+ r);}
    	// nomarlized
    	  return (((exp >> 23)-1)<<23) + sign + fraction ;
	}

