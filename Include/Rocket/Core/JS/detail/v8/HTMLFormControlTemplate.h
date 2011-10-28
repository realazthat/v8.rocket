#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLFORMCONTROLTEMPLATE_H
#define ROCKET_CORE_JS_DETAIL_V8_HTMLFORMCONTROLTEMPLATE_H



#include <Rocket/Core/JS/detail/v8/HTMLElementTemplate.h>

#include <v8.h>
#include <v8/juice/ClassWrap.h>


namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

template<typename ElementT>
struct HTMLFormControlTemplate : public HTMLElementTemplate<ElementT>{
  typedef HTMLElementTemplate<ElementT> super;
  typedef HTMLFormControlTemplate self_type;

public:


public:
  //HTMLElementTemplate should be inherited. This *should* be protected,
  //but must be exposed for ClassWrap :(
  explicit HTMLFormControlTemplate();

  explicit HTMLFormControlTemplate(ElementT* element_);

  self_type& operator=(const self_type& other);
public:
//RO properties
  virtual Core::String type();
  virtual v8::Handle<v8::Value> form();
public:
//Getters/Setters
  virtual Core::String name();
  virtual void name(const Core::String& n);

  virtual Core::String defaultValue();
  virtual void defaultValue(const Core::String& v);

  virtual Core::String value();
  virtual void value(const Core::String& v);

  virtual bool disabled();
  virtual void disabled(bool v);

  virtual bool readOnly();
  virtual void readOnly(bool v);
public:
//Overrides
  //FIXME: is this wise?
  // virtual void innerHTML(const Core::String& v);
  // virtual Core::String innerHTML();
public:
  typedef v8::juice::cw::ClassWrap<self_type> CW;

  static
  CW&
  getCW();
};




} } } }//namespaces Rocket::Core::JS::juice


#include <Rocket/Core/JS/detail/v8/HTMLFormControlTemplate.inl>
// #include <Rocket/Core/JS/detail/v8/glue/HTMLFormControlTemplate.h>

#endif
