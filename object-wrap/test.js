var addon = require('./build/Release/addon');
var person = new addon.Person(18,'abcde');
console.log(person.age);
console.log(person.name);
console.log(person);
console.log(person.sayHello());

person.age = 20;
person.name = 'AAAA';
console.log(person);