#ifndef ROCKET_CORE_JS_BROWSER_CPP
#define ROCKET_CORE_JS_BROWSER_CPP

#include <Rocket/Core/JS/Browser.h>

#include <Rocket/Core/JS/detail/v8/HTMLElementBase.h>
#include <Rocket/Core/JS/detail/v8/HTMLElementGeneric.h>
#include <Rocket/Core/JS/detail/v8/HTMLElementList.h>
#include <Rocket/Core/JS/detail/v8/HTMLDocument.h>
#include <Rocket/Core/JS/detail/v8/Event.h>
#include <Rocket/Core/JS/detail/rocket/ElementDocumentWrapper.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

//for LogCallback()
#include <iostream>

namespace Rocket{ namespace Core{ namespace JS{

namespace {
///A callback to print stuff out, from javascript. Meant for debugging.
static v8::Handle<v8::Value> LogCallback(const v8::Arguments& args) {
  if (args.Length() < 1) return v8::Undefined();
  v8::HandleScope scope;
  v8::Handle<v8::Value> arg = args[0];
  v8::String::Utf8Value value(arg);
  std::cout << std::string(*value, value.length()) << std::endl;
  return v8::Undefined();
}
}//anonymous namespace




Browser::Browser(
  const RocketScope<Core::Context>& context,
  const RocketScope<Core::ElementDocument>& body)
  : m_rocketContext(context), m_rocketBody(body)
{
  assert( dynamic_cast<JS::ElementDocumentWrapper*>(&(*m_rocketBody)) );
  
  JS::ElementDocumentWrapper* docWrapper
    = static_cast<JS::ElementDocumentWrapper*>(&(*m_rocketBody));
  
  assert(docWrapper);

std::cout << "docWrapper: " << docWrapper << std::endl;

  //v8 init
  {
    v8::Locker locker;
    v8::HandleScope handle_scope;
    
    v8::Handle<v8::ObjectTemplate> globt = v8::ObjectTemplate::New();
    
    //Global template
    {
      globt->Set( v8::String::New("log"), v8::FunctionTemplate::New(LogCallback));
    }
    
    m_v8Context = v8::Context::New(NULL, globt);
    

    v8::Context::Scope context_scope(v8Context());

    //v8 context
    {
      v8::Handle<v8::Object> global = v8Context()->Global();
      
      //inform v8 of these classes
      //FIXME: is this necessary? This is probably just exposing the ctors,
      // which we don't want *anyway*
      {
        ///HTMLElement
        JS::juice::HTMLElementBase::getCW().AddClassTo(global);
        
        ///HTMLElement that represents Core::Element
        JS::juice::HTMLElementGeneric::getCW().AddClassTo(global);
        
        ///List of HTMLElement's
        JS::juice::HTMLElementList::getCW().AddClassTo(global);
        
        ///Event
        JS::juice::Event::getCW().AddClassTo(global);

        ///HTMLDocument
        JS::juice::HTMLDocument::getCW().AddClassTo(global);
      }
      
      ///HTMLDocument object (window.document)
      {
        ///Create a HTMLDocument object
        m_v8HTMLDocument = v8::Persistent<v8::Value>::New(
          JS::juice::create<JS::juice::HTMLDocument>(&*m_rocketBody) );

        // assert(!v8Document.IsEmpty());
        
        JS::juice::HTMLDocument* jsDocument
          = v8::juice::convert::CastFromJS<JS::juice::HTMLDocument>(m_v8HTMLDocument);
        
        assert(jsDocument);
        
        //FIXME: check that m_v8HTMLDocument will always last longer than
        docWrapper->setDOMHTMLDocument(jsDocument);
        
        global->Set( v8::String::New("document"), m_v8HTMLDocument);
        
      }
      
    }
    
    //Note: Make sure to do this after window.document is set.
    docWrapper->attachToBrowser(this);
  }
}


Browser::~Browser(){
  m_v8Context.Dispose();
  m_v8Context.Clear();
  m_v8HTMLDocument.Dispose();
  m_v8HTMLDocument.Clear();
}

Rocket::Core::Context&
Browser::
rocketContext()
{
  return *m_rocketContext;
}

const Rocket::Core::Context&
Browser::
rocketContext() const
{
  return *m_rocketContext;
}

v8::Handle<v8::Context>
Browser::
v8Context() const
{
  return m_v8Context;
}


v8::Handle<v8::Value>
Browser::
document() const
{
  return m_v8HTMLDocument;
}



void
Browser::
Browser::ReportException(const v8::TryCatch& try_catch) {
  //noop
}



} } }//namespaces Rocket::Core::JS

#endif
