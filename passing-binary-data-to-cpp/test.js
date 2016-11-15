var addon = require('./build/Release/addon');
var data = "The data include some UTF8 encoding string.";
length = Buffer.byteLength(data); //UTF8 length
var buf = new Buffer(length);
buf.write(data, 0, 'UTF8');
var res = addon.sendData(buf, length);
console.log(res)