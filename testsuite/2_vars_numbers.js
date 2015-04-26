

// This script tests interpretation of numerical constants

var iTest1 = 3;
var iTest2 = 3.1416;
var iTest3 = 0xFF;
var iTest4 = 0xF00F;
var iTest5 = 314.16e-2;
var iTest6 = 0.31416E1;

print (iTest1);
print (iTest2);
print (iTest3);
print (iTest4);
print (iTest5);
print (iTest6);

// testing variable case sensitivity
var iCasesensitiveVariables = "hello";
var ivasesensitivevariables = "world";
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
