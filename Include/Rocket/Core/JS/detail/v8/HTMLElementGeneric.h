#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTGENERIC_H
#define ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTGENERIC_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/detail/v8/HTMLElementTemplate.h>
#include <Rocket/Core/JS/detail/v8/String.h>

#include <v8/juice/ClassWrap.h>
#include <v8.h>



namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

/**
 * This is a generic HTMLElement implementation, representing a
 * Core::Element.
 *
 * It will not expose anything to v8, more than what HTMLElement itself exposes,
 * thus if it a derivation of Core::Element, consider using a more specialized
 * derivation of HTMLElementBase.
 */
struct HTMLElementGeneric : public HTMLElementTemplate<Core::Element>{
  typedef Core::Element RElementT;
  typedef HTMLElementTemplate<RElementT> super;
  typedef HTMLElementGeneric self_type;
public:
  explicit HTMLElementGeneric();
  explicit HTMLElementGeneric(RElementT* element_);
  self_type& operator=(const self_type& other);
public:
  typedef v8::juice::cw::ClassWrap<self_type> CW;

  static CW& getCW();
private:
  friend class v8::juice::cw::WeakWrap<self_type>;
};

} } } }//namespaces Rocket::Core::JS::juice


#include <Rocket/Core/JS/detail/v8/glue/HTMLElementGeneric.h>

#endif
