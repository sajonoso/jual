#!/bin/sh
echo "Making jual and jualc"
cd src
./1_make.sh

echo "Making sample module"
cd modsample
./1_make.sh

echo "Making inet module"
cd ../inet
./1_make.sh

echo "Making uint8array module"
cd ../uint8array
./1_make.sh

echo "Making sqlite module"
cd ../sqlite
./1_make.sh

cd ../../