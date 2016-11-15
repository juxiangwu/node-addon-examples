
#include <iostream>                                                                                                                                 
#include <node.h>
#include <nan.h>
using namespace std;
using namespace v8;
using namespace Nan;

NAN_METHOD(PassArray) {
    Nan::HandleScope scope;
    vector<string> result;
    Handle<Value> val;
    Local<Array> arr = Nan::New<Array>();
 
    if (info[0]->IsArray()) {
      Handle<Array> jsArray = Handle<Array>::Cast(info[0]);
      for (unsigned int i = 0; i < jsArray->Length(); i++) {
        val = jsArray->Get(i);
        result.push_back(string(*String::Utf8Value(val)));
        Nan::Set(arr, i, val);
      }
    }
    info.GetReturnValue().Set(arr);
}

void Init(v8::Local<v8::Object> exports){
    exports->Set(Nan::New("passArray").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(PassArray)->GetFunction());
}

NODE_MODULE(addon,Init);