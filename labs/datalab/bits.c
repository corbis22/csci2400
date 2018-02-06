/*
 * CS:APP Data Lab
 *
 * Corey Stephens, 106228935
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
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  return 0x55 | (0x55<<8) | (0x55<<16) | (0x55<<24);
}
/*
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  return ~0;
}
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  int y = x<<31;
  return y>>31;
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
   int y = x >> 31; // will be 0xFFFFFFFF if x<0, 0x0 otherwise
   int z = y & 0x1; // will be 0x1 if x<0, 0x0 otherwise
   // if x<0, adds n-1 and then divides by 2^n
   // otherwise, z and y will both be zero, so just divides x by 2^n
   return (x + (z<<n) + y) >> n;
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  n = n << 3; // Multiply n by 8
  int y = 0xFF << n; // Now shifts left by n Bytes
  // Grab the desired byte using an &,
  // shift it back to the LSBs,
  // and & with 0xFF to remove any 1s possibly brought in by an arithmetic shift
	return ((x & y) >> n) & 0xFF;
}
/*
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
  int y = x & (0xAA | (0xAA<<8) | (0xAA<<16) | (0xAA<<24));
   return !!y;
}
/*
 * isNegative - return 1 if x < 0, return 0 otherwise
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
    int y = x>>31;
    return y & 0x1;
}
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int extr = x & (~0 << 4); // Capture the 28 leftmost bits
  int isGr7 = !!(x & 0x8); // Check if right nibble greater than 7
  int isGr9 = !!(x & 0x6); // Check if right nibble greater than 9
  // Will return 0 if there is anything in the leftmost 28 bits other than 0x11,
  // or if the right nibble is greater than 9.
  // Checks the 4th bit and bits 1-3 separately because 1000 and 1001 are both valid,
  // but 1010-1111 are not.
 return !(isGr7 & isGr9) & !(extr ^ 0x11);
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int fitsBits(int x, int n) {
  int field = (~0 << (n + ~0)); //Create a field of 1s to capture all bits outside the n-bit range
  int y = x & field; // Capture bits
  int allF = !(y ^ field); // If the captured bits are all 1s, x can still be represented in two's complement
                           // because these bits just serve to subtract/add from the 32-bit min, which would be lower with less bits
  // X fits only if the bits outside n are all 0s or all 1s
  return (!y | allF);
}
/*
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  int x_is_neg = (x >> 31) & 1;
  int y_is_neg = (y >> 31) & 1;
  int neg_y = ~y + 1;
  int diff = x + neg_y;
  int diff_is_neg = (diff >> 31) & 1;
  int x_diff_agree = !(x_is_neg ^ diff_is_neg);
  // The only time overflow has occured is when x and y have different signs,
  // and x and the result have different signs
  return !(x_is_neg ^ y_is_neg) | x_diff_agree;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int x_bool = !x; // 0x0 if x != 0, 0x1 if x == 0
  y = y & ((!x_bool << 31) >> 31); // y & 0xFFFFFFFF if x != 0
  z = z & ((x_bool << 31) >> 31); // z & 0xFFFFFFFF if x == 0
  return y + z;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int is1 = !(x ^ 1); // Check if x is 1 (special case, need to add 1 to bit count
  int isMin = !(x ^ (0x8 << 28)); // Check if x is the min 32-bit value (0x80000000) (special case, need to add 1 to bit count)

  // --- Convert to absolute value ---
  int y = x >> 31; // Will fill 1s if negative, 0s if not
  int p = y & 1; // Need to add 1 if converting from negative to positive
  // If x<0, will invert bits and add 1
  // Otherwise returns x
  x = (x ^ y) + p;

  // --- Check if x is a power of 2 ---
  int z = x + ~0; // subtract 1
  int sp = !x | !(x ^ (1<<31)); // check if x is 0x0 or 0x80000000
  // if x is a power of 2, subtracting 1 will change the MSB to a 0 and cause the & to fail
  // for the special cases of 0x0 and 0x80000000, we check to make sure result is 0
  int p2 = !(x & z) ^ sp;

    // Copy MSB over to fill with 1s,
    // now finding the minimum number of bits just means couting how many 1s we ahve
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);

    // Create a field to capture pairs of bits
    int a = 0x55;
    a = a | (a << 8);
    a = a | (a << 16);

    // Create a filter to capture groups of 4 bits
    int b = 0x33;
    b = b | (b << 8);
    b = b | (b << 16);

    // Create a filter to capture groups of 8 bits
    int c = 0x0F;
    c = c | (c << 8);
    c = c | (c << 16);

    // Create a filter to capture groups of 16 bits
    int d = 0xFF | (0xFF << 16);

    // Create a filter to capture each half of the int
    int hlf = 0xFF | (0xFF << 8);

    int ones_a = x & a; // Grab even bits
    int ones_b = x & (a << 1); // Grab odd bits
    x = ones_a + (ones_b >> 1); // Add together to get the number of 1s in each pair

    int twos_a = x & b; // even pairs
    int twos_b = x & (b << 2); // odd pairs
    x = twos_a + (twos_b >> 2); // gives number of 1s in each group of 4

    int fours_a = x & c; // even 4s
    int fours_b = x & (c << 4); // odd 4s
    x = fours_a + (fours_b >> 4); // number of 1s in each group of 8

    int eights_a = x & d; // even 8s
    int eights_b = x & (d << 8); // odd 8s
    x = eights_a + (eights_b >> 8); // gives number of 1s in each half

    int halves_a = x & hlf; // lower half
    int halves_b = x & (hlf << 16); // upper half
    x = halves_a + (halves_b >> 16); // gives number of 1s in entire int

    // gives 1 less than the number of bits in most cases, so we add 1.
    // now gives 1 too many bits if x is a power of 2, so subtract 1 if x is a power of 2
    // now gives 1 too few bits if x is 1, so add 1 if x is 1
    // now gives 1 too few bits if x is the minimum value for a signed int, so add 1 if x is min
    return x + 1 + (~p2 + 1) + is1 + isMin;
}
/*
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int isNonZero(int x) {
  int y = x | (~x + 1); // If x is zero, (~x+1) also becomes zero
  // Leftmost bit will always be 1 regardless of sign (or with flipped bits), unless x is zero
  return (y >> 31) & 1;
}
/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  int y = x >> 31; // Will fill 1s if negative, 0s if not
  int p = y & 1; // Need to add 1 if converting from negative to positive
  // If x<0, will invert bits and add 1
  // Otherwise returns x
  return (x ^ y) + p;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  int y = x + ~0; // subtract 1
  int sp = !x | !(x ^ (1<<31)); // check if x is 0x0 or 0x80000000
  // if x is a power of 2, subtracting 1 will change the MSB to a 0 and cause the & to fail
  // for the special cases of 0x0 and 0x80000000, we check to make sure result is 0
  return !(x & y) ^ sp;
}
