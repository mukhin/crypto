/** @file basecrypto_algorithm.h */

#ifndef BASECRYPTO_ALGORITHM_H_
#define BASECRYPTO_ALGORITHM_H_

#include "resources.h"

#include <string>

using std::string;

namespace crypto {

  /** Base abstract class for the crypto algorithms realizations */
  class BaseCrypto {
    public:
      /** Constructor */
      BaseCrypto();
      /** Constructor with parameters
      @param inputFN incoming file name
      @param outputFN output file name
      @param key file name */
      BaseCrypto(string inputFN, string outputFN, string keyFN);
      /** Destructor */
      virtual ~BaseCrypto()=0;
      /** Encryption function (Process(true) wrapper)*/
      void Encrypt();
      /** Decryption function (Process(false) wrapper)*/
      void Decrypt();
      /** Some initialization might be empty*/
      virtual void Init()=0;

      /* Some getters */
      const string& getInputFileName() const;
      const string& getOutputFileName() const;
      const string& getKeyFileName() const;
      const string& getKey() const;

    protected:
      /** ECB encryption process
      @param fgDirection true = decrypt, false = encrypt */
      void Process(bool fgDirection);
    private:
      /** Read master key from file */
      void readKey();
      /** Crypto function
      @param dwValue incoming block
      @param fgDirection true = decrypt, false = encrypt */
      virtual void Crypt(Dword& dwValue, bool fgDirection)=0;

    private:
      string inputFileName;
      string outputFileName;
      string keyFileName;
      string key;
  };
}

#endif //BASECRYPTO_ALGORITHM_H_
