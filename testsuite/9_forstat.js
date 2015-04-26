
// test of for loops
var szOut;
var k;

szOut = "*";
for (k=1; k<50; k=k*2) {
    szOut = (szOut + " " + k);
}
print( (slice(szOut,3) + "\r\n") );

szOut = "*";
for (k=35; k>1; k=k-1) {
    szOut = (szOut + " " + k);
    if (k == 10) { break; };
}
print( (szOut + "\r\n") );

szOut = "*";
for (k=1; k<2000; k=k*2) {
    szOut = (szOut + " " + k);
}
print( (szOut + "\r\n") );

// test break statement with multiple for loops

var x=0;
var y=0;
szOut = "*";
for (x=0; x<50; x=x+1) {
    for (y=0; y<50; y=y+1) {
        szOut =  (szOut + " " + y);
        if (y == 15) { break; };
    };
    szOut = (szOut + "\r\n");
    if (x == 10) { break; };
};
print( (szOut + "\r\n") );

