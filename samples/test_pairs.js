var mya={};
mya.a = "alpha";
mya.s = "beta";
mya.c = "cappa";
mya.d = "delta";
mya.e = "epsilon";
mya.f = "feta";
mya.g = "gamma";

var iary = [ "apple", "orange", "pears", "bananas"];

for (key in mya) {
    print(key + " " + mya[key]);
};

print(mya["a"]);

// the next two loops does not work under JavaScript

for (key,ival in pairs(mya)) {
    print(key + " " + ival);
};

print("");

for (key,ival in ipairs(iary)) {
    print(key + " " + ival);
};
