
// This script tests implementation of strings
// For this file to work correctly under unix or linux make sure end
// of line character is \n rather than \n


var szSimple = "This is a simple string";
var szEscaped1 = "Escaped characters - new line test\nnext line\twith tab and slash \\";
var szEscaped2 = "double slash \\\\";
var szEscaped3 = "escape sequences \x64\x65\x66";
var szMultilineString = "Helloworld\n\
this is a multiline string\
with more lines";

print (szSimple);
print (szEscaped1);
print (szEscaped2);
print (szEscaped3);
print (szMultilineString);

print ("");


// same as above with single quotes
szTest1 = 'This is a simple string';
szTest2 = 'Escaped characters - new line test\nnext line\twith tab and slash \\';
szTest3 = 'double slash \\\\';
szTest4 = 'Helloworld\n\
this is a multiline string \
with more lines';
szTest5 = "test \n\r \n interpretation of new line characters \r \n";
szTest6 = "test \n\n\r interpretation of new line characters\n\r";
szTest7 = "Quotation test \"Double quotes\" and \'single quotes\' it works!";

print (szTest1);
print (szTest2);
print (szTest3);
print (szTest4);
print (szTest5);
print (szTest6);
print (szTest7);
print ( szTest1.concat("one","two", 3, "four") );
