
// This script tests implementation of comments

/* This is a multi line comment test
Hello world
print("ERROR0");
*/

var myVar = 1234567; // This is a single line test

/* multiline test to see if variable is redefined
myVar = "ERROR1";
*/

// myVar = "ERROR2"; // should not reach here

print(myVar /* Bad form but should work*/ );
print("/* YES1 */" /* More bad form but should work */ );
print( /* More bad form but should work */ "/* YES2 */" );
print( "\r\n YES3 \\" );
