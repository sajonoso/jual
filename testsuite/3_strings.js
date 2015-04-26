
// This script tests implementation of strings


var szSimple = "This is a simple string";
var szEscaped1 = "Escaped characters - new line test\r\nnext line\twith tab and slash \\";
var szEscaped2 = "double slash \\\\";
var szMultilineString = "Helloworld\r\n\
this is a multiline string\
with more lines";

print (szSimple);
print (szEscaped1);
print (szEscaped2);
print (szMultilineString);

print ("");


// same as above with single quotes
szTest1 = 'This is a simple string';
szTest2 = 'Escaped characters - new line test\r\nnext line\twith tab and slash \\';
szTest3 = 'double slash \\\\';
szTest4 = 'Helloworld\r\n\
this is a multiline string \
with more lines';
szTest5 = "test \n\r \r\n interpretation of new line characters \r \n";
szTest6 = "test \n\r\n\r interpretation of new line characters\n\r";
szTest7 = "Quotation test \"Double quotes\" and \'single quotes\' it works!";

print (szTest1);
print (szTest2);
print (szTest3);
print (szTest4);
print (szTest5);
print (szTest6);
print (szTest7);
print ( concat("one","two", 3, "four") );
