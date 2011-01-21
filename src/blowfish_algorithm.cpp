/** @file blowfish_algorithm.cpp */

#include "blowfish_algorithm.h"
#include "blowfish_sboxes.h"

#include <string>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;
using std::string;

namespace crypto {

  BlowFish::BlowFish(): BaseCrypto() {}

  BlowFish::BlowFish(string inFN, string outFN, string keyFN): BaseCrypto(inFN, outFN, keyFN) {}

  BlowFish::~BlowFish() {}

  void BlowFish::Init() {
    int i, j, k, cnt = 0;
    for (int i = 0; i < N + 2; ++i) {
      P[cnt] = SBOX_INITIALIZER[cnt];
      ++cnt;
    }

    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COL; ++j) {
        SBox[i][j] = SBOX_INITIALIZER[cnt];
        ++cnt;
      }
    }

    j = 0;
    for (i = 0; i < N + 2; ++i) {
      Word data = 0;
      for (k = 0; k < ROWS; ++k) {
        if (j >= getKey().length()) {
          j = 0;
        }
        data = (data << 8) | getKey()[j];
        ++j;
      }
      P[i] ^= data;
    }

    Dword dwValue = 0;

    for (i = 0; i < N + 2; i += 2) {
      Crypt(dwValue, true);
      P[i] = HiWORD(dwValue);
      P[i + 1] = LoWORD(dwValue);
    }

    for (i = 0; i < ROWS; ++i) {
      for (j = 0; j < COL; j += 2) {
        Crypt(dwValue, true);
        SBox[i][j] = HiWORD(dwValue);
        SBox[i][j + 1] = LoWORD(dwValue);
      }
    }
  }

  void BlowFish::Crypt(Dword& dwValue, bool fgDirection) {
    Word rPart = LoWORD(dwValue);
    Word lPart = HiWORD(dwValue);
    Word tPart = 0;

    for (int i = 0; i < N; ++i) {
      if (fgDirection) {
        lPart ^= P[i];
      }
      else {
        lPart ^= P[N + 1 - i];
      }
      rPart ^= F(lPart);

      tPart = lPart;
      lPart = rPart;
      rPart = tPart;
    }

    tPart = lPart;
    lPart = rPart;
    rPart = tPart;

    if (fgDirection) {
      rPart ^= P[N];
      lPart ^= P[N + 1];
    }
    else {
      rPart ^= P[1];
      lPart ^= P[0];
    }

    dwValue = (static_cast<Dword>(lPart) << BITSINWORD) | rPart;
  }

  Word BlowFish::F(Word x) {
    Word f, a, b, c, d;

    a = x & 0x00FF;
    x >>= 8;
    b = x & 0x00FF;
    x >>= 8;
    c = x & 0x00FF;
    x >>= 8;
    d = x & 0x00FF;

    f = SBox[0][a] + SBox[1][b];
    f ^= SBox[2][c];
    f += SBox[3][d];

    return f;
  }
}