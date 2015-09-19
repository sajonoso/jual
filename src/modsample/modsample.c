/*
    This is a sample Jual Native C module
    You can use this as a template for your modules
*/

#include <string.h>
#include <stdio.h>

#include "jxapi.h"

int myfunc(jual_xapi *JXAPI)
{
    void *L = JXAPI->LS;
    // Map functions as required
    defGetNumber *GetNumber = (defGetNumber *)JXAPI->fnGetNumber;
    defGetString *GetString = (defGetString *)JXAPI->fnGetString;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    
    defNumberPush *NumberPush = (defNumberPush *)JXAPI->fnNumberPush;
    defStrInit *StrInit = (defStrInit *)JXAPI->fnStrInit;
    defStrAppend *StrAppend = (defStrAppend *)JXAPI->fnStrAppend;
    defStrPush *StrPush = (defStrPush *)JXAPI->fnStrPush;

    int iNum = GetNumber(L, 1);
    
    size_t tSize;
    const char *szParm2 = GetString(L, 2, &tSize);

    printf("you entered %d %s %d\n", iNum, szParm2, tSize);

    char strBuffer[JXAPI->STRBUFFER_SIZE];
    char *cResult = StrInit(L, strBuffer, 16);

    const char text[]="Hello from the C language";
    StrAppend(strBuffer, text, sizeof(text)-1);

    const char text2[]="More greeting from the C language";
    StrAppend(strBuffer, text2, sizeof(text2)-1);

    StrPush(strBuffer);

    return 1;
}


const char initString[]="\
ffi_func1 = ffi_map('modsample', 'myfunc');\n\
function friendlyCall(num,str){return ffi_call(ffi_func1,num,str)};\n\
";

// **
// init function name must always be in the format of <module name>_init
// the init function must always return 0
// **
int modsample_init(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defStrInit *StrInit = (defStrInit *)JXAPI->fnStrInit;
    defStrAppend *StrAppend = (defStrAppend *)JXAPI->fnStrAppend;
    defStrPush *StrPush = (defStrPush *)JXAPI->fnStrPush;

    char strBuffer[JXAPI->STRBUFFER_SIZE];
    char *cResult = StrInit(L, strBuffer, 32);
    StrAppend(strBuffer, initString, sizeof(initString)-1);
    StrPush(strBuffer);

    return 0;
}
