#ifndef ROCKET_CORE_JS_DETAIL_V8_CSS2PROPERTIES_CPP
#define ROCKET_CORE_JS_DETAIL_V8_CSS2PROPERTIES_CPP


#include <Rocket/Core/JS/detail/v8/CSS2Properties.h>

#include <Rocket/Core/JS/detail/v8/String.h>

#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <v8.h>

namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

CSS2Properties::CW&
CSS2Properties::getCW() {
  CW & cw( CW::Instance() );
  
  if( cw.IsSealed() )
  {
      return cw;
  }
  typedef v8::juice::convert::MemFuncInvocationCallbackCreator<self_type> ICM;  
  
  
  // cw.BindGetterSetter<Core::String,
                   // &self_type::azimuth,
                   // void,const Core::String&,&self_type::azimuth>
                   // ( "azimuth");
  
  // cw.BindGetterSetter<Core::String,
                   // &self_type::background,
                   // void,const Core::String&,&self_type::background>
                   // ( "background");
  
  // cw.BindGetterSetter<Core::String,
                   // &self_type::backgroundAttachment,
                   // void,const Core::String&,&self_type::backgroundAttachment>
                   // ( "backgroundAttachment");
  
  // cw.BindGetterSetter<Core::String,
                   // &self_type::backgroundColor,
                   // void,const Core::String&,&self_type::backgroundColor>
                   // ( "backgroundColor");
  
  // cw.BindGetterSetter<Core::String,
                   // &self_type::backgroundImage,
                   // void,const Core::String&,&self_type::backgroundImage>
                   // ( "backgroundImage");
  
  
  
  
  
  
  
  
  
  cw.BindGetterSetter<Core::String,
                   &self_type::display,
                   void,const Core::String&,&self_type::display>
                   ( "display");
  
  
  
  
  
  
  
  
  
  
  
  
  cw.BindGetterSetter<Core::String,
                   &self_type::visibility,
                   void,const Core::String&,&self_type::visibility>
                   ( "visibility");
  
  cw.Seal(); // ends the binding process
  
  return cw;
}




CSS2Properties::CSS2Properties()
{}

CSS2Properties::CSS2Properties(Core::Element* e)
  : rocket(e)
{

}


CSS2Properties::~CSS2Properties()
{}


CSS2Properties& CSS2Properties::operator=(const self_type& other)
{
  rocket = other.rocket;
  
  return *this;
}



CSS2Properties::RElement*
CSS2Properties::
getRocket()
{
  return &(*rocket);
}



const CSS2Properties::RElement*
CSS2Properties::
getRocket() const
{
  return &(*rocket);
}




void
CSS2Properties::
setProperty(const Core::String& n, const Core::String& v)
{
  if (v.Empty()) {
    getRocket()->RemoveProperty(n);
  } else {
    getRocket()->SetProperty(n, v);
  }
}



Core::String
CSS2Properties::
getProperty(const Core::String& v)
{
  const Core::Property* p = getRocket()->GetLocalProperty(v);
  
  if (p)
    return p->ToString();
  return Core::String();
}





















Core::String CSS2Properties::azimuth()
{
  return getProperty("azimuth");
}

void CSS2Properties::azimuth(const Core::String& v)
{
  setProperty("azimuth", v);
}


Core::String CSS2Properties::background()
{
  return getProperty("background");
}

void CSS2Properties::background(const Core::String& v)
{
  setProperty("background", v);
}


Core::String CSS2Properties::backgroundAttachment()
{
  return getProperty("backgroundAttachment");
}

void CSS2Properties::backgroundAttachment(const Core::String& v)
{
  setProperty("backgroundAttachment", v);
}


Core::String CSS2Properties::backgroundColor()
{
  return getProperty("backgroundColor");
}

void CSS2Properties::backgroundColor(const Core::String& v)
{
  setProperty("backgroundColor", v);
}


Core::String CSS2Properties::backgroundImage()
{
  return getProperty("backgroundImage");
}

void CSS2Properties::backgroundImage(const Core::String& v)
{
  setProperty("backgroundImage", v);
}

























Core::String CSS2Properties::display()
{
  return getProperty("display");
}


void CSS2Properties::display(const Core::String& v)
{
  setProperty("display", v);
}






Core::String CSS2Properties::visibility()
{
  return getProperty("visibility");
}

void CSS2Properties::visibility(const Core::String& v)
{
  setProperty("visibility", v);
}


} } } }//namespaces Rocket::Core::JS::juice

#endif
