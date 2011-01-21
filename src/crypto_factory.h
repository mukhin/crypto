/** @file crypto_factory.h */

#ifndef CRYPTO_FACTORY_H_
#define CRYPTO_FACTORY_H_

#include "blowfish_algorithm.h"
#include "des_algorithm.h"
#include "basecrypto_algorithm.h"

#include <map>

using std::map;
using std::pair;

/** A factory class for the crypto algorithm objects constructing */
namespace crypto {
  class CryptoFactory {
    typedef std::map<ALGORITHM_TYPES, BaseCrypto*> InstantiatorMap;
    CryptoFactory();
    public:
      static CryptoFactory* Instance();
      static void Destroy();
      void Init(string inputFN, string outputFN, string keyFN);
      BaseCrypto* getCryptoInstance(ALGORITHM_TYPES id);
      void registerCryptoInstantiator(ALGORITHM_TYPES id, BaseCrypto* alg);
    private:
      InstantiatorMap m_instantiatorMap;
      static CryptoFactory* instance;
  };
}

#endif //CRYPTO_FACTORY_HPP_