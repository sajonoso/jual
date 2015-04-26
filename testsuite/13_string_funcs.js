/*
    This file tests the string library
*/

function printarray(oArray) {
    var iLen=length(oArray);
    for (i=0; i<iLen; i=i+1) { print(i + ": " + oArray[i]) };
}

// string concatenation can either use the + operator or the lua .. operator
// Note the limitation of the + operator is that variables are subject to automatic
// coercions and conversions so the results may not be as you expected.

var szText="Mary had a little lamb, " +
"His fleece was white as snow, " +
"And everywhere that Mary went, " +
"The lamb was sure to go."

var aWords = split(szText," ");

var szNewWord = "";

for (i=0; i<length(aWords[0]); i=i+1) {
    print( charAt(aWords[0], i) + " " + charCodeAt(aWords[0], i) );
    szNewWord = szNewWord + fromCharCode(charCodeAt(aWords[0], i));
};

print( concat(aWords[0], aWords[1], aWords[2], aWords[3], aWords[4]) );

print( szText );
printarray(aWords);

print(szNewWord);

print( indexOf(szText, "chop") );
print( indexOf(szText, "Mary") );
print( indexOf(szText, "Mary", 5) );
print( indexOf(szText, "go.") );
print( indexOf(szText, "snow") );

var szNewText=join(aWords, "_");

print(szNewText);

print( length(szText) );
print( length(aWords) );
print( length("") );
print( length(aWords[1]) );
print( length(aWords[2]) );

print( replace(szText, "lamb", "cat") );

// Jual implementation of Slice does not offically support negative indexes
print( slice(szText, 0) );
print( slice(szText, 2,6) );
print( slice(szText, 7) );
print( slice(szText, 13,106) );

var szTst = "One two three four";
print ( slice(szTst, 0, 0) );
print ( slice(szTst, 2, 5) );
print ( slice(szTst, 0, 5) );
print ( slice(szTst, 7, 18) );
print ( slice(szTst, 15, 18) );

print( toLowerCase(szText) );
print( toUpperCase(szText) );

print( parseInt("12") );
print( parseInt("3") );
print( parseInt("800") );
print( parseInt("700", 8) );
print( parseInt("01001101010", 2) );
print( parseInt("5678910111213") );

var oFail = parseInt("15");
var blResult = isNaN(oFail);
print ( blResult );


oFail = parseInt("J");
var blResult = isNaN(oFail);
print ( blResult );

print( parseFloat("12.34") );
print( parseFloat("56") );
print( parseFloat("78") );
print( 1 + parseFloat("9e-5") );
print( 1 + parseFloat("56.7e-10") );

