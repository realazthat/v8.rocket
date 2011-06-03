#ifndef ROCKET_CORE_JS_DETAIL_V8_GLUE_CSS2PROPERTIES_H
#define ROCKET_CORE_JS_DETAIL_V8_GLUE_CSS2PROPERTIES_H

#include <Rocket/Core/JS/detail/v8/CSS2Properties.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>

namespace v8{ namespace juice{
namespace convert{

}//namespace convert

namespace cw{


  template <>
  struct Factory<Rocket::Core::JS::juice::CSS2Properties>
    : Factory_CtorForwarder<Rocket::Core::JS::juice::CSS2Properties,
       tmp::TypeList< convert::CtorForwarder0<Rocket::Core::JS::juice::CSS2Properties> >
    >
  {};
  
  template <> struct DebugLevel<Rocket::Core::JS::juice::CSS2Properties>
    : Opt_Int<3> {};
  
  template <>
  struct ToNative_SearchPrototypesForNative<Rocket::Core::JS::juice::CSS2Properties>
      : Opt_Bool<true>
  {};
  


}//namespace cw
} }//namespaces v8::juice




#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::CSS2Properties
#define CLASSWRAP_BOUND_TYPE_NAME "CSS2Properties"
#include <v8/juice/ClassWrap_TwoWay.h>




#endif
