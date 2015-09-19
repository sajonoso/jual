
// test of date object.  This test may fail if the first run and second run
// is not executed in the same minute

var dtNow = new Date();

print( "Today is: " + dtNow.getFullYear() + "/" + 
dtNow.getMonth() + "/" + dtNow.getDate());

print( "The time is: " + dtNow.getHours() + ":" + 
dtNow.getMinutes() );

var dtSomeTime = new Date(1982, 8, 1, 23, 34, 12);
print( dtSomeTime.toLocalISOString() );
