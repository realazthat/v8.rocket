#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTGENERIC_CPP
#define ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTGENERIC_CPP


#include <Rocket/Core/JS/detail/v8/HTMLElementGeneric.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <v8.h>


namespace Rocket{ namespace Core{ namespace JS{ namespace juice{


HTMLElementGeneric::CW&
HTMLElementGeneric::getCW() {
  CW & cw( CW::Instance() );

  if( cw.IsSealed() )
  {
      return cw;
  }

  cw.Inherit(super::getCW());

  cw.Seal(); // ends the binding process

  return cw;
}

HTMLElementGeneric::HTMLElementGeneric()
  : super()
{}


HTMLElementGeneric::HTMLElementGeneric(HTMLElementGeneric::RElementT* element_)
  : super(element_)
{}


HTMLElementGeneric& HTMLElementGeneric::operator=(const HTMLElementGeneric& other){
  super::operator=(other);

  return *this;
}

} } } }//namespaces Rocket::Core::JS::juice

#endif
