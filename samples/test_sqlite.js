// This file tests the SQLite module for JualScript

require_n("libsqlite3");

mydbname= "mytest.db";

print( sqlite3_query( mydbname, "SELECT sqlite_version(), sqlite_source_id();", 0) );

sqlite3_execute( mydbname, "CREATE TABLE People (id INT, name VARCHAR(64))" );
szSQLInsert = "INSERT INTO People VALUES (#ID#, '#PERSON#');\n";
szSQL="";
szStatements="";
iMax=10000;
print("Creating " + iMax + " records");

var i;
for (i=0; i < iMax; i=i+1) {
    szSQL = szSQLInsert.replace("#ID#", i);
    szSQL = szSQL.replace("#PERSON#", "Person" + i);
    szStatements = szStatements + szSQL;

    if ( (i%500 == 0) || (i==iMax-1) )
    {
        sqlite3_execute( mydbname, "BEGIN;\n" + szStatements + "COMMIT;\n");
        szStatements="";
    }
};


print( sqlite3_query( mydbname, "SELECT * FROM People LIMIT 10;", 0) );
