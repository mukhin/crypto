
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