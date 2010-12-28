/** @file getopt.h */

#ifndef GETOPT_H_
#define GETOPT_H_

#include "resources.h"
#include <string>

using std::string;

namespace crypto {

  /** Algorithm description structure. Singleton */
  struct AlgorithmType {
    /** algorithm name */
    string name;
    /** algorithm type @see ALGORITHM_TYPES */
    ALGORITHM_TYPES type;
    /** Constructor */
    AlgorithmType(): name(STR_NULL_), type(NULL_){}
  };

  /** Incoming program arguments parser */
  class GetOpt {
    private:
      /** Constructor */
      GetOpt();
      /** Destructor */
      ~GetOpt();
    public:
      static GetOpt* Instance();
      static void Destroy();
      /** Incoming arguments parser */
      void parseArgs(int argc, char **argv);
      /** Show help */
      void printUsage();
      /** Show incoming arguments */
      void printArgs();

      /* Some getters */
      bool isEncrypted();
      const string& getProgName() const;
      const string& getInputFileName() const;
      const string& getOutputFileName() const;
      const string& getKeyFileName() const;
      const AlgorithmType& getAlgorithmType() const;
    private:
      /** Define algorithm type by name */
      void fillAlgorithmType();
    private:
      bool is_encrypted;
      string progName;
      string inputFileName;
      string outputFileName;
      string keyFileName;
      AlgorithmType algorithmType;
    private:
      static GetOpt* instance;
  };
} // namespace crypto
#endif // GETOPT_H_