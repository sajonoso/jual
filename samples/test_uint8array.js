// This file tests the Uint8Array module of JualScript

if (isJUALSCRIPT) {
    require_n("uint8array");
} else {
    if (WScript) {
        Uint8Array  = Array;
    } else {
        Uint8Array.prototype.size = function() { return this.length; };
    };
};

var ui8a = new Uint8Array(1234567);

var i;
var arraySize = ui8a.size();
var j=0;
var dtStart = new Date();
for (i=0; i<arraySize; i+=1) {
    ui8a[i] = i;
    j = ui8a[i];
};
var dtEnd = new Date();

print(dtStart.toLocalISOString());
print(dtEnd.toLocalISOString());
print( arraySize );
