#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTLIST_CPP
#define ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTLIST_CPP


#include <Rocket/Core/JS/detail/v8/HTMLElementList.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <v8.h>

namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

HTMLElementList::CW&
HTMLElementList::getCW() {
  CW & cw( CW::Instance() );
  
  if( cw.IsSealed() )
  {
      return cw;
  }
  typedef v8::juice::convert::MemFuncInvocationCallbackCreator<HTMLElementList> ICM;

  cw.BindGetter<Core::ElementList::size_type,&HTMLElementList::length>( "length" );

  cw.Set( "item", ICM::M1::Invocable<v8::Handle<v8::Value>, Core::ElementList::size_type, &HTMLElementList::item>);
  
  cw.Seal(); // ends the binding process
  
  return cw;
}




HTMLElementList::HTMLElementList()
{}

HTMLElementList::HTMLElementList(const Core::ElementList& rawElements)
  : elements(rawElements.begin(), rawElements.end())
{

}


HTMLElementList::~HTMLElementList()
{}


HTMLElementList& HTMLElementList::operator=(const HTMLElementList& other)
{
  elements = other.elements;
  
  return *this;
}











Core::ElementList::size_type
HTMLElementList::
length() const
{
  return elements.size();
}

v8::Handle<v8::Value>
HTMLElementList::item(Core::ElementList::size_type index)
{

  v8::HandleScope handle_scope;
  
  if ( index < elements.size() ) {
    Core::Element* element = *elements[index];
    return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(element, v8::Null()));
  }

  return handle_scope.Close(v8::Null());;
}


} } } }//namespaces Rocket::Core::JS::juice

#endif
