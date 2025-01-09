/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * JiangCan 2019011325
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x) | (~y));
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
  return (x >> (n << 3)) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    int mostSignificantBit = (x >> 31) & 1;     // 提取最高位
    x = x ^ (mostSignificantBit << 31);        // 删除最高位
    x = x >> n;                                // 执行算数右移
    x = x ^ (mostSignificantBit << (32 + (~n))); // 恢复最高位
    return x;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    int mask1, mask2;

    mask1 = 0x55 | (0x55 << 8);
    mask2 = mask1 | (mask1 << 16);
    x = (x & mask2) + ((x >> 1) & mask2);

    mask1 = 0x33 | (0x33 << 8);
    mask2 = mask1 | (mask1 << 16);
    x = (x & mask2) + ((x >> 2) & mask2);

    mask1 = 0x0F | (0x0F << 8);
    mask2 = mask1 | (mask1 << 16);
    x = (x & mask2) + ((x >> 4) & mask2);

    mask2 = 0xFF | (0xFF << 16);
    x = (x & mask2) + ((x >> 8) & mask2);

    mask2 = 0xFF | (0xFF << 8);
    x = (x & mask2) + ((x >> 16) & mask2);

    return x;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    x = ~x;
    x = x & (x >> 16);
    x = x & (x >> 8);
    x = x & (x >> 4);
    x = x & (x >> 2);
    x = x & (x >> 1);
    return x & 1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
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
    x = x >> (n + (~0));
    return (!x) | (!(x + 1));
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
    int roundBias = x & ((1 << n) + (~0));
    return (x >> n) + ((x >> 31) & (1 ^ (!roundBias)));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return (~x) + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    return ((x >> 31) + 1) ^ (!x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int xNegSign = ((x >> 31) & 1) & ((y >> 31) + 1);
    int yNegSign = ((x >> 31) + 1) & ((y >> 31) & 1);
    int sameSign = (((~x) + y + 1) >> 31) + 1;
    return (xNegSign | sameSign) & (1 ^ yNegSign);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  //
  // Instead of counting bits, dimidiated maximum digits.
  // c is for counting digits, x is for dimidiated result.
  //
  int c = 0;
  int r = 0;

  r = ((!(x >> 16)) + (~0)) & 16;
  c = c + r;
  x = x >> r;

  r = ((!(x >> 8)) + (~0)) & 8;
  c = c + r;
  x = x >> r;

  r = ((!(x >> 4)) + (~0)) & 4;
  c = c + r;
  x = x >> r;

  r = ((!(x >> 2)) + (~0)) & 2;
  c = c + r;
  x = x >> r;

  r = ((!(x >> 1)) + (~0)) & 1;
  c = c + r;
  x = x >> r;

  /*
  r = ((!x) + (~0)) & 1;
  c = c + r;
  */

  return c;
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
  if(((~uf) & 0x7F800000) || !(uf & 0x007FFFFF))
  {
    uf = uf ^ (1 << 31);
  }
  return uf;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  //
  // 执行整数到浮点数转换。
  // 使用无符号整数变量 t 和 f 以避免算术位移问题。
  //
  int exponent = 0, shift_amount = 0, carry = 0; // 修改变量名：b -> exponent, s -> shift_amount, c -> carry
  unsigned int result = 0x00000000;
  unsigned int t_copy = x, f_copy = x; // 修改变量名：t -> t_copy, f -> f_copy

  // 如果 x 为负数，则使用绝对值。
  if(x >> 31) {
    result = 0x80000000;
    t_copy = f_copy = (~x) + 1;
  }

  // 计算二进制表示中的位数。
  while(t_copy) {
    exponent = exponent + 1;
    t_copy = t_copy >> 1;
  }
  shift_amount = 24 - exponent;

  // 检查位数损失（精度损失）。
  if(shift_amount < 0) {
    shift_amount = 0;
    while(f_copy >> 25) {
      carry = carry | (f_copy & 1);
      f_copy = f_copy >> 1;
    }
    f_copy = (f_copy >> 1) + (f_copy & (carry | (f_copy >> 1)) & 1);
    if(f_copy >> 24) {
      exponent = exponent + 1;
    }
  }

  // 如果 x 为 0，则使指数位为 0。
  if(!exponent) {
    exponent = -126;
  }

  // 构建浮点数的各个部分并返回结果。
  result = result | ((f_copy << shift_amount) & 0x007FFFFF);
  result = result | ((exponent + 126) << 23);
  return result;
}



/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  // 提取浮点数uf的指数部分
  unsigned exponent = (uf >> 23) & 0xFF;

  // 如果指数部分为0，表示uf为非规格化数（或者0）
  if (!exponent) {
    // 将指数部分设置为最小规格化数的指数值
    exponent = 0xFF;
    // 将uf的符号位保持不变，并将尾数部分左移1位
    uf = (uf & 0x80000000) | (uf << 1);
  }

  // 如果指数部分为254（0xFE），表示uf为无穷大或NaN
  if (!(exponent ^ 0xFE)) {
    // 将指数部分设置为最大规格化数的指数值
    exponent = 0xFF;
    // 将uf的符号位保持不变，并将指数部分左移23位
    uf = (uf & 0x80000000) | (exponent << 23);
  }

  // 如果指数部分不等于255（0xFF），表示uf为规格化数或者非规格化数
  if (exponent ^ 0xFF) {
    // 将uf的尾数部分加上1（尾数加1，相当于浮点数加上2^(-23)）
    uf = uf + (1 << 23);
  }

  return uf;
}
