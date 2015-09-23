#include "binding.h"

NAN_METHOD(Wait) {
  Nan::HandleScope scope;
  int status;

  // non-blocking
  // do not wait for a dead child because this is run on the main event loop
  // this method is intended for init, who inherits children that it did not spawn
  pid_t ok = waitpid(-1, &status, WNOHANG);

  if (ok == 0) {
    // no child exited
    info.GetReturnValue().Set(Nan::Null());
  } else if (ok != -1) {
    // we caught a child exiting
    // the exit status is an integer containing bits of useful information

    v8::Local<Object> o = Nan::New<Object>();

    o->Set(Nan::New<String>("_").ToLocalChecked()        , Nan::New<Number>(status));
    o->Set(Nan::New<String>("exited").ToLocalChecked()   , Nan::New<Number>(WIFEXITED(status)));
    o->Set(Nan::New<String>("status").ToLocalChecked()   , Nan::New<Number>(WEXITSTATUS(status)));
    o->Set(Nan::New<String>("signal").ToLocalChecked()   , Nan::New<Number>(WIFSIGNALED(status)));
    o->Set(Nan::New<String>("termsig").ToLocalChecked()  , Nan::New<Number>(WTERMSIG(status)));
    o->Set(Nan::New<String>("coredump").ToLocalChecked() , Nan::New<Number>(WCOREDUMP(status)));
    o->Set(Nan::New<String>("ifstopped").ToLocalChecked(), Nan::New<Number>(WIFSTOPPED(status)));
    o->Set(Nan::New<String>("stopsig").ToLocalChecked()  , Nan::New<Number>(WSTOPSIG(status)));
    o->Set(Nan::New<String>("continued").ToLocalChecked(), Nan::New<Number>(WIFCONTINUED(status)));

    info.GetReturnValue().Set(o);
  }
}
