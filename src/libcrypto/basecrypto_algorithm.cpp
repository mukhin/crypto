/** @file basecrypto_algorithm.cpp */

#include "basecrypto_algorithm.h"
#include "resources.h"

#include <string>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;
using std::string;

namespace crypto {

  BaseCrypto::BaseCrypto(): inputFileName(IN_FNAME), outputFileName(OUT_FNAME), keyFileName(KEY_FNAME) {
    readKey();
  }

  BaseCrypto::BaseCrypto(string inFN, string outFN, string keyFN):
    inputFileName(IN_FNAME), outputFileName(OUT_FNAME), keyFileName(KEY_FNAME) {
    if (inFN.length())
      inputFileName = inFN;
    if (outFN.length())
      outputFileName = outFN;
    if (keyFN.length())
      keyFileName = keyFN;
    readKey();
  }

  BaseCrypto::~BaseCrypto() {}

  void BaseCrypto::readKey() {
    ifstream keyFile(keyFileName.c_str(), std::ifstream::binary);
    if (keyFile.good()) {
      typedef istreambuf_iterator<char> iter;
      key = string((iter(keyFile)), iter());
      keyFile.close();
    }
    else {
      logFileOpenError(keyFileName);
    }
  }

  void BaseCrypto::Process(bool fgDirection) {
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
            Crypt(dwValue, fgDirection);
            outputFile.write(reinterpret_cast<char*>(&dwValue), sizeof(dwValue));
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

  void BaseCrypto::Encrypt() {
    Process(true);
  }

  void BaseCrypto::Decrypt() {
    Process(false);
  }

  const string& BaseCrypto::getInputFileName() const {
    return inputFileName;
  }

  const string& BaseCrypto::getOutputFileName() const {
    return outputFileName;
  }

  const string& BaseCrypto::getKeyFileName() const {
    return keyFileName;
  }

  const string& BaseCrypto::getKey() const {
    return key;
  }
}