#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_EVENTLISTENER_H
#define ROCKET_CORE_JS_DETAIL_ROCKET_EVENTLISTENER_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/Utility.h>

#include <v8.h>

namespace Rocket{ namespace Core{ namespace JS{

struct EventListener : public Rocket::Core::EventListener{
  EventListener( v8::Handle<v8::Function> fun, v8::Handle<v8::Context> v8context )
    : fun(v8::Persistent<v8::Function>::New(fun)),
      v8context(v8::Persistent<v8::Context>::New(v8context)),
      m_element(NULL)
  {
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
  
  }
  
  ~EventListener(){
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
    assert(!fun.IsEmpty());
    
    fun.Dispose();
    fun.Clear();
    
    assert(!v8context.IsEmpty());
    
    v8context.Dispose();
    v8context.Clear();
  }

  void ProcessEvent(Core::Event& event)
  {
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
    assert(m_element);
    
    
    v8::Locker locker;
    
    v8::HandleScope handle_scope;
    
    v8::Context::Scope context_scope(getV8Context());
    
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
    v8::Handle<v8::Value> v8Event = JSRocketWrapperBase::CastToJS(&event);
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
    assert(!v8Event.IsEmpty());
    
    
    v8::Handle<v8::Value> argv[] = {
      v8Event
    };
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
    v8::Handle<v8::Object> v8element = JSRocketWrapperBase::CastToJS(m_element);
    
    assert(!v8element.IsEmpty());
    
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
    fun->Call( v8element,
      sizeof(argv)/sizeof(v8::Handle<v8::Value>),
      argv );
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
  }
  
  
  void OnAttach(Core::Element* element)
  {
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
    m_element = element;
  }
  
  void OnDetach(Core::Element* element)
  {
// std::cout << __FILE__ ": " << __LINE__ << std::endl;
    assert(m_element == element);
    
    delete this;
  }

private:
  v8::Handle<v8::Context> getV8Context() {
    return v8context;
  }

  v8::Persistent<v8::Function> fun;
  /*
   * FIXME: should v8context be persistent? Why? Would this possibly
   * make a cicular reference?
   */
  v8::Persistent<v8::Context> v8context;
  Core::Element* m_element;
};


} } }//namespaces Rocket::Core::JS




#endif
