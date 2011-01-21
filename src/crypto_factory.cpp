/** @file crypto_factory.cpp */

#include "crypto_factory.h"
#include "blowfish_algorithm.h"
#include "des_algorithm.h"
#include "basecrypto_algorithm.h"

using std::map;
using std::pair;

namespace crypto {

  CryptoFactory*  CryptoFactory::instance = 0;

  CryptoFactory::CryptoFactory() {}

  BaseCrypto* CryptoFactory::getCryptoInstance(ALGORITHM_TYPES id) const {
    InstantiatorMap::const_iterator itr = m_instantiatorMap.find(id);
    if (itr != m_instantiatorMap.end()) {
      return (*itr).second;
    }
    return 0;
  }

  void CryptoFactory::registerCryptoInstantiator(ALGORITHM_TYPES id, BaseCrypto* alg) {
    m_instantiatorMap.insert(pair<ALGORITHM_TYPES, BaseCrypto*>(id, alg));
  }

  CryptoFactory* CryptoFactory::Instance() {
    if (!instance) {
      instance = new CryptoFactory();
    }
    return instance;
  }

  void CryptoFactory::Init(string inputFN, string outputFN, string keyFN) {
    CryptoFactory::registerCryptoInstantiator(BLOWFISH_,
      new BlowFish(inputFN, outputFN, keyFN));
    CryptoFactory::registerCryptoInstantiator(DES_,
      new Des(inputFN, outputFN, keyFN));
    CryptoFactory::registerCryptoInstantiator(NULL_, 0);
  }

  void CryptoFactory::Destroy() {
    if (instance) {
      InstantiatorMap::iterator itr = instance->m_instantiatorMap.begin();
      while (itr != instance->m_instantiatorMap.end()) {
        BaseCrypto* crypto = (*itr).second;
        if (crypto)
          delete crypto;
        ++itr;
      }
      delete instance;
    }
    instance = 0;
  }
}
