#!/bin/sh
cd ./testsuite
echo Clearing Results
rm -r result
sleep 1
mkdir result
sleep 1

FILES=*.js

echo Running Tests


# Run programs and generate results
for f in $FILES
do
  node -r ../node2jual.js $f "parm 1" parm2 parm3 > ./result/$f"_expect"
  ../bin/jual $f "parm 1" parm2 parm3 > ./result/$f"_result"
done

# Compare results
for f in $FILES
do
  RRESULT="FAIL"
  diff ./result/$f"_expect" ./result/$f"_result" >/dev/null 2>&1
  if [ $? -eq 0 ]; then
      RRESULT="PASS"
  fi
  echo Result: $RRESULT - $f
done

cd ../
