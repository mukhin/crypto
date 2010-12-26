/* crypto.cpp */

#include "getopt.h"
#include "blowfish_algorithm.h"

using namespace crypto;

int main(int argc, char **argv) {

  GetOpt* opt = GetOpt::Instance();
  opt->parseArgs(argc, argv);
  opt->printArgs();

  BlowFish* blowfish = new BlowFish(opt->getInputFileName(), opt->getOutputFileName(), opt->getKeyFileName());
  if (opt->isEncrypted())
    blowfish->Encrypt();
  else
    blowfish->Decrypt();
  delete blowfish;
  blowfish = 0;

  GetOpt::Destroy();
  return 0;
}
