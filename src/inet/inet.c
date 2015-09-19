/*
    Copyright (C) 2015 Sajon Oso 
    Jual Native C module - Internet Protocol Suite
    Currently only implements IPv4 socket functions
*/

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "jxapi.h"

#define LINE_SIZEMAX 1024

// #### OS specific definitions

// IP4INT is an integer type large enough to hold an IP4 address
// e.g. 127.0.0.1 = 0x01 00 00 7F

#ifdef LUA_USE_WINDOWS
typedef unsigned long IP4INT;
#endif

#ifdef LUA_USE_LINUX
typedef unsigned long IP4INT;
#endif

#ifdef LUA_USE_MACOSX
typedef unsigned long IP4INT;
#endif

// #### OS specific definitions


// #### Helper functions

#ifdef LUA_USE_WINDOWS
#ifndef strnlen
static __inline__ size_t strnlen( const char *start, size_t maxlen )
{
  /* Determine the length of a NUL terminated string, subject
   * to a maximum permitted length constraint.
   */
  const char *stop = start;

  /* Scan at most maxlen bytes, seeking a NUL terminator;
   * note that we MUST enforce the length check, BEFORE the
   * terminator check, otherwise we could scan maxlen + 1
   * bytes, which POSIX forbids.
   */
  while( ((stop - start) < maxlen) && *stop )
    ++stop;

  /* Result is the number of non-NUL bytes actually scanned.
   */
  return stop - start;
}
#endif
#endif

void ip4toarray(int *ip, IP4INT address) {
    ip[0] = address & 0xFF;
    ip[1] = address>>8 & 0xFF;
    ip[2] = address>>16 & 0xFF;
    ip[3] = address>>24 & 0xFF;    
}

// output must be at least 16 characters IP4STR_SIZE including null terminator
void ip4tostr(char *output, IP4INT address) {
    int ip[4];
    ip4toarray(ip, address);
    sprintf(output, "%03d.%03d.%03d.%03d", ip[0], ip[1], ip[2], ip[3]);    
}

// IP string must be in the format 000.000.000.000
IP4INT isIPString(const char *hostAddress) {
    int i, haSize, decimalCount;
    char buf[18];

    haSize = strnlen(hostAddress, 16);
    if (haSize != 15) return 0;

    strncpy(buf, hostAddress, 18);

    decimalCount = 0;
    for (i=0; i<haSize; i++) {
        if ( !(isdigit(buf[i]) || (buf[i] == '.')) ) return 0;
        if (buf[i] == '.') {
            buf[i] = '\0';
            decimalCount++;
        };
    };

    if (decimalCount != 3) return 0;

    char *endp;
    long octect;
    int ip[4];
    for (i=0; i<4; i++) {
        octect = strtol(&buf[i*4], &endp, 10);
        if (endp == &buf[i*4]) return 0;
        if (octect <0 || octect > 255) return 0;
        ip[i] = octect & 0xFF;
    };
    
    IP4INT result = (ip[3]<<24) | (ip[2]<<16) | (ip[1]<<8) | ip[0];
    return result;
    
}

// #### Helper functions


// #### OS specific routines
#ifdef LUA_USE_WINDOWS
#include "inet_win32.c"
#endif

#ifdef LUA_USE_LINUX
#include "inet_unix.c"
#endif

#ifdef LUA_USE_MACOSX
#include "inet_unix.c"
#endif

// #### OS specific routines


int TCP_ObjectSize(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defNumberPush *NumberPush = (defNumberPush *)JXAPI->fnNumberPush;

    NumberPush(L, sizeof(tcp_socket) );
    return 1;
}


int TCP_Client(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetNumber *GetNumber = (defGetNumber *)JXAPI->fnGetNumber;
    defGetString *GetString = (defGetString *)JXAPI->fnGetString;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    defNumberPush *NumberPush = (defNumberPush *)JXAPI->fnNumberPush;

    usrObject *uObj = (usrObject *)GetObject(L, 1);
    tcp_socket *sockClient = (tcp_socket *)uObj->values;

    size_t tSize;
    const char *address = GetString(L, 2, &tSize);
    int iPortNum = GetNumber(L, 3);
    int iTimeout = GetNumber(L, 4);

    tcp_socket *sockResult = TCPClient(sockClient, address, iPortNum, iTimeout);
    if (sockResult == NULL) {
        NumberPush(L, 0);
    } else {
        NumberPush(L, 1);
    };

    return 1;
}


int TCP_Server(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetNumber *GetNumber = (defGetNumber *)JXAPI->fnGetNumber;
    defGetString *GetString = (defGetString *)JXAPI->fnGetString;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    defNumberPush *NumberPush = (defNumberPush *)JXAPI->fnNumberPush;

    usrObject *uObj = (usrObject *)GetObject(L, 1);
    tcp_socket *sockClient = (tcp_socket *)uObj->values;

    size_t tSize;
    const char *address = GetString(L, 2, &tSize);
    int iPortNum = GetNumber(L, 3);
    int iTimeout = GetNumber(L, 4);

    tcp_socket *sockResult = TCPServer(sockClient, address, iPortNum, iTimeout, NULL);
    if (sockResult == NULL) {
        NumberPush(L, 0);
    } else {
        NumberPush(L, 1);
    };

    return 1;
}

int TCP_Accept(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    defNumberPush *NumberPush = (defNumberPush *)JXAPI->fnNumberPush;

    usrObject *uObjServer = (usrObject *)GetObject(L, 1);
    tcp_socket *serverSock = (tcp_socket *)uObjServer->values;

    usrObject *uObjClient = (usrObject *)GetObject(L, 2);
    tcp_socket *clientSock = (tcp_socket *)uObjClient->values;

    if (TCPAccept(serverSock, clientSock) == NULL) {
        NumberPush(L, 0);
    } else {
        NumberPush(L, 1);
    };

    return 1;
}


int TCP_Close(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;

    usrObject *uObj = (usrObject *)GetObject(L, 1);
    tcp_socket *socket = (tcp_socket *)uObj->values;

    TCPClose(socket);
    return 0;
}

int TCP_Write(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    defGetString *GetString = (defGetString *)JXAPI->fnGetString;
    defNumberPush *NumberPush = (defNumberPush *)JXAPI->fnNumberPush;

    usrObject *uObj = (usrObject *)GetObject(L, 1);
    tcp_socket *socket = (tcp_socket *)uObj->values;

    size_t tSize;
    const char *szData = GetString(L, 2, &tSize);
    
    if (TCPWrite(socket, szData, tSize) == TRUE) {
        NumberPush(L, 1);
    } else {
        NumberPush(L, 0);
    };

    return 1;
}


int TCP_Read(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    defGetNumber *GetNumber = (defGetNumber *)JXAPI->fnGetNumber;
    defStrInit *StrInit = (defStrInit *)JXAPI->fnStrInit;
    defStrAppend *StrAppend = (defStrAppend *)JXAPI->fnStrAppend;
    defStrPush *StrPush = (defStrPush *)JXAPI->fnStrPush;

    usrObject *uObj = (usrObject *)GetObject(L, 1);
    tcp_socket *socket = (tcp_socket *)uObj->values;
    
    int numBytes = GetNumber(L, 2);

    char lineData[LINE_SIZEMAX];

    if (numBytes > LINE_SIZEMAX-1) {
        return 0;
    };

    int numRead = TCPRead(socket, lineData, numBytes);
    if (numRead < 0) return 0; // return null;

    char strBuffer[JXAPI->STRBUFFER_SIZE];
    StrInit(L, strBuffer, 64);
    StrAppend(strBuffer, lineData, numRead);
    StrPush(strBuffer);
    return 1;
}


int TCP_ReadLine(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defGetObject *GetObject = (defGetObject *)JXAPI->fnGetObject;
    defStrInit *StrInit = (defStrInit *)JXAPI->fnStrInit;
    defStrAppend *StrAppend = (defStrAppend *)JXAPI->fnStrAppend;
    defStrPush *StrPush = (defStrPush *)JXAPI->fnStrPush;

    usrObject *uObj = (usrObject *)GetObject(L, 1);
    tcp_socket *socket = (tcp_socket *)uObj->values;

    char lineData[LINE_SIZEMAX];

    int numRead = TCPReadLine(socket, lineData, LINE_SIZEMAX-1);
    if (numRead < 0) return 0; // return null;

    char strBuffer[JXAPI->STRBUFFER_SIZE];
    StrInit(L, strBuffer, 64);
    StrAppend(strBuffer, lineData, numRead);
    StrPush(strBuffer);
    return 1;
}


const char initString[]="\
libinet_GetObjectSize = ffi_map('libinet', 'TCP_ObjectSize'); \
libinet_TCP_Client = ffi_map('libinet', 'TCP_Client'); \
libinet_TCP_Server = ffi_map('libinet', 'TCP_Server'); \
libinet_TCP_Accept = ffi_map('libinet', 'TCP_Accept'); \
libinet_TCP_Close = ffi_map('libinet', 'TCP_Close'); \
libinet_TCP_Write = ffi_map('libinet', 'TCP_Write'); \
libinet_TCP_Read = ffi_map('libinet', 'TCP_Read'); \
libinet_TCP_ReadLine = ffi_map('libinet', 'TCP_ReadLine'); \
 \
function TCPClient(hostaddress, port, timeout) { \
    var objSize = ffi_call(libinet_GetObjectSize); \
    var tc = ffi_newobject(objSize); \
    var iResult = ffi_call(libinet_TCP_Client, tc, hostaddress, port, timeout); \
    if (iResult == 0) { \
        tc = null; \
        return null; \
    }; \
    return tc; \
}; \
 \
function TCPServer(hostaddress, port, timeout) { \
    var objSize = ffi_call(libinet_GetObjectSize); \
    var ts = ffi_newobject(objSize); \
    var iResult = ffi_call(libinet_TCP_Server, ts, hostaddress, port, timeout); \
    if (iResult == 0) { \
        ts = null; \
        return null; \
    }; \
    return ts; \
}; \
 \
function TCPAccept(ts) { \
    var objSize = ffi_call(libinet_GetObjectSize); \
    var tc = ffi_newobject(objSize); \
     \
    if (ffi_call(libinet_TCP_Accept, ts, tc) == 0) { \
        tc = null; \
        return null; \
    } else { \
        return tc; \
    }; \
} \
 \
function TCPClose(ts) { \
    ffi_call(libinet_TCP_Close, ts); \
} \
 \
function TCPWrite(tc,data) { \
    return ffi_call(libinet_TCP_Write, tc, data); \
} \
 \
function TCPRead(tc, numBytes) { \
    return ffi_call(libinet_TCP_Read, tc, numBytes); \
} \
 \
function TCPReadLine(tc) { \
    return ffi_call(libinet_TCP_ReadLine, tc); \
} \
";

int libinet_init(jual_xapi *JXAPI) {
    void *L = JXAPI->LS;
    defStrInit *StrInit = (defStrInit *)JXAPI->fnStrInit;
    defStrAppend *StrAppend = (defStrAppend *)JXAPI->fnStrAppend;
    defStrPush *StrPush = (defStrPush *)JXAPI->fnStrPush;

    char strBuffer[JXAPI->STRBUFFER_SIZE];
    StrInit(L, strBuffer, 32);
    StrAppend(strBuffer, initString, sizeof(initString)-1);
    StrPush(strBuffer);

    return 0;
}
