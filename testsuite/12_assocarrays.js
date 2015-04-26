// Test associative arrays
// This test may fail because lua does not return result in order
// of item insertion.

ma={};
ma["one"] = 1;
ma["two"] = 2;
ma["three"] = 3;
ma["four"] = 4;
ma["five"] = 5;

for (mikey in ma) {
    print(mikey + " - " + ma[mikey]);
};
