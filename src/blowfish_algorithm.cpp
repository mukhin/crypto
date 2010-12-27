
#include "blowfish_algorithm.h"
#include "resources.h"

#include <string>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;
using std::string;

namespace crypto {

  BlowFish::BlowFish(): BaseCrypto() {
    initSubKeys();
  }

  BlowFish::BlowFish(string inFN, string outFN, string keyFN): BaseCrypto(inFN, outFN, keyFN) {
    initSubKeys();
  }

  BlowFish::~BlowFish() {}

  void BlowFish::Process(void (*Func)(unit32&, unit32&, unit32 [N_2], unit32 [ROWS][COL])) {
    ifstream inputFile(getInputFileName().c_str(), ifstream::binary);
    if (inputFile.good()) {
      ofstream outputFile(getOutputFileName().c_str(), ofstream::binary);
      if (outputFile.good()) {
        uint64 buffer;
        while(inputFile.good()) {
          memset(&buffer, 0, sizeof(buffer));
          inputFile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
          if(inputFile.good()
            || (!inputFile.good() && (buffer.left != 0 || buffer.right != 0))) {
            Func(buffer.left, buffer.right, P, SBox);
            outputFile.write(reinterpret_cast<char*>(&buffer), sizeof(buffer));
          }
        }
        outputFile.close();
      }
      else {
        logFileOpenError(getOutputFileName());
      }
      inputFile.close();
    }
    else {
      logFileOpenError(getInputFileName());
    }
  }

  void BlowFish::Encrypt() {
    Process(Enc);
  }

  void BlowFish::Decrypt() {
    Process(Dec);
  }

  void BlowFish::initSubKeys() {
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
      unit32 data = 0;
      for (k = 0; k < ROWS; ++k) {
        if (j >= getKey().length()) {
          j = 0;
        }
	data = (data << 8) | getKey()[j];
        ++j;
      }
      P[i] ^= data;
    }

    unit32 lData = 0;
    unit32 rData = 0;

    for (i = 0; i < N + 2; i += 2) {
      Enc(lData, rData, P, SBox);
      P[i] = lData;
      P[i + 1] = rData;
    }

    for (i = 0; i < ROWS; ++i) {
      for (j = 0; j < COL; j += 2) {
        Enc(lData, rData, P, SBox);
        SBox[i][j] = lData;
        SBox[i][j + 1] = rData;
      }
    }
  }

  void BlowFish::Enc(unit32 &left, unit32 &right, unit32 P[N_2], unit32 SBox[ROWS][COL]) {
    unit32  lPart, rPart, tPart;

    lPart = left;
    rPart = right;

    for (int i = 0; i < N; ++i) {
      lPart ^= P[i];
      rPart ^= F(lPart, SBox);

      tPart = lPart;
      lPart = rPart;
      rPart = tPart;
    }

    tPart = lPart;
    lPart = rPart;
    rPart = tPart;

    rPart ^= P[N];
    lPart ^= P[N + 1];

    left = lPart;
    right = rPart;
  }

  void BlowFish::Dec(unit32 &left, unit32 &right, unit32 P[N_2], unit32 SBox[ROWS][COL]) {
    unit32  lPart, rPart, tPart;

    lPart = left;
    rPart = right;

    for (int i = N + 1; i > 1; --i) {
      lPart ^= P[i];
      rPart ^= F(lPart, SBox);

      tPart = lPart;
      lPart = rPart;
      rPart = tPart;
    }

    tPart = lPart;
    lPart = rPart;
    rPart = tPart;

    rPart ^= P[1];
    lPart ^= P[0];

    left = lPart;
    right = rPart;
  }

  unit32 BlowFish::F(unit32 x, unit32 SBox[ROWS][COL]) {
    unit32 f, a, b, c, d;

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