## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

SUBDIRS = src

## Define an executable target "cripto", which will be installed into the
## directory named by the predefined variable $(bindir).
bin_PROGRAMS = crypto

## Define the list of source files for the "hello" target. The file extension
## .cpp is recognized by Automake, and causes it to produce rules which invoke
## the C++ compiler to produce an object file (.o) from each source file. The
## header files (.h) do not result in object files by themselves, but will be
## included in distribution archives of the project.
crypto_SOURCES = src/crypto.cpp src/getopt.cpp src/crypto_factory.cpp src/getopt.h src/crypto_factory.h

crypto_LDADD = src/libcrypto/libcrypto.la
crypto_CPPFLAGS = -Isrc/include

## Define an independent executable script for inclusion in the distribution
## archive. It will not be installed on an end user's system, however.
dist_noinst_SCRIPTS = autogen.sh
