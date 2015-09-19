/*
    Copyright 2015 Sajon Oso
    This library is a partial implementation of the ActiveX Scripting.FileSystemObject for JualScript
*/

textstream_MT = {};
textstream_MT.Skip = function(numChars) {
    if (numChars <=0 ) { return; };
    this.handle:seek("cur", numChars);
};
textstream_MT.SkipLine = function() {
    var data = this.handle:read("l");
    if (data == null || this.handle:seek("cur", 0) == (this.size)) {
        this.AtEndOfStream = true;
    };
};
textstream_MT.Read = function(numChars) {
    if (numChars <=0 ) { return ""; };
    var data = this.handle:read(numChars);
    if (data == null || this.handle:seek("cur", 0) == (this.size)) {
        this.AtEndOfStream = true;
    };
    if (data==null) { return ""; };
    return data;
};
textstream_MT.ReadAll = function() {
    var data = this.handle:read("a");
    this.AtEndOfStream = true;
    if (data == null) {
        return "";
    };
    return data;    
};
textstream_MT.ReadLine = function() {
    var data = this.handle:read("l");
    if (data == null || this.handle:seek("cur", 0) == (this.size)) {
        this.AtEndOfStream = true;
    };
    if (data==null) { return ""; };
    return data;
};
textstream_MT.Write = function(text) {
    this.handle:write(text);
};
textstream_MT.Close = function() {
    io.close(this.handle);
};


fso_MT = {};
fso_MT.OpenTextFile = function(fileName, mode, create) {
    var tso = {};
    tso.handle = 0;
    tso.size = 0;
    tso.AtEndOfStream = false;

    var openMode = "rb"; // default to reading
    if (mode == 1) { openMode = "rb"; }; // read in binary mode only
    if (mode == 2) { openMode = "wb"; }; // write in binary mode to prevent \n translation
    if (mode == 8) { openMode = "ab"; };

    tso.handle = io.open(fileName, openMode);
    if (tso.handle == null) { return null; };

    this.AtEndOfStream = false;
    tso.size = tso.handle:seek("end");
    if (tso.size == 0) {
        // if file is zero bytes
        tso.AtEndOfStream = true;
    };
    tso.handle:seek("set");
    setmetatable(tso, { __index : textstream_MT} );
    return tso;
};

function ActiveXObject(application) {
    var obj = {};

    if (application == "Scripting.FileSystemObject") {
        setmetatable(obj, {__index : fso_MT } );
    };

    return obj;
};
