#include "binding.h"

#include <stdio.h>

// this is just for demo purposes
NAN_METHOD(Demo) {
  Nan::HandleScope scope;

  popen("sleep 30", "r");

  return;
}
