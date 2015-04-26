// This file tests the sample module for JualScript

sztst="This sentence will be reversed";

// if using the global namespace no need to assign to a variable
require("samplemod")
szResult = myfunc(sztst);
print(szResult);
print(myword);
print(mynum);


// if assigning to a namespace uncomment line below and
// comment out section above
/*
var mylib = require("samplemod");
szResult = mylib.myfunc(sztst);
print(szResult);
print(mylib.myword);
print(mylib.num);

*/


