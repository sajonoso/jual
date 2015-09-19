// This file tests the command line arguments variable "arg"

if (isJUALSCRIPT) { arg.size = Array_MT.size; };

var iNumArgs = arg.size();
var i;
print("You entered: " + iNumArgs + " parameters\n");
for (i=0; i<iNumArgs; i=i+1) {
    print(arg[i]);
};
