#ifndef __PERSON_H__
#define __PERSON_H__

#include <node.h>
#include <node_object_wrap.h>
#include <iostream>
#include <cmath>
using namespace std;
using namespace v8;

class Person : public node::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);
    ~Person();
private:
     explicit Person(int age = 0, std::string name = "");
    
    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Getter(Local<String> property, const PropertyCallbackInfo<Value>& info);
    static void Setter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);
  
    static v8::Persistent<v8::Function> constructor;
    static void SayHello(const v8::FunctionCallbackInfo<v8::Value>& args);
    
    int _age;
    std::string _name;
};

#endif