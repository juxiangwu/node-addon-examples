#include "person.h"

void InitPerson(Local<Object> exports) {
  Person::Init(exports);
}

NODE_MODULE(Person, InitPerson)