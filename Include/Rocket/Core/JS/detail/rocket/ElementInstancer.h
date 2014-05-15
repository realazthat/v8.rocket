#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTINSTANCER_H
#define ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTINSTANCER_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/detail/rocket/RocketWrapper.h>


namespace Rocket{ namespace Core{ namespace JS{
/**
 * Element instancer that produces RocketWrapper objects.
 *
 * @param RElementT The native Rocket element type.
 * @param V8WrapperT The v8 wrapper.
 */
template<typename RElementT, typename V8WrapperT>
struct ElementInstancer : public Core::ElementInstancer{

  virtual void ReleaseElement(Core::Element* element)
  {
    delete element;
  }

  virtual void Release()
  {
    delete this;
  }

  virtual Core::Element* InstanceElement(Core::Element* parent,
    const Rocket::Core::String& tag,
    const Rocket::Core::XMLAttributes& attributes)
	{
    RocketWrapper<RElementT, V8WrapperT>* element = new RocketWrapper<RElementT, V8WrapperT>(tag);

    return element;
  }
};


} } }//namespaces Rocket::Core::JS

#endif
