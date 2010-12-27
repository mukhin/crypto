/* crypto.cpp */

#include "getopt.h"
#include "blowfish_algorithm.h"

using namespace crypto;

int main(int argc, char **argv) {

  GetOpt* opt = GetOpt::Instance();
  opt->parseArgs(argc, argv);
  opt->printArgs();

  BaseCrypto* crypto = new BlowFish(opt->getInputFileName(), opt->getOutputFileName(), opt->getKeyFileName());
  if (opt->isEncrypted())
    crypto->Encrypt();
  else
    crypto->Decrypt();
  delete crypto;
  crypto = 0;

  GetOpt::Destroy();
  return 0;
}
