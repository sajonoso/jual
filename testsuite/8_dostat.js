
// Test of do statement

var j = 1;
do {
    j = j + 1;
} while (j==15);
print (j);

print("");

do {
    j = j + 1;
} while (j<=15);
print (j);

var x =0;
var y =0;
var szOut = "*";
do {
    y = 0;
    do {
        szOut = (szOut + " " + y);
        y = y + 1;
        if (y == 25) { break; };
    } while (y < 50);

    szOut = (szOut + "\n");
    x = x + 1;
    if (x == 8) { break; };
} while (x < 10);

print (szOut);
