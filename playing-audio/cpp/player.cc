#include "player.h"
#include <uv.h>
#include <vector>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

#define STATUS_NONE 0
#define STATUS_INITED 0x01
#define STATUS_PLAYING 0x02
#define STATUS_PAUSED 0x03
#define STATUS_STOPPED 0x04

#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

Persistent<Function> Player::constructor;

Player::Player(std::string url):_url(url){
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    result = FMOD::System_Create(&_system);
    ERRCHECK(result);

    result = _system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        //return 0;
    }

    result = _system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = _system->createSound(_url.c_str(), FMOD_HARDWARE, 0, &sound);
    ERRCHECK(result);

    result = _sound->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
    ERRCHECK(result); 
    _status = STATUS_INITED;
}

Player::~Player(){
    if(_sound){
        _sound->release();
    }
    if(_system){
        _system->close();
        _system->release();
    }
}

void Player::doPlay(){
    if(_status == STATUS_NONE || _status == STATUS_PLAYING || _status == STATUS_STOPPED){
        return;
    }
    
    if(!_system || !_)
}

void Player::doPause(){
    
}

void Player::doStop(){
    
}

void Player::doRelease(){
    
}

void Player::Init(v8::Local<v8::Object> exports){
    Isolate* isolate = exports->GetIsolate();
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "Player"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "play", Play);
    NODE_SET_PROTOTYPE_METHOD(tpl, "pause", Pause);
    NODE_SET_PROTOTYPE_METHOD(tpl, "stop", Stop);
    NODE_SET_PROTOTYPE_METHOD(tpl, "release", Release);
    
    tpl->InstanceTemplate()->SetAccessor(String::NewFromUtf8(isolate, "url"), Getter, Setter);
    
    constructor.Reset(isolate, tpl->GetFunction());
      exports->Set(String::NewFromUtf8(isolate, "Player"),
               tpl->GetFunction());
}


void Player::New(const v8::FunctionCallbackInfo<v8::Value>& args){
     Isolate* isolate = args.GetIsolate();
    if (args.IsConstructCall()) {
        // Invoked as constructor: `new Polynomial(...)`
        String::Utf8Value cmd(args[0]);
        string _url_str = string(*cmd);
        string url = args[0]->IsUndefined() ? 0 : _url_str;
        Person* obj = new Player(url);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
      } else {
          
        // Invoked as plain function `Polynomial(...)`, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = { args[0]};
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        args.GetReturnValue().Set(cons->NewInstance(argc, argv));
      }
}


void Player::Getter(Local<String> property, const PropertyCallbackInfo<Value>& info){
    Isolate* isolate = info.GetIsolate();
    Person* obj = ObjectWrap::Unwrap<Player>(info.This());
    v8::String::Utf8Value s(property);
    std::string str(*s);
    if (str == "url") {
        info.GetReturnValue().Set(String::NewFromUtf8(isolate, obj->_url.c_str()));
    }
}

void Player::Setter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info){
    Player* obj = ObjectWrap::Unwrap<Player>(info.This());
    
    v8::String::Utf8Value s(property);
    std::string str(*s);
    
   if (str == "url"){
         String::Utf8Value cmd(value);
        string name = string(*cmd);
        obj->_url = name;
    }
}

void Player::Play(const v8::FunctionCallbackInfo<v8::Value>& info){
    Isolate* isolate = info.GetIsolate();
    Player * obj =  ObjectWrap::Unwrap<Player>(info.Holder());
//    std::string msg("hello,");
//    msg.append(obj->_name);
//    info.GetReturnValue().Set(String::NewFromUtf8(isolate,msg.c_str()));
}