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
 * V8InterfaceT should be a type that can be constructed via
 * JS::juice::create(RocketT*).
 */
template<typename RocketT, typename V8InterfaceT>
struct RocketWrapper : public RocketT, public RocketWrapperInterface{
  typedef RocketWrapper self_type;
  typedef RocketT super;

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
  
  ~RocketWrapper(){
    assert(v8Interface.IsEmpty());
  }
  
  /**
   * Returns a pointer to its RocketWrapperInterface.
   */
  virtual Core::ScriptObject GetScriptObject() const{
    const RocketWrapperInterface* base = static_cast<const RocketWrapperInterface*>(this);
    
    return const_cast<void*>(reinterpret_cast<const void*>(base));
  }
  
  /**
   * Implements getV8InterfaceHandle(); returns a v8::Handle for this object.
   */
  v8::Handle<v8::Object> getV8InterfaceHandle() {
    v8::HandleScope handle_scope;

    if (v8Interface.IsEmpty()) {
      //This is the first time a v8-interface was requested.
      
      //Create a new v8-interface object
      v8Interface = v8::Persistent<v8::Object>::New(JS::juice::create<V8InterfaceT>(this));
      
      //Obtain a stack based ref, to return to v8
      v8::Local<v8::Object> v8InterfaceStrong = v8::Local<v8::Object>::New(v8Interface);
      
      //Make our ref into a weak ref; inform us when there is no longer any ref in v8
      v8Interface.MakeWeak(reinterpret_cast<void*>(this), &self_type::weak_callback);
      
      assert(v8Interface.IsWeak());

      //Return a copy of the stack based ref
      return handle_scope.Close(v8InterfaceStrong);
    } else if ( v8Interface.IsWeak() ) {
      //A v8-interface was already created, *and* there exists a ref to it in v8
      
      assert(v8Interface.IsWeak());
      
      v8Interface.ClearWeak();

      v8::Local<v8::Object> v8InterfaceStrong = v8::Local<v8::Object>::New(v8Interface);

      v8Interface.MakeWeak(reinterpret_cast<void*>(this), &self_type::weak_callback);
      
      assert(v8Interface.IsWeak());

      return handle_scope.Close(v8InterfaceStrong);
    } else {
      v8::Local<v8::Object> v8InterfaceStrong = v8::Local<v8::Object>::New(v8Interface);

      v8Interface.MakeWeak(reinterpret_cast<void*>(this), &self_type::weak_callback);
      
      assert(v8Interface.IsWeak());
    
      return handle_scope.Close(v8InterfaceStrong);
    }
  }
  
  static void weak_callback(v8::Persistent<v8::Value> object, void* p)
  {
    
    
    assert(p);
    self_type& self = *reinterpret_cast<self_type*>(p);
    v8::Persistent<v8::Object>& v8Interface = self.v8Interface;
    
    assert(object.IsNearDeath());
    // assert(object.IsWeak());
    // assert(v8Interface.IsWeak());
    assert(v8Interface.IsNearDeath());
    
    
    
    if (self.GetReferenceCount() == 1) {
      v8Interface.Clear();
      
      object.ClearWeak();
      object.Dispose();
      object.Clear();
    } else {
      object.ClearWeak();
      v8Interface = v8::Persistent<v8::Object>::New(v8Interface);
      
      object.Dispose();
      object.Clear();
      
      assert(!v8Interface.IsWeak());
      assert(!v8Interface.IsNearDeath());
    }
  }

  virtual void RemoveReference() {
    
    if ( v8Interface.IsEmpty() ) {
      //The v8-interface was never created
      
      //Do nothing.
      
      //Pass through.
      super::RemoveReference();
    } else if ( v8Interface.IsWeak() ) {
      //A v8-interface was created, and our reference to the v8-interface is weak.
      //This means that there exists another v8 ref to the v8-interface, that is held in the v8 context.
      
      //A reference other than the one that exists in the v8 context is being removed.
      //Thus, there must be more than one reference.
      assert(super::GetReferenceCount() > 1);
      
      //Pass through.
      super::RemoveReference();
    } else {
      //v8Interface is strong
      //This means, there is no reference to this in the v8 context, but only self referenced
      // from within this wrapper (by @c v8Interface).

      //A reference other than the one that exists in v8Interface is being removed.
      //Thus, there must be more than one reference.
      assert(super::GetReferenceCount() > 1);
      
      //Pass through.
      super::RemoveReference();

      //We can assume that "this" is still valid, since the reference count could
      // never have hit zero.
      
      //Kinda pointless, but for sanity.
      assert(super::GetReferenceCount() > 0);
      
      if ( super::GetReferenceCount() == 1 ) {
        //The only ref to this native, is from v8Interface's v8-interace object.
        
std::cout << __FILE__ ":" << __LINE__ << std::endl;
        //There is no need to keep this object around; its only reference is
        // held by v8Interface.
        v8Interface.Dispose();
std::cout << __FILE__ ":" << __LINE__ << std::endl;
        v8Interface.Clear();
std::cout << __FILE__ ":" << __LINE__ << std::endl;
      }
    }
  }
private:
  v8::Persistent<v8::Object> v8Interface;
};


} } }//namespaces Rocket::Core::JS

#endif
