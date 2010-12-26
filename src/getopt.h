/* getopt.h */

#ifndef GETOPT_H_
#define GETOPT_H_

#include <string>

using std::string;

namespace crypto {

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
    private:
      bool is_encrypted;
      string progName;
      string inputFileName;
      string outputFileName;
      string keyFileName;
      static GetOpt* instance;
  };
} // namespace crypto
#endif // GETOPT_H_