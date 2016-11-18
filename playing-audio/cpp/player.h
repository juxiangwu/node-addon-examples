#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <node.h>
#include <node_object_wrap.h>
#include <iostream>
#include <cmath>
#include "fmode.hpp"
#include "fmod_errors.h"
using namespace std;
using namespace v8;

class Player : public node::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);
    ~Player();
    
private:
    explicit Player(std::string url="");
    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Getter(Local<String> property, const PropertyCallbackInfo<Value>& info);
    static void Setter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);
  
    static v8::Persistent<v8::Function> constructor;
    static void Play(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Pause(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Stop(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Release(const v8::FunctionCallbackInfo<v8::Value>& args);

    void doPlay();
    void doPause();
    void doStop();
    void doRelease();
    
    std::string _url;
    FMOD::System     *_system;
    FMOD::Sound      *_sound;
    FMOD::Channel    *_channel;
    int _status;
};

#endif