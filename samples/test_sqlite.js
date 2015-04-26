// This file tests the SQLite module for JualScript

sql3 = require("libsqlite3");

mydbname= "mytest.db";

print( sql3.query( mydbname, "SELECT sqlite_version(), sqlite_source_id();") );

sql3.execute( mydbname, "CREATE TABLE People (id INT, name VARCHAR(64))" );
szSQLInsert = "INSERT INTO People VALUES (#ID#, '#PERSON#');\n";
szSQL="";
szStatements="";
iMax=10000;
print("Creating " + iMax + " records");

for (var i=0; i < iMax; i=i+1) {
    szSQL = replace(szSQLInsert, "#ID#", i);
    szSQL = replace(szSQL, "#PERSON#", "Person" + i);
    szStatements = szStatements + szSQL;

    if ( (i%500 == 0) || (i==iMax-1) )
    {
        sql3.execute( mydbname, "BEGIN;\n" + szStatements + "COMMIT;\n");
        szStatements="";
    }
};


print( sql3.query( mydbname, "SELECT * FROM People LIMIT 10;") );
