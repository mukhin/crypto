#!/bin/sh

./autogen.sh
./configure
./version.sh
make clean && make

exit 0

