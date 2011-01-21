/** @file des_algorithm.h */

#ifndef DES_ALGORITHM_H_
#define DES_ALGORITHM_H_

#include "basecrypto_algorithm.h"
#include "resources.h"

#include <string>

using std::string;

namespace crypto {
  /** Des algorithm realization */
  class Des: public BaseCrypto {
    public:
      /** Constructor */
      Des();
      /** Constructor with parameters
      @param inputFN incoming file name
      @param outputFN output file name
      @param key file name */
      Des(string inputFN, string outputFN, string keyFN);
      /** Destructor */
      ~Des();
      /** Init sub keys */
      void Init();

    private:
      /** Crypto function
      @param dwValue incoming block
      @param fgDirection true = decrypt, false = encrypt */
      void Crypt(Dword& dwValue, bool fgDirection);

      void SetValue(const Dword& src, Dword& dst);

    private:
      /** Master key */
      Dword dwMaster;
      /** Subkeys */
      Dword dwKey[16];
  };
}

#endif //DES_ALGORITHM_H_
