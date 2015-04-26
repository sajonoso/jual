
// This script tests implementation of the if statement

var j = 20;
var k = 1;
var p = 1;

// single if statement
if (j == 20) { print("YES1"); };

// multiple statements
if (j == 20) {
    print("YES2");
    print("YES3");
};

// single else statement
if (j == 20) {
    print("YES4");
} else {
    print("NO");
};

// single if and else statement
if (j == 16) {
    print("NO");
} else if (k == 1) {
    print("YES5");
};

// multiple else if statements

var i;
for (i=0; i<3; i = i + 1) {

    if (i == 2) {
        print("YES8");
    } else if (i == 0) {
        print("YES6");
    } else if (i == 1) {
        print("YES7");
    };

};
