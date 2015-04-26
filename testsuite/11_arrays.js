
// test of arrays

var myAry = ["one", 2, "three", 4, 5, 6, 7, '8'];

var i;
for (i = 0; i<8; i=i+1) {
    print(myAry[i]);
};

print ( "Size: " + length(myAry) );

function printa(a) {
    var L=length(a);
    for (var i=0; i<L; i=i+1) { print(a[i]) };
};

var szJoined = join(myAry, ";");

print ( szJoined  );

printa( split(szJoined , ";") );
