#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTFORMCONTROLWRAPPERTEMPLATE_H
#define ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTFORMCONTROLWRAPPERTEMPLATE_H

#include <Rocket/Core.h>


namespace Rocket{ namespace Core { namespace JS{

/**
 */
template<typename ElementFormControlT>
struct ElementFormControlWrapperTemplate : public ElementFormControlT
{
  typedef ElementFormControlT super;
  typedef ElementDocumentWrapper self_type;

  ElementFormControlWrapperTemplate(const Core::String& tag);
protected:

virtual void OnChildAdd(Rocket::Core::Element *child);

virtual void setValueFromInnerText();

};

} } }//namespaces Rocket::Core::JS

#include <Rocket/Core/JS/detail/rocket/ElementFormControlWrapperTemplate.inl>

#endif
