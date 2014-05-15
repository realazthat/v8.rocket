#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLTEXTAREAELEMENT_H
#define ROCKET_CORE_JS_DETAIL_V8_HTMLTEXTAREAELEMENT_H


#include <Rocket/Controls.h>

#include <Rocket/Core/JS/detail/v8/HTMLFormControlTemplate.h>

#include <v8.h>
#include <v8/juice/ClassWrap.h>


namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

struct HTMLTextAreaElement : public HTMLFormControlTemplate<Controls::ElementFormControlTextArea>
{
  typedef Controls::ElementFormControlTextArea RElementT;
  typedef HTMLTextAreaElement self_type;
  typedef HTMLFormControlTemplate<RElementT> super;
public:
  explicit HTMLTextAreaElement();

  explicit HTMLTextAreaElement(RElementT* element_);

  self_type& operator=(const self_type& other);
public:
  typedef v8::juice::cw::ClassWrap<self_type> CW;

  static
  CW&
  getCW();
};

} } } }//namespaces Rocket::Core::JS::juice

#include <Rocket/Core/JS/detail/v8/glue/HTMLTextAreaElement.h>

#endif
