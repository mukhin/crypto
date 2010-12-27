#ifndef BASECRYPTO_ALGORITHM_H_
#define BASECRYPTO_ALGORITHM_H_

#include "resources.h"

#include <string>

using std::string;

namespace crypto {

  class BaseCrypto {
    public:
      BaseCrypto();
      BaseCrypto(string inputFN, string outputFN, string keyFN);
      virtual ~BaseCrypto();
      virtual void Encrypt()=0;
      virtual void Decrypt()=0;
      const string& getInputFileName() const;
      const string& getOutputFileName() const;
      const string& getKeyFileName() const;
      const string& getKey() const;

    private:
      void readKey();

    private:
      string inputFileName;
      string outputFileName;
      string keyFileName;
      string key;
  };
}

#endif //BASECRYPTO_ALGORITHM_H_
