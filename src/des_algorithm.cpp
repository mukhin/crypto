
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

  Des::Des(): BaseCrypto() {
    initSubKeys();
  }

  Des::Des(string inFN, string outFN, string keyFN): BaseCrypto(inFN, outFN, keyFN) {
    initSubKeys();
  }

  Des::~Des() {}

  void Des::Process(bool fgDirection) {
    ifstream inputFile(getInputFileName().c_str(), ifstream::binary);
    if (inputFile.good()) {
      ofstream outputFile(getOutputFileName().c_str(), ofstream::binary);
      if (outputFile.good()) {
        Dword dwValue = 0;
        while(inputFile.good()) {
          dwValue = 0;
          inputFile.read(reinterpret_cast<char*>(&dwValue), sizeof(dwValue));
          if(inputFile.good()
            || (!inputFile.good() && dwValue > 0)) {
            SetValue(dwValue);
            Crypt(fgDirection);
            SetValue(dwData, dwResult);
            outputFile.write(reinterpret_cast<char*>(&dwResult), sizeof(dwResult));
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

  void Des::Encrypt() {
    Process(true);
  }

  void Des::Decrypt() {
    Process(false);
  }

  void Des::initSubKeys() {
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

  void Des::Crypt(bool fgDirection) {
    Dword a;
    Dword b;

    STIRBITS(dwData, 64, bIP1, a);
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
      STIRBITS(a, 32, bP, b);

      s = r;
      r = l ^ LoWORD(b);
      l = s;
    }
    a = ((Dword)l << 32) | r;
    STIRBITS(a, 64, bIP2, dwData);
    a = b = l = r = 0; // Cleanup
  }

  void Des::SetValue(const Dword& dwValue) {
    MIRROR(dwValue, 64, dwData);
  }

  void Des::SetValue(const Dword& dwValue, Dword& dwData) {
    MIRROR(dwValue, 64, dwData);
  }

  Dword Des::GetValue() {
    MIRROR(dwData, 64, dwResult);
    return dwResult;
  }
}