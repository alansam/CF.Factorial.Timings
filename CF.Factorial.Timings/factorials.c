//
//  factorials.c
//  CF.Factorial.Timings
//
//  @see: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
//
//  Created by Alan Sampson on 2/16/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

//  MARK: - Setup and header includes
#include "factorials.h"

//  MARK: - Implementation.
/*
 *  MARK: fact_u64_iterative()
 *
 *  Function to calculate factorials using an iterative method.
 *
 *  Uses the gnu/clang builtin function __builtin_umulll_overflow()
 *  to capture integer overflow conditions.
 */
uint64_t fact_u64_iterative(uint64_t val, bool * oflow) {

  uint64_t fv = 1;
  bool overflow;
  bool overflowed;
  overflow = overflowed = false;

  for (uint64_t i_ = 1; i_ <= val ; ++i_) {
    uint64_t intermediate;
    overflow = __builtin_umulll_overflow(fv, i_, &intermediate);
    overflowed = overflowed ? overflowed : overflow;
    fv = intermediate;
  }

  *oflow = overflowed;

  return fv;
}

/*
 *  MARK: fact_u64_unrolled()
 *
 *  Function to calculate factorials using an unrolled version of the iterative method.
 *
 *  Uses the realization that the maximum factorial that can be stored in a
 *  64-bit unsigned integer is 20! Thus a simple switch can be used to reduce
 *  calculation time.
 */
uint64_t fact_u64_unrolled(uint64_t val, bool * oflow) {

  uint64_t fv = 1;
  bool overflowed;
  overflowed = false;;

  uint64_t ix = 1;
  switch (val) {
    case 20:  /* TODO: max factorial for 64-bit integers */
      fv = fv * ++ix;
    case 19:
      fv = fv * ++ix;
    case 18:
      fv = fv * ++ix;
    case 17:
      fv = fv * ++ix;
    case 16:
      fv = fv * ++ix;
    case 15:
      fv = fv * ++ix;
    case 14:
      fv = fv * ++ix;
    case 13:
      fv = fv * ++ix;
    case 12:  /* TODO: max factorial for 32-bit integers */
      fv = fv * ++ix;
    case 11:
      fv = fv * ++ix;
    case 10:
      fv = fv * ++ix;
    case  9:
      fv = fv * ++ix;
    case  8:
      fv = fv * ++ix;
    case  7:
      fv = fv * ++ix;
    case  6:
      fv = fv * ++ix;
    case  5:
      fv = fv * ++ix;
    case  4:
      fv = fv * ++ix;
    case  3:
      fv = fv * ++ix;
    case  2:
      fv = fv * ++ix;
      break;

    case  1:
      fv = 1;
      break;

    default:
      fv = 0;
      overflowed = true;
      break;
  }

  *oflow = overflowed;

  return fv;
}

/*
 *  MARK: fact_u64_recurse()
 *
 *  Function to calculate factorials using a recursive method.
 *
 *  Uses the gnu/clang builtin function __builtin_umulll_overflow()
 *  to capture integer overflow conditions.
 */
uint64_t fact_u64_recursive(uint64_t val, bool * oflow) {

  static bool overflowed = false;
  uint64_t fv;
  bool overflow;

  if (val >= 1) {
    overflow = __builtin_umulll_overflow(val, fact_u64_recursive(val - 1, oflow), &fv);
    overflowed = overflowed ? overflowed : overflow;
//    fv = val * fact_u64_recursive(val - 1);
  }
  else {
    fv = 1;
  }

  *oflow = overflowed;

  return fv;
}

/*
 *  MARK: fact_u64_tabular()
 *
 *  Function to calculate factorials using a lookup table.
 *
 *  Uses the realization that the maximum factorial that can be stored in a
 *  64-bit unsigned integer is 20! Thus all factorials from 1! to 20! can
 *  be maintained in a 20 element array.
 */
uint64_t fact_u64_tabular(uint64_t val, bool * oflow) {

  static
  uint64_t const factorials[] = {
    /* 0!*/                   0ULL, /* TODO: Added to make picking factorials intuitive */
    /* 1!*/                   1ULL,
    /* 2!*/                   2ULL,
    /* 3!*/                   6ULL,
    /* 4!*/                  24ULL,
    /* 5!*/                 120ULL,
    /* 6!*/                 720ULL,
    /* 7!*/                5040ULL,
    /* 8!*/               40320ULL,
    /* 9!*/              362880ULL,
    /*10!*/             3628800ULL,
    /*11!*/            39916800ULL,
    /*12!*/           479001600ULL, /* TODO: max factorial for 32-bit integers */
    /*13!*/          6227020800ULL,
    /*14!*/         87178291200ULL,
    /*15!*/       1307674368000ULL,
    /*16!*/      20922789888000ULL,
    /*17!*/     355687428096000ULL,
    /*18!*/    6402373705728000ULL,
    /*19!*/  121645100408832000ULL,
    /*20!*/ 2432902008176640000ULL, /* TODO: max factorial for 64-bit integers */
  };
  size_t factorials_c = sizeof(factorials) / sizeof(*factorials);
  uint64_t fv = 0;

  if (val > 0 && val < factorials_c) {
    fv = factorials[val];
    *oflow = false;
  }
  else {
    fv = 0;
    *oflow = true;
  }

  return fv;
}
