#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLFORMELEMENT_CPP
#define ROCKET_CORE_JS_DETAIL_V8_HTMLFORMELEMENT_CPP


#include <Rocket/Core/JS/detail/v8/HTMLFormElement.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <v8.h>


namespace Rocket{ namespace Core{ namespace JS{ namespace juice{


HTMLFormElement::CW&
HTMLFormElement::getCW() {
  typedef typename v8::juice::convert::MemFuncInvocationCallbackCreator<self_type> ICM;

  CW & cw( CW::Instance() );

  if( cw.IsSealed() )
  {
      return cw;
  }

  cw.Inherit(super::getCW());

  cw.BindGetter<int,
            &self_type::length>
            ("length");





  cw.BindGetterSetter<Core::String,
                   &self_type::name,
                   void, const Core::String&,&self_type::name>
                   ( "name");

  cw.BindGetterSetter<Core::String,
                   &self_type::method,
                   void, const Core::String&,&self_type::method>
                   ( "method");



  cw.Set( "submit", ICM::M0::Invocable<void,&self_type::submit>);
  cw.Set( "reset", ICM::M0::Invocable<void,&self_type::reset>);


  cw.Seal(); // ends the binding process

  return cw;
}

HTMLFormElement::HTMLFormElement()
  : super()
{}


HTMLFormElement::HTMLFormElement(RElementT* element_)
  : super(element_)
{}


HTMLFormElement& HTMLFormElement::operator=(const self_type& other){
  super::operator=(other);

  return *this;
}

int
HTMLFormElement::
length()
{
  throw std::runtime_error("HTMLFormElement::length(): Not implemented");
  return 0;
}

Core::String
HTMLFormElement::
name()
{
  return getRocket()->GetAttribute("name", Core::String());
}

void
HTMLFormElement::
name(const Core::String& n)
{
  getRocket()->SetAttribute("name", n);
}

Core::String
HTMLFormElement::
method()
{
  return getRocket()->GetAttribute("method", Core::String());
}

void
HTMLFormElement::
method(const Core::String& m)
{
  //FIXME: method can only be set to valid methods
  getRocket()->SetAttribute("method", m);
}


void
HTMLFormElement::
submit()
{
  //FIXME:??
  getRocket()->Submit();
}

void
HTMLFormElement::
reset()
{
  //FIXME: iterate through all the formcontrols, and reset their values to initial.
  throw std::runtime_error("HTMLFormElement::reset(): Not implemented");
}


} } } }//namespaces Rocket::Core::JS::juice

#endif
