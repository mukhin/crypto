#!/bin/bash

if [ ! -f `which git` ]; then
  exit 0
elif [ ! -d .git ]; then
  exit 0
fi

VER="1.0";
VER_ARRAY=(1 0)
CURRENT_BRANCH_NAME="$(git describe --all)";

# getting major version from configure.ac
if [ -f configure.ac ]; then
  VER="$(cat configure.ac | grep "AC_INIT(" | sed -e "s:^\s*AC_INIT(\[crypto\],\s\+\[\(.*\)\],.*$:\1:g")";
  IFS=. ; i=0;
  for V in $VER; do
    VER_ARRAY[$i]=$V
    let i++;
  done;
fi

# getting minor version from git
VER="$VER.$(git rev-list HEAD | wc -l).$(git rev-list HEAD -n 1 | head -c 7)";

rm -f version.h

cat <<EOF > version.h
#ifndef CRYPTO_VERSION_H__
#define CRYPTO_VERSION_H__

#define CRYPTO_VERSION_MAJ ${VER_ARRAY[0]}
#define CRYPTO_VERSION_MIN ${VER_ARRAY[1]}

#define CRYPTO_VERSION "$VER"

#define CURRENT_BRANCH_NAME "$CURRENT_BRANCH_NAME"

#endif //CRYPTO_VERSION_H__

EOF
