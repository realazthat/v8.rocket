#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTLIST_H
#define ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTLIST_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/detail/v8/String.h>

#include <v8/juice/ClassWrap.h>
#include <v8.h>



namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

struct HTMLElementList{
  explicit HTMLElementList();
  
  explicit HTMLElementList(const Core::ElementList& rawElements);
  
  virtual ~HTMLElementList();
  
  HTMLElementList& operator=(const HTMLElementList& other);
public:
  ///JS getters
  Core::ElementList::size_type length() const;
public:
  v8::Handle<v8::Value> item(Core::ElementList::size_type index);
public:
  typedef v8::juice::cw::ClassWrap<HTMLElementList> CW;
  
  static CW& getCW();
private:

  friend class v8::juice::cw::WeakWrap<HTMLElementList>;
  std::vector< Core::ElementReference > elements;
};

} } } }//namespaces Rocket::Core::JS::juice



#include <Rocket/Core/JS/detail/v8/glue/HTMLElementList.h>

#endif
