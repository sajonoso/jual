// This library makes JScript compatible with JualScript
// You can copy and modify this file for other JavaScript engines

isJUALSCRIPT = false;

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
Date.prototype.toLocalISOString = function() {
    var out= this.getFullYear() + "-" + Date_pad(this.getMonth()+1, 2) + "-" + Date_pad(this.getDate(), 2) +
    "T" + Date_pad(this.getHours(), 2) + ":" + Date_pad(this.getMinutes(), 2) + ":" + Date_pad(this.getSeconds(), 2) + "." + Date_pad(this.getMilliseconds(), 3);
    return out;
};



function print(szOut) {
    var szTmp=szOut;
    if (typeof szOut == 'string') szTmp=szOut.replace(/\n/g,"\r\n");
    if (typeof szOut == 'boolean') szTmp=szOut?"true":"false";
    WScript.echo(szTmp);
};


// ## FILE Functions
var io = {};
io.fso = new ActiveXObject("Scripting.FileSystemObject");
io.close = function(hFile) { hFile.ts.Close(); };
// io.flush - Not supported by FSO
io.exists = function(szFilename) { return io.fso.FileExists(szFilename); };
io.open = function(szFilename, szMode) {
    var hFile = {};
    hFile.name = szFilename;
    if (szMode == "r") {
        hFile.ts = io.fso.OpenTextFile(szFilename, 1);
        return hFile;
    };
    if (szMode == "w") {
        hFile.ts = io.fso.OpenTextFile(szFilename, 2, true);
        return hFile;
    };
    return null;
};
io.readbyte = function(hFile, iNumBytes) { return hFile.ts.read(iNumBytes); };
io.readline = function(hFile) { return hFile.ts.AtEndOfStream?null:hFile.ts.ReadLine(); };
// io.seek - Not supported by FSO
io.size = function(hFile) { return (io.fso.FileExists(hFile.name) ? io.fso.GetFile(hFile.name).Size : 0) };
io.writebyte = function(hFile, szData) { return hFile.ts.write(szData); };

var os = {};
os.exit = function(iCode) { WScript.Quit(iCode); };


//  ## Transfer command line arguments
var arg=[]; for (i=0; i<WScript.arguments.length; i++) { arg[i] = WScript.arguments(i); };
