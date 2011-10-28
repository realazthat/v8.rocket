#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTDOCUMENTWRAPPER_CPP
#define ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTDOCUMENTWRAPPER_CPP


#include <Rocket/Core/JS/detail/rocket/ElementDocumentWrapper.h>
#include <Rocket/Core/JS/Browser.h>

namespace Rocket{ namespace Core{ namespace JS{



ElementDocumentWrapper::ElementDocumentWrapper(const Core::String& tag)
  : super(tag), document(NULL), browser(NULL)
{

}

JS::juice::HTMLDocument*
ElementDocumentWrapper::
getDOMHTMLDocument()
{
  return document;
}

void
ElementDocumentWrapper::
setDOMHTMLDocument(JS::juice::HTMLDocument* doc)
{
  document = doc;
}



namespace detail{
  struct handle_errors_t{
    void operator()(const v8::TryCatch& try_catch){
      std::ostream& out(std::cout);

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
  };
}


void
ElementDocumentWrapper::
attachToBrowser(JS::Browser* b)
{
  browser = b;

  for ( scripts_buffer_t::const_iterator w = scripts_buffer.begin(), wend = scripts_buffer.end();
    w != wend;
    ++w)
  {
    LoadScript(w->first, w->second);
  }

  scripts_buffer.clear();
}

void
ElementDocumentWrapper::
LoadScript(Core::Stream* stream, const Core::String& source_name) {

  if ( browser ) {
    assert(scripts_buffer.empty());
    Rocket::Core::String buffer;
    stream->Read(buffer, stream->Length());

    LoadScript(buffer, source_name);
  } else {
    scripts_buffer.push_back(std::make_pair(Core::String(),source_name));
    stream->Read(scripts_buffer.back().first, stream->Length());
  }
}

void
ElementDocumentWrapper::
LoadScript(const Core::String& script_source, const Core::String& source_name) {
  v8::Locker locker;
  v8::HandleScope handle_scope;

  assert(browser);

  v8::Context::Scope context_scope(browser->v8Context());

  detail::handle_errors_t handle_errors;


  v8::Handle<v8::Script> script = browser->compile(v8::String::New(script_source.CString()),
    v8::String::New(source_name.CString()),
    handle_errors);

  browser->run(script, handle_errors);
}

} } }//namespaces Rocket::Core::JS

#endif
