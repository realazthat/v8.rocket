#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLINPUTELEMENT_CPP
#define ROCKET_CORE_JS_DETAIL_V8_HTMLINPUTELEMENT_CPP


#include <Rocket/Core/JS/detail/v8/HTMLTextAreaElement.h>

#include <v8.h>

namespace Rocket{ namespace Core{ namespace JS{ namespace juice{


HTMLTextAreaElement::CW&
HTMLTextAreaElement::getCW() {
  CW & cw( CW::Instance() );
  
  if( cw.IsSealed() )
  {
      return cw;
  }
  
  //HTMLFormControlTemplate
  cw.Inherit(super::getCW());
  
  // cw.BindGetterSetter<Core::String,
             // &super::name,
             // void,const Core::String&,&super::name>
             // ( "name");

  
  cw.Seal(); // ends the binding process
  
  return cw;
}

HTMLTextAreaElement::HTMLTextAreaElement()
  : super()
{}


HTMLTextAreaElement::HTMLTextAreaElement(RElementT* element_)
  : super(element_)
{}


HTMLTextAreaElement& HTMLTextAreaElement::operator=(const HTMLTextAreaElement& other){
  super::operator=(other);
  
  return *this;
}





} } } }//namespaces Rocket::Core::JS::juice

#endif
