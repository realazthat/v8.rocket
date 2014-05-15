#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTBASE_H
#define ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTBASE_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/detail/v8/String.h>

#include <v8.h>
#include <v8/juice/ClassWrap.h>





namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

/**
 * This is an interface for all HTMLElement v8 objects.
 */
struct HTMLElementBase{
  typedef HTMLElementBase self_type;

  explicit HTMLElementBase(){}
  virtual ~HTMLElementBase(){}
public:
  //RO properties

  virtual Core::String tagName();

  virtual v8::Handle<v8::Value> childNodes();
  virtual v8::Handle<v8::Value> firstChild();
  virtual v8::Handle<v8::Value> lastChild();
  virtual v8::Handle<v8::Value> nextSibling();
  virtual Core::String nodeName();
  virtual int nodeType();
  virtual v8::Handle<v8::Value> ownerDocument();
  virtual v8::Handle<v8::Value> parentNode();
  virtual v8::Handle<v8::Value> previousSibling();
  virtual v8::Handle<v8::Value> style();
public:
  //Getters/Setters
  virtual void id(const Core::String& rml);
  virtual const Core::String& id();

  virtual void innerHTML(const Core::String& rml);
  virtual Core::String innerHTML();

  virtual v8::Handle<v8::Value> nodeValue();
  virtual void nodeValue(const Core::String& value);


  virtual Core::String className();
  virtual void className(const Core::String& value);


public:
  virtual void addEventListener(const Core::String& type, v8::Handle<v8::Value> listener, bool useCapture);


  virtual void appendChild(self_type* nodePtr);
  virtual void blur();
  virtual void click();
  virtual v8::Handle<v8::Value> cloneNode(bool deep);
  // detachEvent(eventType, function)
  // dispatchEvent(eventObject)
  virtual void focus();
  virtual v8::Handle<v8::Value> getAttribute(const Core::String& attributeName);
  // getElementsByClassName(classes)
  virtual v8::Handle<v8::Value> getElementsByTagName(const Core::String& tagname);
  virtual v8::Handle<v8::Value> getElementById(const Core::String& id);

  virtual bool hasAttribute(const Core::String& attributename);
  // hasAtrributes()
  virtual bool hasChildNodes();

  virtual void insertBefore(self_type* newElementPtr, self_type* targetElementPtr);
  virtual void insertAfter(self_type* newElementPtr, self_type* targetElementPtr);
  virtual v8::Handle<v8::Value> item(int index);
  virtual void removeAttribute(const Core::String& attributename);
  virtual v8::Handle<v8::Value> removeChild(self_type* childreference);
  // removeEventListener(eventType, listener, useCapture)
  virtual void replaceChild(self_type* newChildPtr, self_type* oldChildPtr);
  virtual void scrollIntoView(bool top);
  virtual void scrollIntoView();
  virtual void setAttribute(const Core::String& name, const Core::String& value);
  // supports(feature, [version])


  typedef v8::juice::cw::ClassWrap<HTMLElementBase> CW;

  static
  CW&
  getCW();
protected:
  template<typename T>
  static
  v8::juice::cw::ClassWrap<T>&
  populate(v8::juice::cw::ClassWrap<T>& cw);

private:

  friend class v8::juice::cw::WeakWrap<HTMLElementBase>;
  virtual Core::Element* getRocket() {
    throw std::logic_error( "Javascript wrapping failed: Abstract class HTMLElementBase created" );
  }
};

} } } }//namespaces Rocket::Core::JS::juice

#include <Rocket/Core/JS/detail/v8/glue/HTMLElementBase.h>

#endif
