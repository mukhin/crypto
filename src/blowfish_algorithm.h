#ifndef BLOWFISH_ALGORITHM_H_
#define BLOWFISH_ALGORITHM_H_

#include "basecrypto_algorithm.h"
#include "resources.h"

#include <string>

using std::string;

namespace crypto {

  class BlowFish: public BaseCrypto {
    public:
      BlowFish();
      BlowFish(string inputFN, string outputFN, string keyFN);
      virtual ~BlowFish();
      void Encrypt();
      void Decrypt();

    private:
      void initSubKeys();
      void Process(void (*Func)(unit32&, unit32&, unit32 [N_2], unit32 [ROWS][COL]));
      static void Enc(unit32& left, unit32& right, unit32 P[N_2], unit32 SBox[ROWS][COL]);
      static void Dec(unit32& left, unit32& right, unit32 P[N_2], unit32 SBox[ROWS][COL]);
      static unit32 F(unit32 x, unit32 SBox[ROWS][COL]);

    private:
      unit32 P[N_2];
      unit32 SBox[ROWS][COL];
  };
}

#endif //BLOWFISH_ALGORITHM_H_
