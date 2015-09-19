/*
    Copyright (C) 2015 Sajon Oso 
    Jual Native C module - Uint8Array module
*/

#include <string.h>
#include <stdio.h>

#include "jxapi.h"


int zeroarray (jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;

    usrObject *uObj = (usrObject *)GetObject(L, 1);

    memset (uObj->values,'\0',uObj->size);
    return 0;
}


int setarray (jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetNumber *GetNumber = (defGetNumber *)JXAPI->fnGetNumber;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    
    usrObject *uObj = (usrObject *)GetObject(L, 1);
    int index = GetNumber(L, 2);
    int value = GetNumber(L, 3);

    if (uObj == NULL) return 0;
    if (index < 0 || index >= uObj->size) return 0;

    uObj->values[index] = value &0xFF;
    return 0;
}


int getarray (jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetNumber *GetNumber = (defGetNumber *)JXAPI->fnGetNumber;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    
    defNumberPush *NumberPush = (defNumberPush *)JXAPI->fnNumberPush;
    
    usrObject *uObj = (usrObject *)GetObject(L, 1);
    int index = GetNumber(L, 2);

    if (uObj == NULL) return 0;
    if (index < 0 || index >= uObj->size) return 0;

    NumberPush(L, uObj->values[index]);
    return 1;
}


int getasize (jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    defNumberPush *NumberPush = (defNumberPush *)JXAPI->fnNumberPush;

    usrObject *uObj = (usrObject *)GetObject(L, 1);
    
    NumberPush(L, uObj->size);
    return 1;
}


int getstring (jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;

    defStrInit *StrInit = (defStrInit *)JXAPI->fnStrInit;
    defStrAppend *StrAppend = (defStrAppend *)JXAPI->fnStrAppend;
    defStrPush *StrPush = (defStrPush *)JXAPI->fnStrPush;
    
    usrObject *uObj = (usrObject *)GetObject(L, 1);

    char strBuffer[JXAPI->STRBUFFER_SIZE];
    (void)StrInit(L, strBuffer, uObj->size+1);

    StrAppend(strBuffer, (const char *)uObj->values, uObj->size);
    StrPush(strBuffer);

    return 1;
}


const char initString[]="\
uint8array_zeroarray = ffi_map('uint8array', 'zeroarray'); \
uint8array_setarray = ffi_map('uint8array', 'setarray'); \
uint8array_getarray = ffi_map('uint8array', 'getarray'); \
uint8array_arraysize = ffi_map('uint8array', 'getasize'); \
uint8array_arraystring = ffi_map('uint8array', 'getstring'); \
uint8array = {}; \
uint8array.__index=function(key) { \
  return ffi_call(uint8array_getarray,this.Z,key); \
}; \
uint8array.__newindex=function(key,value) { \
  return ffi_call(uint8array_setarray,this.Z,key, value); \
}; \
uint8array.size=function() { \
  return ffi_call(uint8array_arraysize,this.Z); \
}; \
uint8array.toString=function() { \
  return ffi_call(uint8array_arraystring,this.Z); \
}; \
uint8array.zero=function() { \
  return ffi_call(uint8array_zeroarray,this.Z); \
}; \
function Uint8Array(iSize) { \
    var ob = {}; \
    ob.Z = ffi_newobject(iSize); \
    setmetatable(ob, {__index:uint8array} ); \
    return ob; \
}; \
";

// **
// init function name must always be in the format of <module name>_init
// the init function must always return 0
// **
int uint8array_init(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defStrInit *StrInit = (defStrInit *)JXAPI->fnStrInit;
    defStrAppend *StrAppend = (defStrAppend *)JXAPI->fnStrAppend;
    defStrPush *StrPush = (defStrPush *)JXAPI->fnStrPush;

    char strBuffer[JXAPI->STRBUFFER_SIZE];
    (void)StrInit(L, strBuffer, 32);
    StrAppend(strBuffer, initString, sizeof(initString)-1);
    StrPush(strBuffer);

    return 0;
}
