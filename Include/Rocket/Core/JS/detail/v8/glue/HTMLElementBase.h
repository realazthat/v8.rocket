#ifndef ROCKET_JS_DETAIL_GLUE_HTMLELEMENTBASE_H
#define ROCKET_JS_DETAIL_GLUE_HTMLELEMENTBASE_H


#include <Rocket/Core/JS/detail/v8/HTMLElementBase.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>

namespace v8{ namespace juice{
namespace convert{

}//namespace convert

namespace cw{

  template <>
  struct Factory<Rocket::Core::JS::juice::HTMLElementBase>
      : Factory_CtorForwarder<Rocket::Core::JS::juice::HTMLElementBase,
                              tmp::TypeList<
          convert::CtorForwarder0<Rocket::Core::JS::juice::HTMLElementBase>
          >
      >
  {
  };

  template <> struct DebugLevel<Rocket::Core::JS::juice::HTMLElementBase> : Opt_Int<3> {};
  template <>
  struct ToNative_SearchPrototypesForNative<Rocket::Core::JS::juice::HTMLElementBase>
      : Opt_Bool<true>
  {};
  

}//namespace cw
} }//namespaces v8::juice


#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::HTMLElementBase
#define CLASSWRAP_BOUND_TYPE_NAME "HTMLElement"
// #define CLASSWRAP_BOUND_TYPE_INHERITS "Node"
#include <v8/juice/ClassWrap_TwoWay.h>




#endif
