#ifndef ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLTEXTAREAELEMENT_H
#define ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLTEXTAREAELEMENT_H

#include <Rocket/Core/JS/detail/v8/HTMLTextAreaElement.h>

#include <Rocket/Core/JS/detail/v8/HTMLElementBase.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>

namespace v8{ namespace juice{
namespace convert{

}//namespace convert

namespace cw{


  template <>
  struct Factory<Rocket::Core::JS::juice::HTMLTextAreaElement>
    : Factory_CtorForwarder<Rocket::Core::JS::juice::HTMLTextAreaElement,
       tmp::TypeList< convert::CtorForwarder0<Rocket::Core::JS::juice::HTMLTextAreaElement> >
    >
  {};
  
  template <> struct DebugLevel<Rocket::Core::JS::juice::HTMLTextAreaElement>
    : Opt_Int<3> {};
  
  template <>
  struct ToNative_SearchPrototypesForNative<Rocket::Core::JS::juice::HTMLTextAreaElement>
      : Opt_Bool<true>
  {};
  

  
  template <>
  struct Factory< Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlTextArea> >
      : Factory_CtorForwarder<Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlTextArea>,
                              tmp::TypeList<
          convert::CtorForwarder0<Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlTextArea> >
          >
      >
  {
  };
  
  template <>
  struct DebugLevel< Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlTextArea> > : Opt_Int<3> {};
  
  template <>
  struct ToNative_SearchPrototypesForNative< Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlTextArea> >
      : Opt_Bool<true>
  {};
  

}//namespace cw
} }//namespaces v8::juice



#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlTextArea>
#define CLASSWRAP_BOUND_TYPE_NAME "HTMLFormControlTemplate_ElementFormControlTextArea"
#define CLASSWRAP_BOUND_TYPE_INHERITS Rocket::Core::JS::juice::HTMLElementBase
#include <v8/juice/ClassWrap_TwoWay.h>


#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::HTMLTextAreaElement
#define CLASSWRAP_BOUND_TYPE_NAME "HTMLTextAreaElement"
#define CLASSWRAP_BOUND_TYPE_INHERITS Rocket::Core::JS::juice::HTMLFormControlTemplate<Rocket::Controls::ElementFormControlTextArea>
#include <v8/juice/ClassWrap_TwoWay.h>




#endif
