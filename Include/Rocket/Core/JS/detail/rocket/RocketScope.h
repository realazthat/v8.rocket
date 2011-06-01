#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_ROCKETSCOPE_H
#define ROCKET_CORE_JS_DETAIL_ROCKET_ROCKETSCOPE_H

#include <cassert>

namespace Rocket{ namespace Core{ namespace JS{

/**
 * A utility class to perform RIIA for Core::ReferenceCountable types.
 */
template<typename RefT>
struct RocketScope{

  
  RocketScope(RefT* ref)
    : ref(ref)
  {
    aquire();
  }



  RocketScope(const RocketScope& other)
    : ref(other.ref)
  {
    aquire();
  }
  
  explicit RocketScope()
    : ref(NULL)
  {}
  
  RocketScope& operator=(const RocketScope& other) {
    if (ref == other.ref)
      return *this;
    
    ///Make certain we don't go down to zero refs,
    /// in case we are assigning to one's self
    RocketScope tmp(other);
    
    release();
    
    ref = other.ref;
    
    aquire();
    
    return *this;
  }
  
  ~RocketScope(){
    release();
  }
  
  RefT* get(){
    return ref;
  }
  
  const RefT* get() const{
    return ref;
  }
  
  RefT& operator*(){
    assert(ref != NULL);
    return *ref;
  }
  
  const RefT& operator*() const{
    assert(ref != NULL);
    return *ref;
  }
  
  RefT* operator->(){
    assert(ref != NULL);
    return ref;
  }
  
  const RefT* operator->() const{
    assert(ref != NULL);
    return ref;
  }
  
  
  template<typename ParentT>
  operator RocketScope<ParentT>() const{
    return RocketScope<ParentT>(ref);
  }
  
  operator bool(){
    return ref != NULL;
  }
  
  template<typename U>
  friend struct RocketScope;
protected:
  void release(){
    if (ref)
      ref->RemoveReference();
    ref = NULL;
  }
  
  void aquire(){
    if (ref)
      ref->AddReference();
  }
private:
  RefT* ref;
};

} } }//namespaces Rocket::JS::Core

#endif
