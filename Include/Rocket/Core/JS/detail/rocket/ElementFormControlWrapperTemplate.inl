#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTFORMCONTROLWRAPPERTEMPLATE_INL
#define ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTFORMCONTROLWRAPPERTEMPLATE_INL

#include <Rocket/Core/JS/detail/rocket/ElementFormControlWrapperTemplate.h>
#include <Rocket/Core.h>


namespace Rocket{ namespace Core { namespace JS{


template<typename ElementFormControlT>
ElementFormControlWrapperTemplate<ElementFormControlT>::
ElementFormControlWrapperTemplate(const Core::String& tag)
  : super(tag)
{}

template<typename ElementFormControlT>
void
ElementFormControlWrapperTemplate<ElementFormControlT>::
OnChildAdd(Rocket::Core::Element *child)
{
	if (child == this) {
  } else {
    // if ( super::type != NULL ) {
      setValueFromInnerText();
    // }
  }
  super::OnChildAdd(child);
}

template<typename ElementFormControlT>
void
ElementFormControlWrapperTemplate<ElementFormControlT>::
setValueFromInnerText()
{
  //FIXME: Kludge?
  //FIXME: is this the smartest way to do this?

  Rocket::Core::String result;
  
  {
    Rocket::Core::ElementList elements;
    
    //FIXME: Must we release references for each of these?
    this->GetElementsByTagName(elements, "#text");
    
    for (Rocket::Core::ElementList::const_iterator w = elements.begin(), wend = elements.end();
      w != wend;
      ++w)
    {
      const Rocket::Core::Element* r = *w;
      assert(r);
      assert(dynamic_cast<const Rocket::Core::ElementText*>(r));
      assert(r->GetTagName() == "#text");
      
      static_cast<const Rocket::Core::ElementText*>(r)->GetText().ToUTF8(result,true);
    }
  }
  
  this->SetValue(result);
}

} } }//namespaces Rocket::Core::JS


#endif
