#include "person.h"

Person::Person(int age , std::string name ):_age(age),_name(name){
    
}

Person::~Person(){
        
}

void Person::Init(v8::Local<v8::Object> exports){
    Isolate* isolate = exports->GetIsolate();
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "Person"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    // Prototype
      NODE_SET_PROTOTYPE_METHOD(tpl, "sayHello", SayHello);
    
    tpl->InstanceTemplate()->SetAccessor(String::NewFromUtf8(isolate, "age"), Getter, Setter);
    tpl->InstanceTemplate()->SetAccessor(String::NewFromUtf8(isolate, "name"), Getter, Setter);
    
    constructor.Reset(isolate, tpl->GetFunction());
      exports->Set(String::NewFromUtf8(isolate, "Person"),
               tpl->GetFunction());
}

void Person::New(const v8::FunctionCallbackInfo<v8::Value>& args){
     Isolate* isolate = args.GetIsolate();
    if (args.IsConstructCall()) {
        // Invoked as constructor: `new Polynomial(...)`
        String::Utf8Value cmd(args[1]);
        string name = string(*cmd);
        int a = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        string b = args[1]->IsUndefined() ? 0 : name;
        Person* obj = new Person(a, b);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
      } else {
          
        // Invoked as plain function `Polynomial(...)`, turn into construct call.
        const int argc = 2;
        Local<Value> argv[argc] = { args[0] , args[1]};
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        args.GetReturnValue().Set(cons->NewInstance(argc, argv));
      }
}

void Person::Getter(Local<String> property, const PropertyCallbackInfo<Value>& info){
    Isolate* isolate = info.GetIsolate();
    Person* obj = ObjectWrap::Unwrap<Person>(info.This());
    v8::String::Utf8Value s(property);
    std::string str(*s);
    if ( str == "age") {
        info.GetReturnValue().Set(Number::New(isolate, obj->_age));
    }
    else if (str == "name") {
        info.GetReturnValue().Set(String::NewFromUtf8(isolate, obj->_name.c_str()));
    }
}

void Person::Setter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info){
    Person* obj = ObjectWrap::Unwrap<Person>(info.This());
    
    v8::String::Utf8Value s(property);
    std::string str(*s);
    
    if(str == "age"){
        obj->_age = (int)value->NumberValue();
    }else if (str == "name"){
         String::Utf8Value cmd(value);
        string name = string(*cmd);
        obj->_name = name;
    }
}

void Person::SayHello(const v8::FunctionCallbackInfo<v8::Value>& info){
    Isolate* isolate = info.GetIsolate();
    Person * obj =  ObjectWrap::Unwrap<Person>(info.Holder());
    std::string msg("hello,");
    msg.append(obj->_name);
    info.GetReturnValue().Set(String::NewFromUtf8(isolate,msg.c_str()));
}



Persistent<Function> Person::constructor;

