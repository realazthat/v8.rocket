#ifndef ROCKET_JS_DETAIL_GLUE_HTMLFORMCONTROLTEMPLATE_H
#define ROCKET_JS_DETAIL_GLUE_HTMLFORMCONTROLTEMPLATE_H


#include <Rocket/Core/JS/detail/v8/HTMLFormControlTemplate.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>

namespace v8{ namespace juice{
namespace cw{


  template <typename ElementT>
  struct Factory< Rocket::Core::JS::juice::HTMLFormControlTemplate<ElementT> >
      : Factory_CtorForwarder<Rocket::Core::JS::juice::HTMLFormControlTemplate<ElementT>,
                              tmp::TypeList<
          convert::CtorForwarder0<Rocket::Core::JS::juice::HTMLFormControlTemplate<ElementT>>
          >
      >
  {
  };

  template <typename ElementT>
  struct DebugLevel< Rocket::Core::JS::juice::HTMLFormControlTemplate<ElementT> > : Opt_Int<3> {};

  template <typename ElementT>
  struct ToNative_SearchPrototypesForNative< Rocket::Core::JS::juice::HTMLFormControlTemplate<ElementT> >
      : Opt_Bool<true>
  {};



}//namespace cw
} }//namespaces v8::juice


#endif
