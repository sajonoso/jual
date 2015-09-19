// Testing simulation of ternary operator with logical AND + OR operators

var condition, j, t

condition=true;
t=(condition && [false] || [true])[0];
print(t);

condition=false;
var j=(condition && [false] || [true])[0];
print(j);


condition=true;
t=(condition && "fire" || "water");
print(t);

condition=false;
j=(condition && "fire" || "water");
print(j);

j = (["peter","paul"])[1];
print(j);