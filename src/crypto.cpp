/** @file crypto.cpp */

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

  BaseCrypto* crypto = 0;
  switch (opt->getAlgorithmType().type) {
    case BLOWFISH_:
      crypto = new BlowFish(opt->getInputFileName(), opt->getOutputFileName(), opt->getKeyFileName());
    break;
    case DES_:
      crypto = new Des(opt->getInputFileName(), opt->getOutputFileName(), opt->getKeyFileName());
    default: break;
  }

  if (crypto) {
    if (opt->isEncrypted())
      crypto->Encrypt();
    else
      crypto->Decrypt();
    delete crypto;
    crypto = 0;
  }

  GetOpt::Destroy();

  std::cout << "crypto is done\n";
  return 0;
}
