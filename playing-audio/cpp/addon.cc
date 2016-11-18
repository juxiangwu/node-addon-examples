#include <node.h>
#include <v8.h>
#include <iostream>
#include <fstream>
#include <uv.h>
#include <vector>
#include "fmod.hpp"
#include "fmod_errors.h"

#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

using namespace v8;
using namespace std;
//Define functions in scope
std::string stringValue(Local<Value> value);

int m_brk;
int32_t preview_width, preview_height;
uv_async_t async;
uv_loop_t *loop;

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


struct TMessage {
    Persistent<Function> callBack;
    FMOD::System * system;
    FMOD::Sound      *sound;
    FMOD::Channel    *channel;
    ~TMessage() {
        callBack.Reset();
        if(sound){
            sound->release();
        }
        if(system){
            system->close();
            system->release();
        }
    }
};

struct AsyncMessage {
//    std::vector<unsigned char> image;
//    cv::Mat frame;
//    bool window;
     double position;
     double length;
     double duration;
     double curms;
     bool playing;
     bool paused;
};

TMessage *message;
void updateAsync(uv_async_t* req, int status) {
    
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    
    AsyncMessage* asyncMessage = (AsyncMessage*) req->data;
    
    Local<Function> callBack = Local<Function>::New(isolate,message->callBack);

    
    Local<Number> arr = Number::New(isolate,asyncMessage->position);
    Local<Value> argv[] = {
            arr
    };
    callBack->Call(isolate->GetCurrentContext()->Global(), 1, argv);
//    if(!asyncMessage->playing){
//        m_brk = 0;
//    }
    delete asyncMessage;
}


void AudioOpen(uv_work_t* req) {
    TMessage* message = (TMessage*) req->data;
    
    while(m_brk > 0) {  
        AsyncMessage *msg = new AsyncMessage();
        msg->position = 0;
        msg->duration = 0;
        msg->curms = 0;
        msg->playing = false;
        msg->paused = true;
        FMOD_RESULT       result;
        unsigned int ms = 0;
        unsigned int lenms = 0;
        bool         playing = 0;
        bool         paused = 0;
        int          channelsplaying = 0;
        message->system->update();
        
        if(message->channel){
            FMOD::Sound *currentsound = 0;
            result = message->channel->isPlaying(&playing);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }
            msg->playing = playing;
            result = message->channel->getPaused(&paused);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }
            msg->paused = paused;
            result = message->channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }
            msg->position = ms;   
            message->channel->getCurrentSound(&currentsound);
            if (currentsound)
            {
                result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }
                msg->duration = lenms;
            }
      }
      async.data  = msg;
      uv_async_send(&async);
      Sleep(20);
    }
}

void AudioClose(uv_work_t* req, int status) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    TMessage* message = (TMessage*) req->data;
    //message->capture->release();
    //delete message->capture;
    delete req;
}

void Open(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    
    loop = uv_default_loop();
    message = new TMessage;
    
    m_brk = 1;
    if(args.Length() < 2){
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Arguments too few")));
        return;
    }
    
    if(!args[1]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"First argument must be frame callback function")));
        return;
    }
    
    String::Utf8Value cmd(args[0]);
    string url = string(*cmd);
    
    message->callBack.Reset(isolate,Handle<Function>::Cast(args[1]));
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    result = FMOD::System_Create(&message->system);
    ERRCHECK(result);

    result = message->system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Invalid FMOD version")));
        return;
    }

    result = message->system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);  
    
    result = message->system->createSound(url.c_str(), FMOD_HARDWARE, 0, &message->sound);
    ERRCHECK(result);

    result = message->sound->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
    ERRCHECK(result);
    
    uv_work_t* req = new uv_work_t();
    req->data = message;
    
    async = uv_async_t();
    
    uv_async_init(loop,&async,(uv_async_cb)updateAsync);
    uv_queue_work(loop, req, AudioOpen,(uv_after_work_cb) AudioClose);
    result = message->system->playSound(FMOD_CHANNEL_FREE, message->sound, false, &message->channel);
                    ERRCHECK(result);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate,"ok"));
}

void Close(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    
    m_brk = 0;
    if(message){
        if(message->sound){
            message->sound->release();
        }
        if(message->system){
            message->system->close();
            message->system->release();
        }
    }
    uv_loop_close(loop);
    uv_close((uv_handle_t *) &async, NULL);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate,"ok"));
}

void Init(Handle<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    exports->Set(String::NewFromUtf8(isolate,"Open"), FunctionTemplate::New(isolate,Open)->GetFunction());
    exports->Set(String::NewFromUtf8(isolate,"Close"), FunctionTemplate::New(isolate,Close)->GetFunction());
}

std::string stringValue(Local<Value> value) {
    if(value->IsString()){
        //Alloc #1
        char * buffer = (char*) malloc(sizeof(char) * value->ToString()->Utf8Length());
        value->ToString()->WriteUtf8(buffer,value->ToString()->Utf8Length());
        std::string ret(buffer);
        free(buffer);
        return ret;
    } else {
        return "";
    }
}

NODE_MODULE(player, Init);