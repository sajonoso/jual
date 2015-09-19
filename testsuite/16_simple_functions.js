// This file tests the typeof function

var num1=1234.56;
var num2=1234;
var string1="1234";
var string2="ABC1234";

function foo_bar() { return 0; };
var bool1=false;

print(typeof(num1) + " " + typeof(num2));
print(typeof(string1) + " " + typeof(string2));
print(typeof(foo_bar) + " " + typeof(bool1));
