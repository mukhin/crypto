/** @file des_algorithm.cpp */

#include "des_algorithm.h"
#include "des_sboxes.h"

#include <string>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;
using std::string;

namespace crypto {

  Des::Des(): BaseCrypto() {}

  Des::Des(string inFN, string outFN, string keyFN): BaseCrypto(inFN, outFN, keyFN) {}

  Des::~Des() {}

  void Des::Init() {
    string key = getKey();
    key.resize(sizeof(dwMaster));
    memcpy(&dwMaster, key.data(), sizeof(dwMaster));

    Dword c = 0;
    Dword d = 0;
    for (int k = 0; k < 28; k++) {
      PUTBIT(c, k, GETBIT(dwMaster, bPC1[k]));
      PUTBIT(d, k, GETBIT(dwMaster, bPC1[k + 28]));
    }
    for (int q = 0; q < 16; q++) {
      c = (c >> bShift[q]) | ((c & wMask[q]) << (28 - bShift[q]));
      d = (d >> bShift[q]) | ((d & wMask[q]) << (28 - bShift[q]));
      Dword t = ((Dword)d << 28) | c;
      STIRBITS(t, 48, bPC2, dwKey[q]);
    }
    c = d = 0;
  }

  void Des::Crypt(Dword& dwValue, bool fgDirection) {
    Dword a;
    Dword b;
    Dword dwData;

    SetValue(dwValue, dwData);

    STIRBITS(dwData, BITSINDWORD, bIP1, a);
    Word r = HiWORD(a);
    Word l = LoWORD(a);
    Word s;
    for (int i = 0; i < 16; i++) {
      STIRBITS(r, 48, bE, a);
      if (fgDirection) {
        b = a ^ dwKey[15 - i];
      }
      else {
        b = a ^ dwKey[i];
      }
      a = 0;
      for (int j = 0; j < 8; j++) {
        a <<= 4;
        a |= bS[j][(b >> ((7 - j) * 6)) & 0x3f];
      }
      STIRBITS(a, BITSINWORD, bP, b);

      s = r;
      r = l ^ LoWORD(b);
      l = s;
    }
    a = ((Dword)l << BITSINWORD) | r;
    STIRBITS(a, BITSINDWORD, bIP2, dwData);
    a = b = l = r = 0; // Cleanup
    SetValue(dwData, dwValue);
  }

  void Des::SetValue(const Dword& dwValue, Dword& dwData) {
    MIRROR(dwValue, BITSINDWORD, dwData);
  }
}