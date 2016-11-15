#include <iostream>                                                                                                                                 
#include <node.h>
#include <nan.h>
using namespace std;
using namespace v8;
using namespace Nan;
 
NAN_METHOD(SendObject)
{
    if(info[0]->IsObject()){
        Isolate* isolate = info.GetIsolate();
        Local<Object> obj = Local<Object>::Cast(info[0]);
        Local<String> name = String::NewFromUtf8(isolate,"name");
        if(obj->Has(name)){
            Local<Value> nameValue = obj->Get(name);
            info.GetReturnValue().Set(nameValue);
        }
        
    }
}

void Init(v8::Local<v8::Object> exports){
    exports->Set(Nan::New("sendObject").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(SendObject)->GetFunction());
}

NODE_MODULE(addon,Init);