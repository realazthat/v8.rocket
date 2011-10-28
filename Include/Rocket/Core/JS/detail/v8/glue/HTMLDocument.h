#ifndef ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLDOCUMENT_H
#define ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLDOCUMENT_H


#include <Rocket/Core/JS/detail/v8/HTMLDocument.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>

namespace v8{ namespace juice{
namespace cw{


  template <>
  struct Factory<Rocket::Core::JS::juice::HTMLDocument>
    : Factory_CtorForwarder<Rocket::Core::JS::juice::HTMLDocument,
       tmp::TypeList< convert::CtorForwarder0<Rocket::Core::JS::juice::HTMLDocument> >
    >
  {};

  template <> struct DebugLevel<Rocket::Core::JS::juice::HTMLDocument>
    : Opt_Int<3> {};

  template <>
  struct ToNative_SearchPrototypesForNative<Rocket::Core::JS::juice::HTMLDocument>
      : Opt_Bool<true>
  {};


}//namespace cw
} }//namespaces v8::juice


//Only inherits functions. Do not tell JS about native inheritance.
#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::HTMLDocument
#define CLASSWRAP_BOUND_TYPE_NAME "HTMLDocument"
#include <v8/juice/ClassWrap_TwoWay.h>




#endif
