
// Testing classes using closures

// define class for person
function Person(iAge, szName) {
    var obj = {};
    // public properties
    obj.age = iAge;
    obj.Name = szName;
        
    // public methods
    obj.setAge = function(iAge) { obj.age = iAge; };
    obj.getAge = function() { return obj.age; };
    obj.setName = function (szName) { obj.Name = szName; };
    obj.getName = function () { return obj.Name; };
    obj.whoami = function () { print(obj.Name); };

    return obj;
};


John = Person(15, "John Smith");
John.whoami();
print(John.getAge());

Jane = Person(22, "Jane Smith");
Jane.whoami();

print(Jane.age);
