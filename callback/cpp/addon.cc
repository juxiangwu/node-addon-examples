#include <nan.h>

void RunCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Function> cb = info[0].As<v8::Function>();
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::New("hello world").ToLocalChecked() };
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
}

//void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
//  Nan::SetMethod(module, "onDataReceived", RunCallback);
//}
void Init(v8::Local<v8::Object> exports){
    exports->Set(Nan::New("onDataReceived").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(RunCallback)->GetFunction());
}


NODE_MODULE(addon, Init)