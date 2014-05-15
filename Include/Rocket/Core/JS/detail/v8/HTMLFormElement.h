#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLEFORMELEMENT_H
#define ROCKET_CORE_JS_DETAIL_V8_HTMLEFORMELEMENT_H

#include <Rocket/Core.h>
#include <Rocket/Controls.h>

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
struct HTMLFormElement : public HTMLElementTemplate<Controls::ElementForm>{
  typedef Controls::ElementForm RElementT;
  typedef HTMLElementTemplate<RElementT> super;
  typedef HTMLFormElement self_type;
public:
  explicit HTMLFormElement();
  explicit HTMLFormElement(RElementT* element_);
  self_type& operator=(const self_type& other);
public:
//RO properties
  virtual int length();
public:
//Getters/Setters
  virtual Core::String name();
  virtual void name(const Core::String& n);

  virtual Core::String method();
  virtual void method(const Core::String& m);
public:
  virtual void submit();
  virtual void reset();
public:
  typedef v8::juice::cw::ClassWrap<self_type> CW;

  static CW& getCW();
private:
  friend class v8::juice::cw::WeakWrap<self_type>;
};

} } } }//namespaces Rocket::Core::JS::juice


#include <Rocket/Core/JS/detail/v8/glue/HTMLFormElement.h>

#endif
