/*
    Jual Native C module API interface
    
    This is the only file you need to include in your module file to interface with the jual module system
*/

typedef struct usrObject {
    size_t size;                // Variable data size
    void *ptr;                  // Generic pointer
    unsigned char values[1];    // Variable data
} usrObject;

typedef struct jual_xapi_ {
    int STRBUFFER_SIZE;
    void *LS;
    void *fnGetNumber;
    void *fnGetString;
    void *fnGetObject;
    void *fnNumberPush;
    void *fnStrInit;
    void *fnStrAppend;
    void *fnStrPush;
} jual_xapi;

typedef int defGetNumber(void *LS, int argnum);
typedef const char *defGetString(void *LS, int argnum, size_t *tSize);
typedef void *defGetObject(void *LS, int argnum);
typedef void defNumberPush(void *LS, int iValue);
typedef char *defStrInit(void *LS, void *strBuf, size_t tSize);
typedef void defStrAppend(void *strBuf, const char *szValue, size_t tSize);
typedef void defStrPush(void *strBuf);


/*

Your exported C functions should look something like this:

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
    
    int iArgument1 = GetNumber(L, 1);
    
    NumberPush(L, 123456789);
    return 1;  // always 1 to indicate number of variables returned or 0 if returning nothing.
};
*/
