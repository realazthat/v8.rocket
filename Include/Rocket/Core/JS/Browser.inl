#ifndef ROCKET_CORE_JS_BROWSER_INL
#define ROCKET_CORE_JS_BROWSER_INL

#include <Rocket/Core/JS/Browser.h>

#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <Rocket/Core.h>

#include <v8.h>

namespace Rocket{ namespace Core{ namespace JS{


template<typename OutT>
void
Browser::
Browser::ReportException(const v8::TryCatch& try_catch, OutT& out) {

  v8::HandleScope handle_scope;
  
  v8::String::Utf8Value exception(try_catch.Exception());
  const char* exception_string = JS::juice::ToCString(exception);
  v8::Handle<v8::Message> message = try_catch.Message();
  if (message.IsEmpty()) {
    // V8 didn't provide any extra information about this error; just
    // print the exception.
    out << exception_string << std::endl;
  } else {
    // Print (filename):(line number): (message).
    v8::String::Utf8Value filename(message->GetScriptResourceName());
    const char* filename_string = JS::juice::ToCString(filename);
    int linenum = message->GetLineNumber();
    out
      << filename_string
      << ":" << linenum
      << ": " << exception_string
      << std::endl;
    // Print line of source code.
    v8::String::Utf8Value sourceline(message->GetSourceLine());
    const char* sourceline_string = JS::juice::ToCString(sourceline);
    out << sourceline_string << std::endl;
    // Print wavy underline (GetUnderline is deprecated).
    int start = message->GetStartColumn();
    for (int i = 0; i < start; i++) {
      out << (" ");
    }
    int end = message->GetEndColumn();
    for (int i = start; i < end; i++) {
      out << ("^");
    }
    out << std::endl;
  }
}

template<typename HandleTryCatch>
v8::Handle<v8::Script>
Browser::
compile(const v8::Handle<v8::String> script_source,
  const v8::Handle<v8::String> script_name,
  HandleTryCatch handleTryCatch)
{
  assert(!script_source.IsEmpty());
  
  v8::Context::Scope context_scope(v8Context());
  v8::HandleScope handle_scope;
  
  // Compile script in try/catch context.
  v8::TryCatch try_catch;
  
  v8::Handle<v8::Script> script = v8::Script::Compile(script_source, script_name);
  
  
  if (script.IsEmpty()) {
    handleTryCatch(try_catch);
  }
  
  return handle_scope.Close(script);
}

template<typename HandleTryCatch>
v8::Handle<v8::Value>
Browser::
run(v8::Handle<v8::Script> script, HandleTryCatch handleTryCatch)
{
  assert(!script.IsEmpty());
  
  v8::Context::Scope context_scope(v8Context());
  v8::HandleScope handle_scope;

  v8::TryCatch try_catch;
  v8::Handle<v8::Value> result = script->Run();
  
  if (try_catch.HasCaught()) {
    handleTryCatch(try_catch);
  }
  
  return handle_scope.Close(result);
}


} } }//namespaces Rocket::Core::JS


#endif
