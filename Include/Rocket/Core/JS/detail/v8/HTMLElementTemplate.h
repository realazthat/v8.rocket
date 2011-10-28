#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTTEMPLATE_H
#define ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTTEMPLATE_H


#include <Rocket/Core/JS/detail/v8/HTMLElementBase.h>

#include <v8.h>
#include <v8/juice/ClassWrap.h>



namespace Rocket{ namespace Core{ namespace JS{ namespace juice{


template<typename ElementT>
struct HTMLElementTemplate : public HTMLElementBase{
  typedef HTMLElementBase super;
  typedef HTMLElementTemplate self_type;

public:

  ~HTMLElementTemplate();
  virtual ElementT* getRocket();

protected:
  //HTMLElementTemplate should be inherited.
  explicit HTMLElementTemplate();

  explicit HTMLElementTemplate(ElementT* element_);

  self_type& operator=(const self_type& other);
private:
  ElementT* element;
};

} } } }//namespaces Rocket::Core::JS::juice


#include <Rocket/Core/JS/detail/v8/HTMLElementTemplate.inl>

#endif
