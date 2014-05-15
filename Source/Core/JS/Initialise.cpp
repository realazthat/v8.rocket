#ifndef ROCKET_CORE_JS_INITIALISE_CPP
#define ROCKET_CORE_JS_INITIALISE_CPP

#include <Rocket/Core.h>
#include <Rocket/Controls.h>

#include <Rocket/Core/JS/detail/rocket/ElementInstancer.h>
#include <Rocket/Core/JS/detail/rocket/EventInstancer.h>
#include <Rocket/Core/JS/detail/rocket/ElementDocumentWrapper.h>
#include <Rocket/Core/JS/detail/rocket/ElementFormControlWrapperTemplate.h>

#include <Rocket/Core/JS/detail/v8/HTMLDocument.h>
#include <Rocket/Core/JS/detail/v8/HTMLElementList.h>
#include <Rocket/Core/JS/detail/v8/Event.h>

#include <Rocket/Core/JS/detail/v8/HTMLElementBase.h>
#include <Rocket/Core/JS/detail/v8/HTMLElementGeneric.h>
#include <Rocket/Core/JS/detail/v8/HTMLFormElement.h>
#include <Rocket/Core/JS/detail/v8/HTMLInputElement.h>
#include <Rocket/Core/JS/detail/v8/HTMLTextAreaElement.h>

#include <Core/ElementTextDefault.h>
#include <Core/ElementHandle.h>
#include <Core/ElementImage.h>

namespace Rocket{ namespace Core{ namespace JS{

void Initialise() {
  {

    ///FIXME:
    // Rocket::Debugger::Initialise(boost::addressof(*htmlContext));

    using namespace Rocket;
    Core::Factory::RegisterElementInstancer("*",
      new JS::ElementInstancer<Core::Element, JS::juice::HTMLElementGeneric>)->RemoveReference();

    ///FIXME: this should not inerhit from HTMLElement, and should also expose text-specific API
    Core::Factory::RegisterElementInstancer("#root",
      new JS::ElementInstancer<Core::Element, JS::juice::HTMLElementGeneric>)->RemoveReference();

    Core::Factory::RegisterElementInstancer("#text",
      new JS::ElementInstancer<Core::ElementTextDefault, JS::juice::HTMLElementGeneric>)->RemoveReference();

    //Wrap ElementDocuments; they have to be able to retrieve the true HTMLDocument object.
    Core::Factory::RegisterElementInstancer("body",
      new JS::ElementInstancer<JS::ElementDocumentWrapper, JS::juice::HTMLElementGeneric>)->RemoveReference();

    ///FIXME: mouse handle should not inherit from HTMLElement
    Core::Factory::RegisterElementInstancer("handle",
      new JS::ElementInstancer<Core::ElementHandle, JS::juice::HTMLElementGeneric>)->RemoveReference();

    ///FIXME: Make this more specific
    Core::Factory::RegisterElementInstancer("img",
      new JS::ElementInstancer<Core::ElementImage, JS::juice::HTMLElementGeneric>)->RemoveReference();


    // Core::Factory::RegisterElementInstancer("debug-hook",
      // new JS::ElementInstancer<Debugger::ElementContextHook, JS::HTMLElementGeneric>)->RemoveReference();
    // Core::Factory::RegisterElementInstancer("debug-info",
      // new JS::ElementInstancer<Debugger::ElementInfo, JS::HTMLElementGeneric>)->RemoveReference();
    // Core::Factory::RegisterElementInstancer("debug-log",
      // new JS::ElementInstancer<Debugger::ElementLog, JS::HTMLElementGeneric>)->RemoveReference();
  }

  {
    // using namespace Rocket;

    Core::Factory::RegisterElementInstancer("form",
      new JS::ElementInstancer<Controls::ElementForm, JS::juice::HTMLFormElement>)->RemoveReference();

    {//Form Controls
      //Wrap FormControls; they are missing some functionality, which we implement in overiden functions
      typedef JS::ElementFormControlWrapperTemplate< Controls::ElementFormControlTextArea > WrappedElementFormControlTextArea;
      typedef JS::ElementFormControlWrapperTemplate< Controls::ElementFormControlInput > WrappedElementFormControlInput;
      typedef JS::ElementFormControlWrapperTemplate< Controls::ElementFormControlSelect > WrappedElementFormControlSelect;

      Core::Factory::RegisterElementInstancer("input",
        new JS::ElementInstancer< WrappedElementFormControlInput, JS::juice::HTMLInputElement>)->RemoveReference();

      Core::Factory::RegisterElementInstancer("textarea",
        new JS::ElementInstancer< WrappedElementFormControlTextArea, JS::juice::HTMLTextAreaElement>)->RemoveReference();

      Core::Factory::RegisterElementInstancer("select",
        new JS::ElementInstancer< WrappedElementFormControlSelect, JS::juice::HTMLElementGeneric>)->RemoveReference();
    }
  }

  {
    using namespace Rocket;
    Core::Factory::RegisterEventInstancer(new JS::EventInstancer<Core::Event, JS::juice::Event>)->RemoveReference();

  }
}

} } }//namespaces Rocket::Core::JS

#endif
