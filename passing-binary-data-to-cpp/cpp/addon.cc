#include <iostream>                                                                                                                                 
#include <node.h>
#include <nan.h>
using namespace std;
using namespace v8;
using namespace Nan;
 
NAN_METHOD(SendData)
{
    Local<Object> bufferObj = info[0]->ToObject();
    unsigned int len = info[1]->Uint32Value();
    char* msg = node::Buffer::Data(bufferObj);
 
    info.GetReturnValue().Set(Nan::New<String>(msg, len).ToLocalChecked());
    // You can not use strlen(msg). Because it is a binary not a string. The end of  string is a null byte and  the end of binary data is not null.
}

void Init(v8::Local<v8::Object> exports){
    exports->Set(Nan::New("sendData").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(SendData)->GetFunction());
}

NODE_MODULE(addon,Init);