//    This file tests the string library

function printarray(oArray) {
    var iLen=oArray.size();
    for (i=0; i<iLen; i=i+1) { print(i + ": " + oArray[i]) };
}

// string concatenation can either use the + operator or the lua .. operator
// Note the limitation of the + operator is that variables are subject to automatic
// coercions and conversions so the results may not be as you expected.

var szText="Mary had a little lamb, " +
"His fleece was white as snow, " +
"And everywhere that Mary went, " +
"The lamb was sure to go."

var aWords = szText.split(" ");

var szNewWord = "";

for (i=0; i<aWords[0].size(); i=i+1) {
    print( aWords[0].charAt(i) + " " + aWords[0].charCodeAt(i) );
    szNewWord = szNewWord + String.fromCharCode(aWords[0].charCodeAt(i));
};

print( aWords[0].concat(aWords[1], aWords[2], aWords[3], aWords[4]) );

print( szText );
printarray(aWords);

print(szNewWord);

print( szText.indexOf("chop") );
print( szText.indexOf("Mary") );
print( szText.indexOf("Mary", 5) );
print( szText.indexOf("go.") );
print( szText.indexOf("snow") );

var szNewText = aWords.join("_");

print(szNewText);

print( szText.size() );
print( aWords.size() );
print( ("").size() );
print( aWords[1].size() );
print( aWords[2].size() );

print("XXX");

print( szText.replace("lamb", "cat") );

print("ZZZ");

// Jual implementation of Slice does not offically support negative indexes
print( szText.slice(0) );
print( szText.slice(2,6) );
print( szText.slice(7) );
print( szText.slice(13,106) );

var szTst = "One two three four";
print ( szTst.slice(0, 0) );
print ( szTst.slice(2, 5) );
print ( szTst.slice(0, 5) );
print ( szTst.slice(7, 18) );
print ( szTst.slice(15, 18) );

print( szText.toLowerCase() );
print( szText.toUpperCase() );

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

