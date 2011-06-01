#ifndef ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLELEMENTLIST_HPP
#define ROCKET_CORE_JS_DETAIL_V8_GLUE_HTMLELEMENTLIST_HPP


#include <Rocket/Core/JS/detail/v8/HTMLElementBase.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>

namespace v8{ namespace juice{
namespace cw{


  template <>
  struct Factory<Rocket::Core::JS::juice::HTMLElementList>
      : Factory_CtorForwarder<Rocket::Core::JS::juice::HTMLElementList,
                              tmp::TypeList<
          convert::CtorForwarder0<Rocket::Core::JS::juice::HTMLElementList>
          >
      >
  {
  };
  
  template <> struct DebugLevel<Rocket::Core::JS::juice::HTMLElementList> : Opt_Int<3> {};
  template <>
  struct ToNative_SearchPrototypesForNative<Rocket::Core::JS::juice::HTMLElementList>
      : Opt_Bool<true>
  {};
  

}//namespace cw
} }//namespaces v8::juice


#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::HTMLElementList
#define CLASSWRAP_BOUND_TYPE_NAME "HTMLElementList"
// #define CLASSWRAP_BOUND_TYPE_INHERITS "Element"
#include <v8/juice/ClassWrap_TwoWay.h>




#endif
