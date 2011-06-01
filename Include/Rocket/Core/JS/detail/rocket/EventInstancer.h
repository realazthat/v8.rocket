#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_EVENTINSTANCER_H
#define ROCKET_CORE_JS_DETAIL_ROCKET_EVENTINSTANCER_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/detail/rocket/RocketWrapper.h>

namespace Rocket{ namespace Core{ namespace JS{
/**
 * Event instancer that produces RocketWrapper objects.
 *
 * @param REventT The native Rocket event type.
 * @param V8WrapperT The v8 wrapper.
 */

template<typename REventT, typename V8WrapperT>
struct EventInstancer : public Core::EventInstancer{

  virtual void ReleaseEvent(Core::Event* event)
  {
    delete event;
  }

  virtual void Release()
  {
    delete this;
  }

  virtual Core::Event* InstanceEvent( Core::Element * target,
    const Core::String& name,
    const Core::Dictionary& parameters,
    bool interruptible )
	{
    RocketWrapper<REventT, V8WrapperT>* event =
      new RocketWrapper<REventT, V8WrapperT>(target, name, parameters, interruptible);
    
    return event;
  }
};

} } }//namespaces Rocket::Core::JS

#endif
