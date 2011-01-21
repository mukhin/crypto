/** @file crypto.cpp */

#include "crypto_factory.h"
#include "getopt.h"
#include "blowfish_algorithm.h"
#include "des_algorithm.h"
#include "version.h"

using namespace crypto;

int main(int argc, char **argv) {

  std::cout << "crypto v." << CRYPTO_VERSION << " is started\n";

  GetOpt* opt = GetOpt::Instance();
  opt->parseArgs(argc, argv);
  opt->printArgs();

  CryptoFactory* factory = CryptoFactory::Instance();
  factory->Init(opt->getInputFileName(), opt->getOutputFileName(), opt->getKeyFileName());
  BaseCrypto* crypto = factory->getCryptoInstance(opt->getAlgorithmType().type);

  if (crypto) {
    if (opt->isEncrypted())
      crypto->Encrypt();
    else
      crypto->Decrypt();
    delete crypto;
    crypto = 0;
  }

  CryptoFactory::Destroy();

  GetOpt::Destroy();

  std::cout << "crypto is done\n";
  return 0;
}


