var addon = require('./build/Release/hello');
var res = addon.hello('hello,node');
console.log(res);