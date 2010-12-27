#ifndef DESSBOXES_H_
#define DESSBOXES_H_

#include "resources.h"

#include <string>
#include <iostream>
#include <cstring>
#include <cerrno>

namespace crypto {
  static const Byte bS[][64] = {
    {
      11, 14,  5,  0,  6,  9, 10, 15,  1,  2, 12,  5, 13,  7,  3, 10,
       4, 13,  9,  6, 15,  3,  0, 12,  2,  8,  7, 11,  8,  4, 14,  1,
       8,  4,  3, 15,  5,  2,  0, 12, 11,  7,  6,  9, 14,  1,  9,  6,
      15,  8, 10,  3, 12,  5,  7, 10,  1, 14, 13,  0,  2, 11,  4, 13
    },
    {
      2,  8, 12,  5, 15,  3, 10,  0,  4, 13,  9,  6,  1, 14,  6,  9,
     13,  2,  3, 15,  0, 12,  5, 10,  7, 11, 14,  1, 11,  7,  8,  4,
     11,  6,  7,  9,  2,  8,  4,  7, 13, 11, 10,  0,  8,  5,  1, 12,
      0, 13, 12, 10,  9,  2, 15,  4, 14,  1,  3, 15,  5, 14,  6,  3
    },
    {
      3,  9,  0, 14,  9,  4,  7,  8,  5, 15, 12,  2,  6,  3, 10, 13,
      8,  7, 11,  0,  4,  1, 14, 11, 15, 10,  2,  5,  1, 12, 13,  6,
      5,  2,  6, 13, 14,  9,  0,  6,  2,  4, 11,  8,  9, 15, 12,  1,
     15, 12,  8,  7,  3, 10, 13,  0,  4,  3,  7, 14, 10,  5,  1, 11
    },
    {
      4,  2,  1, 15, 14,  5, 11,  6,  2,  8, 12,  3, 13, 14,  7,  0,
      3,  4, 10,  9,  5, 11,  0, 12,  8, 13, 15, 10,  6,  1,  9,  7,
      7, 13, 10,  6,  2,  8, 12,  5,  4,  3, 15,  0, 11,  4,  1, 10,
     13,  1,  0, 15, 14,  7,  9,  2,  3, 14,  5,  9,  8, 11,  6, 12
    },
    {
     14,  5,  8, 15,  0,  3, 13, 10,  7,  9,  1, 12,  9, 14,  2,  1,
     11,  6,  4,  8,  6, 13,  3,  4, 12,  0, 10,  7,  5, 11, 15,  2,
     11, 12,  2,  9,  6,  5,  8,  3, 13,  0,  4, 10,  0, 11,  7,  4,
      1, 15, 14,  2, 15,  8,  5, 14, 10,  6,  3, 13, 12,  1,  9,  7
    },
    {
      5, 11,  8, 13,  6,  1, 13, 10,  9,  2,  3,  4, 15, 12,  4,  7,
      0,  6, 11,  8, 12, 15,  2,  5,  7,  9, 14,  3, 10,  0,  1, 14,
     11,  8,  4,  2, 12,  6,  3, 13,  0, 11, 10,  7,  6,  1, 15,  4,
     14,  5,  1, 15,  2,  9, 13, 10,  9,  0,  7, 12,  5, 14,  8,  3
    },
    {
     15,  0,  9, 10,  6,  5,  3,  9,  1, 14,  4,  3, 12, 11, 10,  4,
      8,  7, 14,  1, 13,  2,  0, 12,  7, 13, 11,  6,  2,  8,  5, 15,
     12, 11,  3, 13, 15, 12,  6,  0,  2,  5,  8, 14,  1,  2, 13,  7,
     11,  1,  0,  6,  4, 15,  9, 10, 14,  8,  5,  3,  7,  4, 10,  9
    },
    {
      7,  2, 12, 15,  4, 11, 10, 12, 11,  7,  6,  9, 13,  4,  0, 10,
      2,  8,  5,  3, 15,  6,  9,  5,  8,  1,  3, 14,  1, 13, 14,  0,
      0, 15,  5, 10,  7,  2,  9,  5, 14,  1,  3, 12, 11,  8, 12,  6,
     15,  3,  6, 13,  4,  9, 10,  0,  2,  4, 13,  7,  8, 14,  1, 11
    }
  };

  static const Word wMask[] = { 1, 1, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1 };

  static const Byte bShift[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

  // Table for key permutation
  static const Byte bPC1[] = {
    56, 48, 40, 32, 24, 16,  8,
     0, 57, 49, 41, 33, 25, 17,
     9,  1, 58, 50, 42, 34, 26,
    18, 10,  2, 59, 51, 43, 35,
    62, 54, 46, 38, 30, 22, 14,
     6, 61, 53, 45, 37, 29, 21,
    13,  5, 60, 52, 44, 36, 28,
    20, 12,  4, 27, 19, 11,  3};

  // Table for compression permutation
  static const Byte bPC2[] = {
    13, 16, 10, 23,  0,  4,
     2, 27, 14,  5, 20,  9,
    22, 18, 11,  3, 25,  7,
    15,  6, 26, 19, 12,  1,
    40, 51, 30, 36, 46, 54,
    29, 39, 50, 44, 32, 47,
    43, 48, 38, 55, 33, 52,
    45, 41, 49, 35, 28, 31
  };

  // Table for initial permutation IP
  static const Byte bIP1[] = {
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7,
    56, 48, 40, 32, 24, 16,  8,  0,
    58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6
  };

  // Table for final permutation IP
  static const Byte bIP2[] = {
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25,
    32,  0, 40,  8, 48, 16, 56, 24
  };

  // Table for expansion permutation
  static const Byte bE[] = {
    31,  0,  1,  2,  3,  4,
     3,  4,  5,  6,  7,  8,
     7,  8,  9, 10, 11, 12,
    11, 12, 13, 14, 15, 16,
    15, 16, 17, 18, 19, 20,
    19, 20, 21, 22, 23, 24,
    23, 24, 25, 26, 27, 28,
    27, 28, 29, 30, 31,  0
  };

  // Table for P-Box permutation
  static const Byte bP[] = {
    15,  6, 19, 20, 28, 11, 27, 16,
     0, 14, 22, 25,  4, 17, 30,  9,
     1,  7, 23, 13, 31, 26,  2,  8,
     18, 12, 29,  5, 21, 10,  3, 24
  };
}
#endif // DESSBOXES_H_