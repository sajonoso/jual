@echo off
echo Making jual and jualc
cd src
call 1_make.cmd

echo Making sample module
cd modsample
call 1_make.cmd

echo Making inet module
cd ../inet
call 1_make.cmd


echo Making uint8array module
cd ../uint8array
call 1_make.cmd

echo Making sqlite module
cd ../sqlite
call 1_make.cmd

cd ../../