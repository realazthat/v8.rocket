#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_ROCKETWRAPPER_H
#define ROCKET_CORE_JS_DETAIL_ROCKET_ROCKETWRAPPER_H

#include <Rocket/Core/JS/detail/rocket/RocketWrapperInterface.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

namespace Rocket{ namespace Core{ namespace JS{

/**
 * Generic wrapper for all Rocket::Core::ReferenceCountable classes.
 *
 * The main point of this class, is to generate a v8::Handle to to this
 * object on demand. It is a generic template, and inherits from RocketT.
 * It also implements the RocketWrapperInterface.
 *
 * JSInterfaceT should be a type that can be constructed via
 * JS::create(RocketT*).
 */
template<typename RocketT, typename JSInterfaceT>
struct RocketWrapper : public RocketT, public RocketWrapperInterface{
  ///default ctor
  RocketWrapper()
    : RocketT(){}
  
  ///passthrough ctor
  template<typename A1>
  RocketWrapper(const A1& arg1)
    : RocketT(arg1){}
  
  ///passthrough ctor
  template<typename A1, typename A2>
  RocketWrapper(const A1& arg1, const A2& arg2)
    : RocketT(arg1, arg2){}
  
  ///passthrough ctor
  template<typename A1, typename A2, typename A3>
  RocketWrapper(const A1& arg1, const A2& arg2, const A3& arg3)
    : RocketT(arg1, arg2, arg3){}
  
  ///passthrough ctor
  template<typename A1, typename A2, typename A3, typename A4>
  RocketWrapper(const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4)
    : RocketT(arg1, arg2, arg3, arg4){}
  
  /**
   * Returns a pointer to its RocketWrapperInterface.
   */
  virtual Core::ScriptObject GetScriptObject() const{
    const RocketWrapperInterface* base = static_cast<const RocketWrapperInterface*>(this);
    
    return const_cast<void*>(reinterpret_cast<const void*>(base));
  }
  
  /**
   * Implements getJSInterfaceHandle(); returns a v8::Handle for this object.
   */
  v8::Handle<v8::Object> getJSInterfaceHandle() {
    v8::HandleScope handle_scope;

    //FIXME: we should be creating it once, and using a weak pointer to keep track of it
    v8::Handle<v8::Object> v8InterfaceStrong = JS::juice::create<JSInterfaceT>(this);
    assert(!v8InterfaceStrong.IsEmpty());
    
    // v8Interface.MakeWeak(NULL, NULL);
    return handle_scope.Close(v8InterfaceStrong);
  }
  
private:
  // v8::Persistent<v8::Object> v8Interface;
};


} } }//namespaces Rocket::Core::JS

#endif
