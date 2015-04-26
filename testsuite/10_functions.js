
// This script tests function statements

// no parameters
function myfunc0() {
    print("myfunc0");
}

// one parameter
function myfunc1(parm1) {
    print(parm1);
}

// two parameter
function myfunc2(parm1, parm2) {
    print(parm1);
    print(parm2);
}

// returning number
function myfunc3(one, two) {
    return ((one + two) * 21);
}

// returning string
function myfunc4(one, two) {
    return ( "hello world" + one + two );
}

myfunc0();
myfunc1("hello", "world");
myfunc2("hello", "world");

print( myfunc3(16,12) );
print( myfunc4("one","two") );
