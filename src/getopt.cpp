/* getopt.cpp */

#include "getopt.h"

#include <iostream>
#include <stdio.h>
#include <cstdlib> // for the exit(0)

using std::string;

namespace crypto {

  GetOpt* GetOpt::instance = 0;

  GetOpt::GetOpt(): is_encrypted(true) {}
  GetOpt::~GetOpt() {}

  GetOpt* GetOpt::Instance() {
    if (!instance)
      instance = new GetOpt();
    return instance;
  }

  void GetOpt::Destroy() {
    if (instance)
      delete instance;
    instance = 0;
  }

  void GetOpt::parseArgs(int argc, char **argv) {
    int c;
    progName = string(argv[0]);
    while(( c = getopt(argc, argv,"di:o:k:")) != -1) {
      switch(c) {
        case 'd':
          is_encrypted = false;
        break;
        case 'i':
          inputFileName = string(optarg);
        break;
        case 'o':
          outputFileName = string(optarg);
        break;
        case 'k':
          keyFileName = string(optarg);
        break;
        case 'h':
        case '?':
        default:
          printUsage();
      }
    }

    argc -= optind;
    if (argc > 0)
     printUsage();
    argv += optind;
  }

  bool GetOpt::isEncrypted() {
    return is_encrypted;
  }

  const string& GetOpt::getProgName() const {
    return progName;
  }

  const string& GetOpt::getInputFileName() const {
    return inputFileName;
  }

  const string& GetOpt::getOutputFileName() const {
    return outputFileName;
  }

  const string& GetOpt::getKeyFileName() const {
    return keyFileName;
  }

  void GetOpt::printUsage() {
    std::cout << "usage: " << progName
      << " [-d] -i <input file name> -o <output file name> -k <key file name>\n";
    Destroy();
    exit(0);
  }

  void GetOpt::printArgs() {
    std::cout << "\n"
      << " program name: " << progName << "\n"
      << " is encrypted: " << ((is_encrypted) ? "true" : "false") << "\n"
      << " input file name: '" << inputFileName << "'\n"
      << " output file name: '" << outputFileName << "'\n"
      << " key file name: '" << keyFileName << "'\n\n";
  }

} // namespace crypto
