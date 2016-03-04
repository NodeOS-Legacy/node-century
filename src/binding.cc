#include "binding.h"

void InitAll(Handle<Object> exports) {
  exports->Set(Nan::New<String>("wait").ToLocalChecked(),
    Nan::New<FunctionTemplate>(Wait)->GetFunction());
  exports->Set(Nan::New<String>("demo").ToLocalChecked(),
    Nan::New<FunctionTemplate>(Demo)->GetFunction());
}

NODE_MODULE(binding, InitAll)
