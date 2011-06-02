#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLDOCUMENT_H
#define ROCKET_CORE_JS_DETAIL_V8_HTMLDOCUMENT_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/detail/v8/String.h>

#include <v8/juice/ClassWrap.h>
#include <v8.h>


#include <Rocket/Core/JS/detail/rocket/RocketScope.h>

namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

struct HTMLDocument{
  typedef HTMLDocument self_type;
  typedef Core::ElementDocument RElementT;

public:
  explicit HTMLDocument();
  explicit HTMLDocument(RElementT* element_);
  self_type& operator=(const self_type& other);
public:
  //RO properties
  virtual v8::Handle<v8::Value> documentElement();
  virtual v8::Handle<v8::Value> body();
public:
  virtual v8::Handle<v8::Value> createComment(const Core::String& comment);
  virtual v8::Handle<v8::Value> createElement(const Core::String& tag);
  virtual v8::Handle<v8::Value> createDocumentFragment();
  virtual v8::Handle<v8::Value> createTextNode(const Core::String& text);
  virtual v8::Handle<v8::Value>	getElementById(const Core::String& elementId);
  virtual v8::Handle<v8::Value>	getElementsByTagName(const Core::String& tagname);
  virtual void write(const Core::String& html);
  virtual void writeln(const Core::String& html);
public:
  typedef v8::juice::cw::ClassWrap<self_type> CW;
  
  static CW& getCW();
protected:
  virtual RElementT* getRocket();
private:
  friend class v8::juice::cw::WeakWrap<self_type>;
  RocketScope<RElementT> document;
};

} } } }//namespaces Rocket::Core::JS::juice


#include <Rocket/Core/JS/detail/v8/glue/HTMLDocument.h>

#endif
