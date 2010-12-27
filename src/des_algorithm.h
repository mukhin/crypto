#ifndef DES_ALGORITHM_H_
#define DES_ALGORITHM_H_

#include "basecrypto_algorithm.h"
#include "resources.h"

#include <string>

using std::string;

namespace crypto {

  class Des: public BaseCrypto {
    public:
      Des();
      Des(string inputFN, string outputFN, string keyFN);
      ~Des();
      void Encrypt();
      void Decrypt();

    private:
      void initSubKeys();
      /** ECB encryption process
      @param fgDirection true = decrypt, false = encrypt */
      void Process(bool fgDirection);

      /** Crypt function
      @param fgDirection true = decrypt, false = encrypt */
      void Crypt(bool fgDirection);

      void SetValue(const Dword& dwValue);
      void SetValue(const Dword& src, Dword& dst);
      Dword GetValue();

    private:
      /** Master key */
      Dword dwMaster;
      /** Subkeys */
      Dword dwKey[16];
      /** 64-bit Block of the plain text */
      Dword dwData;
      /** 64-bit Block of the cipher text */
      Dword dwResult;
  };
}

#endif //DES_ALGORITHM_H_
