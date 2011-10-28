#ifndef ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLEFORMELEMENT_H
#define ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLEFORMELEMENT_H

#include <Rocket/Core/JS/detail/v8/HTMLFormElement.h>

#include <Rocket/Core/JS/detail/v8/HTMLElementBase.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>

namespace v8{ namespace juice{
namespace convert{

}//namespace convert

namespace cw{


  template <>
  struct Factory<Rocket::Core::JS::juice::HTMLFormElement>
    : Factory_CtorForwarder<Rocket::Core::JS::juice::HTMLFormElement,
       tmp::TypeList< convert::CtorForwarder0<Rocket::Core::JS::juice::HTMLFormElement> >
    >
  {};

  template <> struct DebugLevel<Rocket::Core::JS::juice::HTMLFormElement>
    : Opt_Int<3> {};

  template <>
  struct ToNative_SearchPrototypesForNative<Rocket::Core::JS::juice::HTMLFormElement>
      : Opt_Bool<true>
  {};


}//namespace cw
} }//namespaces v8::juice


#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::HTMLFormElement
#define CLASSWRAP_BOUND_TYPE_NAME "HTMLFormElement"
#define CLASSWRAP_BOUND_TYPE_INHERITS Rocket::Core::JS::juice::HTMLElementBase
#include <v8/juice/ClassWrap_TwoWay.h>




#endif
