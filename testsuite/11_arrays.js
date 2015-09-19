
// test of arrays

// There are two ways to declare an array
var arrayLiteral = [1, 3, "one", 2, "three", 4, 5, 6, 7, '8'];
var arrayConstructor = new Array("mon", "tue", "wed", "thu", "fri", "sat", "sun");

function printa(a) {
    var i; var sz=""; var L=a.size();
    for (i=0; i<L; i=i+1) { sz = sz.concat(a[i], " "); };
    print(sz);
};

printa( arrayLiteral );
print ( "Size: " + arrayLiteral.size() );

printa( arrayConstructor );
print ( "Size: " + arrayConstructor.size() );
var szJoined = arrayConstructor.join(";");

print ( szJoined  );
printa( szJoined.split(";") );


// Testing nested Arrays
var aNesting1 = ["one", 2, "three", 4, 5, 6, [7, '8'] ];
print( aNesting1[6][1] );
print( aNesting1[6][0] );
print( aNesting1[5] );
print( aNesting1.size() );

var aNesting2 = ["one", {name:"john", age:34}, 2, "three", 4, 5, 6, [7, '8'] ];
print( aNesting2[1].name );
print( aNesting2[1].age );
print( aNesting2.size() );
