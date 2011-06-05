#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_ROCKETWRAPPERINTERFACE_H
#define ROCKET_CORE_JS_DETAIL_ROCKET_ROCKETWRAPPERINTERFACE_H


#include <Rocket/Core.h>

#include <v8.h>

#include <assert.h>

namespace Rocket{ namespace Core{ namespace JS{

/**
 * This abstract interface allows one to obtain the v8::Handle of
 * a Rocket element that is of any concrete type based on the template
 * RocketWrapper<>. Thus, any object that is actually of any RocketWrapper
 * type, produce its handle via this interface.
 *
 */
struct RocketWrapperInterface{
  
  virtual ~RocketWrapperInterface(){}
  
  /**
   * Abstract, implemented in RocketWrapper.
   */
  virtual v8::Handle<v8::Object> getV8InterfaceHandle() = 0;
  
  
  /**
   * Utility function to convert any Core::ScriptInterface pointer, to a v8:Handle.
   * The pointer returned from Core::ScriptInterface::GetScriptObject()
   * must be of type RocketWrapperInterface.
   *
   * RocketWrapper, implements both Core::ScriptInterface, and RocketWrapperInterface.
   */
  static
  v8::Handle<v8::Object>
  CastToJS(const Core::ScriptInterface* e) {
    assert(e);
    
    Core::ScriptObject object = e->GetScriptObject();
    
    assert(object);
    RocketWrapperInterface* jsBase = reinterpret_cast<RocketWrapperInterface*>(object);
    
    assert(jsBase);
    
    v8::HandleScope handle_scope;
    v8::Handle<v8::Object> h = jsBase->getV8InterfaceHandle();
    
    return handle_scope.Close(h);
  }
};

} } }//namespaces Rocket::Core::JS

#endif
