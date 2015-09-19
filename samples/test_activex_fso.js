// The JualScript engine can now simulate JScript Scripting.FileSystemObject object!

var file ="test17a.txt";

if (isJUALSCRIPT) {
    eval( includeJS("../lib/activex_fso.js") );
    file ="test17b.txt";
};

var fso = new ActiveXObject("Scripting.FileSystemObject");


// test creation of file
var wf = fso.OpenTextFile(file, 2, true);
wf.Write("This is the contents of the test file\n");
wf.Write("It should be in plain ASCII format\n");
wf.Close();
wf = null;

// test reading file
var rf = fso.OpenTextFile(file, 1);
var contents="";
while (!rf.AtEndOfStream) {
   contents = contents + rf.ReadLine() + "\n";
};
rf.Close();
rf = null;
print(contents);
