// This library makes nodejs compatible with JualScript
// You can copy and modify this file for other JavaScript engines

global.isJUALSCRIPT = false;

// ## STRING functions
// Supported methods
// charAt charCodeAt concat indexOf replace split slice toLowerCase toUpperCase
String.prototype.size = function() { return this.length; };
// Object.defineProperty (String.prototype, 'size', {enumerable: false});
Array.prototype.size = String.prototype.size;
// Object.defineProperty (Array.prototype, 'size', {enumerable: false});

// DATE functions
function Date_pad(num, pad) {
    if (num==null) { num = 0; };
    var ns = "0000" + num;
    return ns.slice(-pad);
}
global.Date.prototype.toLocalISOString = function() {
    var out= this.getFullYear() + "-" + Date_pad(this.getMonth()+1, 2) + "-" + Date_pad(this.getDate(), 2) +
    "T" + Date_pad(this.getHours(), 2) + ":" + Date_pad(this.getMinutes(), 2) + ":" + Date_pad(this.getSeconds(), 2) + "." + Date_pad(this.getMilliseconds(), 3);
    return out;
};

global.print = function(szOut) {
    console.log(szOut);
};


var os = {};
// os.exit = process.exit;
global.os = os;
global.os.exit = process.exit;

//  ## Transfer command line arguments
var arg=[]; for (i=0; i<process.argv.length-1; i++) { arg[i] = process.argv[i+1] };
global.arg = arg;

var fs = require('fs');
global.includeJS = function(szFilename) {
    return fs.readFileSync(szFilename).toString();
}
