/** @file blowfish_algorithm.h */

#ifndef BLOWFISH_ALGORITHM_H_
#define BLOWFISH_ALGORITHM_H_

#include "basecrypto_algorithm.h"
#include "resources.h"

#include <string>

using std::string;

namespace crypto {

  /** Blowfish algorithm realization */
  class BlowFish: public BaseCrypto {
    public:
      /** Constructor */
      BlowFish();
      /** Constructor with parameters
      @param inputFN incoming file name
      @param outputFN output file name
      @param key file name */
      BlowFish(string inputFN, string outputFN, string keyFN);
      /** Destructor */
      ~BlowFish();

    private:
      /** Init sub keys */
      void initSubKeys();
      /** Crypto function
      @param dwValue incoming block
      @param fgDirection true = decrypt, false = encrypt */
      void Crypt(Dword& dwValue, bool fgDirection);
      /** F-function */
      Word F(Word x);

    private:
      /** Subkeys */
      Word P[N_2];
      /** SBoxes */
      Word SBox[ROWS][COL];
  };
}

#endif //BLOWFISH_ALGORITHM_H_
