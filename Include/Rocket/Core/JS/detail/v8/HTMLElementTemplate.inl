#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTTEMPLATE_INL
#define ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTTEMPLATE_INL


#include <Rocket/Core/JS/detail/v8/HTMLElementTemplate.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <v8.h>


namespace Rocket{ namespace Core{ namespace JS{ namespace juice{ 


  template<typename ElementT>
  HTMLElementTemplate<ElementT>::
  HTMLElementTemplate()
    : element(NULL)
  {
std::cout << __FILE__ ":" << __LINE__ << std::endl;
  }
    
  template<typename ElementT>
  HTMLElementTemplate<ElementT>::
  HTMLElementTemplate(ElementT* element_)
    : element(element_)
  {
    assert(element);
    element->AddReference();
  }
  
  template<typename ElementT>
  HTMLElementTemplate<ElementT>::
  ~HTMLElementTemplate(){
    assert(element);
    element->RemoveReference();
  }
  
  template<typename ElementT>
  HTMLElementTemplate<ElementT>&
  HTMLElementTemplate<ElementT>::operator=(const HTMLElementTemplate<ElementT>& other) {
    super::operator=(other);
    {
      assert(!element);
      assert(other.element);
    }
    element = other.element;
    {
      assert(element);
    }
    element->AddReference();
    
    return *this;
  }

  template<typename ElementT>
  ElementT*
  HTMLElementTemplate<ElementT>::
  getRocket() {
    assert(element);
    return element;
  }
  
} } } }//namespaces Rocket::Core::JS::juice

#endif
