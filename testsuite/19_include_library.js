
// This file tests the ability to include a library

eval(includeJS("../lib/common.js"));

print("result: " + isNum("J") + " " + isNum("0"));

print(GLOBALVAL);