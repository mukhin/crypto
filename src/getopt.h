/* getopt.h */

#ifndef GETOPT_H_
#define GETOPT_H_

#include "resources.h"
#include <string>

using std::string;

namespace crypto {

  struct AlgorithmType {
    string name;
    ALGORITHM_TYPES type;
    AlgorithmType(): name(STR_NULL_), type(NULL_){}
  };

  class GetOpt {
    private:
      GetOpt();
      ~GetOpt();
    public:
      static GetOpt* Instance();
      static void Destroy();
      void parseArgs(int argc, char **argv);
      void printUsage();
      void printArgs();
      bool isEncrypted();
      const string& getProgName() const;
      const string& getInputFileName() const;
      const string& getOutputFileName() const;
      const string& getKeyFileName() const;
      const AlgorithmType& getAlgorithmType() const;
    private:
      void fillAlgorithmType();
    private:
      bool is_encrypted;
      string progName;
      string inputFileName;
      string outputFileName;
      string keyFileName;
      AlgorithmType algorithmType;
      static GetOpt* instance;
  };
} // namespace crypto
#endif // GETOPT_H_