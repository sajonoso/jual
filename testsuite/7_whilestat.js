
// Test of the while statement

var j = 0;
while (j < 4) {
    j = j + 1;
    print (j);
};

while (false) {
    print("this should never run");
};

// testing break statment
var szOut = "*";
j = 0;
while (j < 50) {
    szOut = (szOut + " " + j);
    if (j  == 20) { break; };
    j = j + 1;
};
print (szOut);

var szOut = "*";
var x = 0;
var y;
while (x < 10) {
    y = 0;
    while (y < 50) {
        szOut = (szOut + " " + y);
        if (y  == 20) { break; };
        y = y + 1;
    };
    szOut = (szOut + "\n");
    x = x + 1;
    
    if (x == 6) { break; };
};
print (szOut);

var k = 19;
print("");

j = 1;
while ( j < 4 && k == 19) {
    j = j + 1;
    print (j);    
};
