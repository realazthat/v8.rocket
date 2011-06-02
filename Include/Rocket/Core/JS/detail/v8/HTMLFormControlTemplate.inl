#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLFORMCONTROLTEMPLATE_INL
#define ROCKET_CORE_JS_DETAIL_V8_HTMLFORMCONTROLTEMPLATE_INL


#include <Rocket/Core/JS/detail/v8/HTMLFormControlTemplate.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <v8.h>


namespace Rocket{ namespace Core{ namespace JS{ namespace juice{ 


  template<typename ElementT>
  typename HTMLFormControlTemplate<ElementT>::CW&
  HTMLFormControlTemplate<ElementT>::
  getCW()
  {
    typedef typename v8::juice::convert::MemFuncInvocationCallbackCreator<self_type> ICM;

    CW & cw( CW::Instance() );
  
    if( cw.IsSealed() )
    {
        return cw;
    }

    cw.Inherit(super::getCW());
    
    cw.template BindGetter<Core::String,
              &self_type::type>
              ("type");
             
    cw.template BindGetter<v8::Handle<v8::Value>,
              &self_type::form>
              ("form");
    
    
    
    
    

    cw.template BindGetterSetter<Core::String,
                 &self_type::name,
                 void,const Core::String&,&self_type::name>
                 ("name");
    
    cw.template BindGetterSetter<Core::String,
                 &self_type::defaultValue,
                 void,const Core::String&,&self_type::defaultValue>
                 ("defaultValue");
    
    cw.template BindGetterSetter<Core::String,
                 &self_type::value,
                 void,const Core::String&,&self_type::value>
                 ("value");
    
    cw.template BindGetterSetter<bool,
                 &self_type::disabled,
                 void,bool,&self_type::disabled>
                 ("disabled");
    
    cw.template BindGetterSetter<bool,
                 &self_type::readOnly,
                 void,bool,&self_type::readOnly>
                 ( "readOnly");
    
    cw.Seal(); // ends the binding process
  
    return cw;

  }


  template<typename ElementT>
  HTMLFormControlTemplate<ElementT>::
  HTMLFormControlTemplate()
    : super()
  {
  
  }
    
  template<typename ElementT>
  HTMLFormControlTemplate<ElementT>::
  HTMLFormControlTemplate(ElementT* element_)
    : super(element_)
  {
  
  }
  
  
  template<typename ElementT>
  HTMLFormControlTemplate<ElementT>&
  HTMLFormControlTemplate<ElementT>::operator=(const HTMLFormControlTemplate<ElementT>& other) {
    super::operator=(other);
    return *this;
  }

  


  template<typename ElementT>
  Core::String
  HTMLFormControlTemplate<ElementT>::
  type()
  {
    if (super::getRocket()->HasAttribute("type"))
      return super::getRocket()->GetAttribute("type", Core::String());
    return "text";
  }

  template<typename ElementT>
  v8::Handle<v8::Value>
  HTMLFormControlTemplate<ElementT>::
  form()
  {
    v8::HandleScope handle_scope;
    
    Core::Element* r = super::getRocket();
    
    while( r ) {
      if (r->GetTagName() == "form")
        return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(r, v8::Null()));
      r = r->GetParentNode();
    }
    
    return handle_scope.Close(v8::Null());
  }
  
  
  template<typename ElementT>
  Core::String
  HTMLFormControlTemplate<ElementT>::
  name()
  {
    return super::getRocket()->GetName();
  }

  template<typename ElementT>
  void
  HTMLFormControlTemplate<ElementT>::
  name(const Core::String& n)
  {
    return super::getRocket()->SetName(n);
  }

  template<typename ElementT>
  Core::String
  HTMLFormControlTemplate<ElementT>::
  defaultValue()
  {
    //FIXME:???????
    return super::getRocket()->GetAttribute("value", Core::String());
  }
  
  template<typename ElementT>
  void
  HTMLFormControlTemplate<ElementT>::
  defaultValue(const Core::String& v)
  {
    //FIXME: ????
    super::getRocket()->SetAttribute("value",v);
  }

  template<typename ElementT>
  Core::String
  HTMLFormControlTemplate<ElementT>::
  value()
  {
    return super::getRocket()->GetValue();
  }
  
  template<typename ElementT>
  void
  HTMLFormControlTemplate<ElementT>::
  value(const Core::String& v)
  {
    return super::getRocket()->SetValue(v);
  }

  template<typename ElementT>
  bool
  HTMLFormControlTemplate<ElementT>::
  disabled()
  {
    return super::getRocket()->IsDisabled();
  }


  template<typename ElementT>
  void
  HTMLFormControlTemplate<ElementT>::
  disabled(bool v)
  {
    return super::getRocket()->SetDisabled(v);
  }

  template<typename ElementT>
  bool
  HTMLFormControlTemplate<ElementT>::
  readOnly()
  {
    return super::getRocket()->HasAttribute("readonly");
  }
  
  template<typename ElementT>
  void
  HTMLFormControlTemplate<ElementT>::
  readOnly(bool v)
  {
    if (v)
      super::getRocket()->SetAttribute("readonly", Core::String("readonly"));
    else
      super::getRocket()->RemoveAttribute("readonly");
  }
  
  
  
  
  
  
  
  
  
  
  template<typename ElementT>
  void
  HTMLFormControlTemplate<ElementT>::
  innerHTML(const Core::String& v)
  {
    //FIXME: ??
    super::innerHTML(v);
    value(v);
  }
  
  template<typename ElementT>
  Core::String
  HTMLFormControlTemplate<ElementT>::
  innerHTML()
  {
    //FIXME: ??
    return value();
  }

  
  
  
  
  
  

} } } }//namespaces Rocket::Core::JS::juice

#endif
