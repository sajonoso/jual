
var szMyFileName = "testfile.txt";

// Create a text file
var hFile = io.open(szMyFileName, "w");
if (hFile == null) { return; };

var j=0;
var szLine;
while (j<15) {
    szLine = "This is line number" + j + "\n";
    io.writebyte(hFile, szLine);
    j+=1;
}
io.close(hFile);


// Read a text file
var hFileIn = io.open(szMyFileName, "r");

szLine = io.readline(hFileIn);
while (szLine != null) {
    print(szLine);
    szLine = io.readline(hFileIn);
}
io.close(hFileIn);


// Create a binary file
var hBinWrite = io.open("myfile.bin", "w");
if (hBinWrite == null) { return; };

var j=0;
var aChars=[];
while (j<256) {
    aChars[j] = String.fromCharCode(j);
    j+=1;
};
szLine = aChars.join();
io.writebyte(hBinWrite, szLine);
io.seek(hBinWrite,0x31);
io.writebyte(hBinWrite, String.fromCharCode(0xFF) );
io.close(hBinWrite);


// Read a binary file
var hBinRead = io.open("myfile.bin", "rb");
if (hBinRead == null) { return; };
io.seek(hBinRead, 0x31);
szLine = io.readbyte(hBinRead, 10);
io.close(hBinRead);
print(szLine);
