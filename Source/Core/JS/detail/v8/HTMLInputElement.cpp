#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLINPUTELEMENT_CPP
#define ROCKET_CORE_JS_DETAIL_V8_HTMLINPUTELEMENT_CPP


#include <Rocket/Core/JS/detail/v8/HTMLInputElement.h>

#include <v8.h>

namespace Rocket{ namespace Core{ namespace JS{ namespace juice{


HTMLInputElement::CW&
HTMLInputElement::getCW() {
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

HTMLInputElement::HTMLInputElement()
  : super()
{}


HTMLInputElement::HTMLInputElement(RElementT* element_)
  : super(element_)
{}


HTMLInputElement& HTMLInputElement::operator=(const HTMLInputElement& other){
  super::operator=(other);
  
  return *this;
}





} } } }//namespaces Rocket::Core::JS::juice

#endif
