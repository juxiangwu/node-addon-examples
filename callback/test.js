var addon = require('./build/Release/addon');
addon.onDataReceived(function(data){
   console.log('recv:' + data); 
});