

// This script tests interpretation of numerical constants

var iTest1 = 3;         // integers
var iTest2 = 3.1416;    // floats
var iTest3 = 0xFF;      // hexadecimal
var iTest4 = 0xF00F;    // hexadecimal
var iTest5 = 314.16e-2; // scientific
var iTest6 = 0.31416E1; // scientific
// var iTest7 = 0377;      // octal number constants is not supported in JualScript

print (iTest1);
print (iTest2);
print (iTest3);
print (iTest4);
print (iTest5);
print (iTest6);
// print (iTest7);

// testing variable case sensitivity
var iCasesensitiveVariables = "hello";
var icasesensitivevariables = "world";
var variablewithnumber1 = "works1";
var variable_with_under_scores = 12345;

print(iCasesensitiveVariables);
print(variablewithnumber1);
print(variable_with_under_scores);

// testing variable scope
var iScope = "Global";

function localfunc(szText) {
    // if (iScope == null) { iScope = "null" };
    // print ( "I am " + iScope) );    
    var iScope = "Local";
    print ( "I am " + iScope );
}

localfunc("I am Spartacus!");

print ( "No I am Spartacus! " + iScope );
