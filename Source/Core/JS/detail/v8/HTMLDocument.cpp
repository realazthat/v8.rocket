#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLDOCUMENT_CPP
#define ROCKET_CORE_JS_DETAIL_V8_HTMLDOCUMENT_CPP


#include <Rocket/Core/JS/detail/v8/HTMLDocument.h>
#include <Rocket/Core/JS/detail/v8/HTMLElementList.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <v8.h>


namespace Rocket{ namespace Core{ namespace JS{ namespace juice{


HTMLDocument::CW&
HTMLDocument::getCW() {
  CW & cw( CW::Instance() );
  typedef v8::juice::convert::MemFuncInvocationCallbackCreator<HTMLDocument> ICM;
  
  if( cw.IsSealed() )
  {
      return cw;
  }
  
  // cw.BindGetter<Core::String,
              // &HTMLElementBase::tagName>
              // ("tagName");

  cw.BindGetter<v8::Handle<v8::Value>,
              &self_type::body>
              ("body");

  cw.BindGetter<v8::Handle<v8::Value>,
              &self_type::documentElement>
              ("documentElement");

  
  cw.Set( "createComment", ICM::M1::Invocable<v8::Handle<v8::Value>, const Core::String&, &HTMLDocument::createComment>);
  cw.Set( "createElement", ICM::M1::Invocable<v8::Handle<v8::Value>, const Core::String&, &HTMLDocument::createElement>);
  cw.Set( "createTextNode", ICM::M1::Invocable<v8::Handle<v8::Value>, const Core::String&, &HTMLDocument::createTextNode>);
  cw.Set( "createDocumentFragment", ICM::M0::Invocable<v8::Handle<v8::Value>, &HTMLDocument::createDocumentFragment>);
  cw.Set( "getElementById", ICM::M1::Invocable<v8::Handle<v8::Value>, const Core::String&, &HTMLDocument::getElementById>);
  cw.Set( "getElementsByTagName", ICM::M1::Invocable<v8::Handle<v8::Value>, const Core::String&, &HTMLDocument::getElementsByTagName>);
  cw.Set( "write", ICM::M1::Invocable<void, const Core::String&, &HTMLDocument::write>);
  cw.Set( "writeln", ICM::M1::Invocable<void, const Core::String&, &HTMLDocument::writeln>);

  
  cw.Seal(); // ends the binding process
  
  return cw;
}


HTMLDocument::HTMLDocument()
{
}


HTMLDocument::HTMLDocument(HTMLDocument::RElementT* element_)
  : document(element_)
{

}

HTMLDocument& HTMLDocument::operator=(const HTMLDocument& other){
  document = other.document;
  
  return *this;
}













v8::Handle<v8::Value> HTMLDocument::body() {
  v8::HandleScope handle_scope;
  
  return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket(), v8::Null()));
}



v8::Handle<v8::Value> HTMLDocument::documentElement() {
  Core::Element* result = getRocket();

  while ( result->GetParentNode() )
    result = result->GetParentNode();
  
  v8::HandleScope handle_scope;
  
  return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(result, v8::Null()));

}







v8::Handle<v8::Value>
HTMLDocument::
createElement(const Core::String& tag)
{
  v8::HandleScope handle_scope;
  
  return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->CreateElement(tag), v8::Null()));
}


v8::Handle<v8::Value>
HTMLDocument::
createComment(const Core::String& comment)
{

  v8::HandleScope handle_scope;
  
  
  //FIXME:??
  return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->CreateTextNode("<!-- " + comment + " -->"), v8::Null()));
}

v8::Handle<v8::Value>
HTMLDocument::
createTextNode(const Core::String& text)
{
  v8::HandleScope handle_scope;
  return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->CreateTextNode(text), v8::Null()));
}

v8::Handle<v8::Value>
HTMLDocument::
createDocumentFragment()
{
  v8::HandleScope handle_scope;
  
  return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->CreateElement("div"), v8::Null()));
}


v8::Handle<v8::Value> HTMLDocument::getElementById(const Core::String& elementId)
{
  v8::HandleScope handle_scope;
  return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetElementById(elementId), v8::Null()));
}

v8::Handle<v8::Value>
HTMLDocument::
getElementsByTagName(const Core::String& tagname)
{
  v8::HandleScope handle_scope;
  
  //FIXME: use overloaded create()
  v8::Handle<v8::Value> v8ElementList = JS::juice::create<JS::juice::HTMLElementList>();
  {
    assert(!v8ElementList.IsEmpty());
    
    //Retrieve the native pointer
    HTMLElementList* jsElementList = v8::juice::convert::CastFromJS<JS::juice::HTMLElementList>(v8ElementList);
    
    assert(jsElementList);
    
    //Retreive the native list, and fill it
    Core::ElementList elements;
    
    getRocket()->GetElementsByTagName(elements, tagname);
    
    *jsElementList = HTMLElementList(elements);
  }
  return handle_scope.Close(v8ElementList);
}


void HTMLDocument::write(const Core::String& tagname)
{
  v8::HandleScope handle_scope;
  
  throw std::runtime_error("IMPLEMENT THIS!!");
  
  // return handle_scope.Close();
}

void HTMLDocument::writeln(const Core::String& tagname)
{
  v8::HandleScope handle_scope;
  
  throw std::runtime_error("IMPLEMENT THIS!!");
  
  // return handle_scope.Close();
}

HTMLDocument::RElementT* HTMLDocument::getRocket(){
  return &(*document);
}

} } } }//namespaces Rocket::Core::JS::juice

#endif
