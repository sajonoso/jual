// testing object declarations

var objCar1 = { make:"toyota", model:"corolla", year:2002 };
var objCar2 = { make:"ford", model:function(t){ print(this.make); return "falcon " + t; }, year:2006 };
var objCar3 = { make:"holden", model:"camira", year:[2001,2002,2003,2004,2005] };

print( objCar1.make + " " + objCar1.model + " " + objCar1.year );

print( objCar2.make + " " + objCar2.model("J") + " " + objCar2.year );

print( objCar3.make + " " + objCar3.model + " " + objCar3.year[2] );

print( "Test array field initialization: " + objCar3.year.size() );
