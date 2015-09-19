/*
    Copyright (C) 2015 Sajon Oso 
    Jual Native C module - SQLite3 module
*/

#include <string.h>
#include <stdlib.h>

#include "jxapi.h"
#include "sqlite3.h"

const char *szFIELDSEP = "\t";
const char *szRECSEP = "\n";

int sql3_execute(jual_xapi *JXAPI)
{
    void *L = JXAPI->LS;
    defGetString *GetString = (defGetString *)JXAPI->fnGetString;
    defNumberPush *NumberPush = (defNumberPush *)JXAPI->fnNumberPush;

    int iResult = -1;

    const char *sqldbname = GetString(L, 1, NULL);
    const char *sqlstatement = GetString(L, 2, NULL);

    sqlite3 *sql3db;

    if ( sqlite3_open( sqldbname, &sql3db ) == SQLITE_OK ) {
        if (sqlite3_exec( sql3db, sqlstatement, 0, 0, 0 ) == SQLITE_OK )
            iResult = sqlite3_changes(sql3db);
    };
    sqlite3_close( sql3db );

    NumberPush(L, iResult);
	return 1;
}


int sql3_query(jual_xapi *JXAPI)
{
    void *L = JXAPI->LS;
    defGetNumber *GetNumber = (defGetNumber *)JXAPI->fnGetNumber;
    defGetString *GetString = (defGetString *)JXAPI->fnGetString;

    defStrInit *StrInit = (defStrInit *)JXAPI->fnStrInit;
    defStrAppend *StrAppend = (defStrAppend *)JXAPI->fnStrAppend;
    defStrPush *StrPush = (defStrPush *)JXAPI->fnStrPush;

    const char *sqldbname = GetString(L, 1, NULL);
    const char *sqlstatement = GetString(L, 2, NULL);
    int blFirstRowOnly = GetNumber(L, 3);

    char strBuffer[JXAPI->STRBUFFER_SIZE];
    char *cResult = StrInit(L, strBuffer, 32);    
    
    sqlite3 *sql3db;
    sqlite3_stmt *stmt;
    int iLenFIELDSEP = strlen(szFIELDSEP);
    int iLenRECSEP = strlen(szRECSEP);

    if ( sqlite3_open( sqldbname, &sql3db ) == SQLITE_OK )
    {
        if ( sqlite3_prepare( sql3db, sqlstatement, -1,&stmt,0 ) == SQLITE_OK )
        {
            int iNumColumns = sqlite3_column_count(stmt);
            int retval = sqlite3_step(stmt);

            while (retval == SQLITE_ROW)
            {
                int col;
                for ( col=0; col<iNumColumns; col++)
                {
                    const char *val = (const char*)sqlite3_column_text(stmt,col);
                    if (col > 0) StrAppend(strBuffer, szFIELDSEP, iLenFIELDSEP);
                    if (val) StrAppend(strBuffer, val, strlen(val));
                };

                if (blFirstRowOnly) {
                    retval = !SQLITE_ROW;
                } else {
                    StrAppend(strBuffer, szRECSEP, iLenRECSEP);
                    retval = sqlite3_step(stmt);                    
                };
            };
        };
    };

    sqlite3_close( sql3db );

    StrPush(strBuffer);
	return 1;
}


const char initString[]="\
lib_sqlite3_execute = ffi_map('libsqlite3', 'sql3_execute'); \
lib_sqlite3_query = ffi_map('libsqlite3', 'sql3_query'); \
function sqlite3_execute(db,sql){return ffi_call(lib_sqlite3_execute,db,sql)}; \
function sqlite3_query(db,sql,nos){return ffi_call(lib_sqlite3_query,db,sql,nos)}; \
";

int libsqlite3_init(jual_xapi *JXAPI) {
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

