#include <iostream>                                                                                                                                 
#include <node.h>
#include <nan.h>
using namespace std;
using namespace v8;
using namespace Nan;
 
NAN_METHOD(Hello)
{
    Nan::HandleScope scope;
    String::Utf8Value cmd(info[0]);
    string s = string(*cmd);
    info.GetReturnValue().Set(Nan::New<String>(s.c_str()).ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports){
    exports->Set(Nan::New("hello").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(Hello)->GetFunction());
}

NODE_MODULE(addon,Init);