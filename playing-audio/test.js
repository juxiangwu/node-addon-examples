var player = require('./build/Release/player');
player.Open('D:/CloudMusic/1.mp3',function(curpos){
    console.log(curpos);
});

//player.Close();