var addon = require('./build/Release/addon');
var res = addon.sendObject({name:'abcde'});
console.log(res);