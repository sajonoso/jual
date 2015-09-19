
// A method of object orientation that works the same in JavaScript
// and JualScript


// Object methods
Animal_Eat = function(food) {
    print(this.Name + " just ate a " + food);
}
Animal_Chase = function(prey) {
    print(this.Name + ", the " + this.Type + " is chasing a " + prey);
}
// Object Constructor
function Animal(name, age, type) {
    var obj = {};
    // Properties
    obj.Name = name;
    obj.Type = type;
    obj.Age = age;

    // Methods
    obj.Eat = Animal_Eat;
    obj.Chase = Animal_Chase;

    // example of inline method definition. This should be avoided to reduce memory usage
    // as each instance of object will create it's own anonymous function
    obj.Sleep = function(time) {
        print( this.Name + " will sleep for " + time + " minutes" );
    };
    return obj;
};


var Lion = Animal("Simba", 5, "Lion");
var Tiger = Animal("Tiga", 3, "Tiger");

print("Did you know that " + Lion.Name + " is a " + Lion.Type + "?");
Lion.Eat("person");
Lion.Chase("car");
Lion.Sleep(5);

print("");

Tiger.Chase("Tarzan");
Tiger.Eat("Jane");
