#ifndef ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLINPUTELEMENT_H
#define ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLINPUTELEMENT_H

#include <Rocket/Core/JS/detail/v8/HTMLInputElement.h>

#include <Rocket/Core/JS/detail/v8/HTMLElementBase.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>

namespace v8{ namespace juice{
namespace convert{

}//namespace convert

namespace cw{


  template <>
  struct Factory<Rocket::Core::JS::juice::HTMLInputElement>
    : Factory_CtorForwarder<Rocket::Core::JS::juice::HTMLInputElement,
       tmp::TypeList< convert::CtorForwarder0<Rocket::Core::JS::juice::HTMLInputElement> >
    >
  {};

  template <> struct DebugLevel<Rocket::Core::JS::juice::HTMLInputElement>
    : Opt_Int<3> {};

  template <>
  struct ToNative_SearchPrototypesForNative<Rocket::Core::JS::juice::HTMLInputElement>
      : Opt_Bool<true>
  {};



  template <>
  struct Factory< Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlInput> >
      : Factory_CtorForwarder<Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlInput>,
                              tmp::TypeList<
          convert::CtorForwarder0<Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlInput> >
          >
      >
  {
  };

  template <>
  struct DebugLevel< Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlInput> > : Opt_Int<3> {};

  template <>
  struct ToNative_SearchPrototypesForNative< Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlInput> >
      : Opt_Bool<true>
  {};


}//namespace cw
} }//namespaces v8::juice



#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlInput>
#define CLASSWRAP_BOUND_TYPE_NAME "HTMLFormControlTemplate_ElementFormControlInput"
#define CLASSWRAP_BOUND_TYPE_INHERITS Rocket::Core::JS::juice::HTMLElementBase
#include <v8/juice/ClassWrap_TwoWay.h>


#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::HTMLInputElement
#define CLASSWRAP_BOUND_TYPE_NAME "HTMLInputElement"
#define CLASSWRAP_BOUND_TYPE_INHERITS Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlInput>
#include <v8/juice/ClassWrap_TwoWay.h>




#endif
