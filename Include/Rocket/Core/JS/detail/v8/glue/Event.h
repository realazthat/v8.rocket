#ifndef ROCKET_CORE_JS_DETAIL_V8_GLUE_EVENT_H
#define ROCKET_CORE_JS_DETAIL_V8_GLUE_EVENT_H


#include <Rocket/Core/JS/detail/v8/Event.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>

namespace v8{ namespace juice{
namespace cw{


  template <>
  struct Factory<Rocket::Core::JS::juice::Event>
    : Factory_CtorForwarder<Rocket::Core::JS::juice::Event,
       tmp::TypeList< convert::CtorForwarder0<Rocket::Core::JS::juice::Event> >
    >
  {};
  
  template <> struct DebugLevel<Rocket::Core::JS::juice::Event>
    : Opt_Int<3> {};
  
  template <>
  struct ToNative_SearchPrototypesForNative<Rocket::Core::JS::juice::Event>
      : Opt_Bool<true>
  {};
  

}//namespace cw
} }//namespaces v8::juice


#define CLASSWRAP_BOUND_TYPE Rocket::Core::JS::juice::Event
#define CLASSWRAP_BOUND_TYPE_NAME "Event"
#include <v8/juice/ClassWrap_TwoWay.h>




#endif
