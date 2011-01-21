/** @file resources.h
Describes some common functions and variables
*/

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <string>
#include <iostream>
#include <cstring>
#include <cerrno>

// DWORDs
#define DWORDCONST(x)  (x##LL)
#define ONE  DWORDCONST(0x1)

#define BITSINWORD  32
#define BITSINDWORD  64

// Operations with DWORDs
#define HiWORD(a)  ((Word)((a) >> BITSINWORD))
#define LoWORD(a)  ((Word)(a))
#define REVERSEDWORD(a)  (((Dword)REVERSEWORD(LoWORD(a)) << BITSINWORD) | (REVERSEWORD(HiWORD(a))))

// Bit operations with DWORDs
// Bit 0 is the least significant bit
// Bit 63 is the most significant bit
#define GETBIT(a, b)  (((a) >> (b)) & ONE)
#define SETBIT(a, b)  ((a) = (a) | (ONE << (b)))
#define CLRBIT(a, b)  ((a) = (a) & (~(ONE << (b))))
#define PUTBIT(a, b, c)  (((c) == 1) ? SETBIT((a), (b)) : CLRBIT((a), (b)))
#define STIRBITS(a, b, c, d)  { d = 0; for (int ii = 0; ii < (b); ii++) PUTBIT((d), ii, GETBIT((a), (c)[ii])); }
#define MIRROR(a, b, c) { c = 0; for (int ii = 0; ii < (b); ii++) { c <<= 1; c |= (a >> ii) & 1; } }

namespace crypto {
  typedef unsigned int Word;
  typedef unsigned long long Dword;
  typedef unsigned char Byte;
  typedef unsigned short Short;

  enum ALGORITHM_TYPES{BLOWFISH_, DES_, NULL_};
  static const char* STR_BLOWFISH_ = "blowfish";
  static const char* STR_DES_ = "des";
  static const char* STR_NULL_ = "null";

  static const char* IN_FNAME = "doc/in.txt";
  static const char* OUT_FNAME = "doc/out.txt";
  static const char* KEY_FNAME = "doc/key.txt";

  static const unsigned N = 16;
  static const unsigned N_2 = N + 2;
  static const unsigned ROWS = 4, COL = 256;
  static const unsigned S = ROWS * COL;

  inline void logFileOpenError(const std::string& fname) {
    std::cout << "Couldn't open file '" << fname.c_str() << "': " << strerror(errno) << "\n";
  }

  inline void logAlgorithmTypeOutput(const std::string& name) {
    std::cout << "Encrypted algorithm is " << name << "\n";
  }
}
#endif // RESOURCES_H_