// Test associative arrays
// The test results are sorted because the order that key/value pairs are returned is not guaranteed

// ## Simple non-recursive sort function
function shellSort(a) {
    var aSize = a.size();
	var inc = Math.floor(aSize/2);
    var i, j, tmp;
	while (inc > 0) {
        i = inc;
		while (i<aSize) {
			tmp = a[i];
			j = i;
			while (j>=inc && a[j-inc]>tmp) {
				a[j] = a[j-inc];
				j -= inc;
			}
			a[j] = tmp;
            i+=1;
		};
		inc = Math.floor(inc/2);
	};
	return a;
}

function printArray(oArray) {
    var iLen=oArray.size();
    var out= "[";
    for (i=0; i<iLen; i+=1) { out=out + " " + oArray[i]; };
    out=out + " ]";
    print(out);
}


var ma=new Array();
ma["one"] = 1;
ma["two"] = 2;
ma["three"] = 3;
ma["four"] = 4;
ma["five"] = 5;

var mn=new Array();
var  i=0;
for (mikey in ma) {
    if (mikey != "size") { // size property is visible in javascript engines, but not jual so skip this key.
        mn[i] = (mikey + "_" + ma[mikey]);
        i+=1;
    };
};

// sort output to make results the same.
shellSort(mn);

printArray(mn);
