
// testing javascript operators

// arithmetic
var num1 = 276328;
var num2 = 32654;
var test1=((123+56-89)/12*167) % 15;
var test2=num1 * 98374 - num2;
var test3=num1 / 4 % num2;
var test4=num1 + 98374 - num2;

print (test1);
print (test2);
print (test3);
print (test4);

// logical operators
var t = true;
var f = false;
print (t && t);
print (t && f);
print (f && t);
print (f && f);
print (t && t && f);
print (t && f && t);
print (t && t && t);

print (t || t);
print (t || f);
print (f || t);
print (f || f);
print (!f);
print (!t);

// comparisons
var higher = 123;
var lower = 12;
var equalh = 123;

print (higher > lower);
print (higher >= lower);
print (higher >= equalh);
print (higher < lower);
print (higher <= lower);
print (higher <= equalh);
print (higher == lower);
print (higher == equalh);
print (higher != lower);
print (higher != equalh);

print (higher == higher);
print (lower == lower);

//bitwise operators
print (higher & lower);
print (higher | lower);
print (higher ^ equalh);
print (~higher);
print (~lower);
print (higher << 2);
print (higher >> 2);
