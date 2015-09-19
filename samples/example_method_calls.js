
// This file demonstrates the use of object oriented methods in both JualScript
// and JavaScript. It shows how an object can be defined that will produce the same
// results in both languages

// functions declared via a statment like this are unchanged
function walk(distance) {
    print( "Someone will walk " + distance + " miles" );
}
walk(200);


var person = {};
person.name = "John";
    
// functions declared via assignment have a hidden 'this'
// parameter passed as the first parameter
person.drive = function(/* this, */ colour, car) {
    print( this.name + " is now driving his " + colour + " " + car );
}
// functions called with the dot notation will automatically have the 
// function converted to a method call with the preceeding object passed as the first parameter
// The method call below will result in the same ouput in JualScript and JavaScript
person.drive( /* person, */ "purple", "porsche");


// If you would like to declare the method separately, this is the correct way
// to separately declare a method for an object
person_run = function(distance) {
    print( this.name + " will run " + distance + " miles" );
}
person.run = person_run;
// The method call below will result in the same ouput in JualScript and JavaScript
person.run(500);


// Do not declare a method for an object via a the function statement
// You will manually need to include the object as the first parameter
// However, this will break compatibility with JavaScript, because the first parameter
// can not be named 'this', therefore it will be undefined in JavaScript.
function person_walk(who, distance) {
    print( who.name + " will walk " + distance + " miles" );
}
person.walk = person_walk;

// The method call below will result in different ouput in JualScript and JavaScript
person.walk(500);
