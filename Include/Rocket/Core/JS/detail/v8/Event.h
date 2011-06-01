#ifndef ROCKET_CORE_JS_DETAIL_V8_EVENT_H
#define ROCKET_CORE_JS_DETAIL_V8_EVENT_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/detail/v8/String.h>

#include <v8/juice/ClassWrap.h>
#include <v8.h>


namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

struct Event{
  typedef Event self_type;
  typedef Core::Event RocketT;
public:
  Event();
  Event(RocketT* element_);
  virtual ~Event();
  
  self_type& operator=(const self_type& other);
public:
//Enumerations
  enum {
    CAPTURING_PHASE = 1,
    AT_TARGET,
    BUBBLING_PHASE
  };
public:
//Getters
  virtual bool bubbles();
  virtual bool cancelable();
  virtual v8::Handle<v8::Value> currentTarget();
  virtual int eventPhase();
  virtual v8::Handle<v8::Value> target();
  virtual Core::String type();
public:
  virtual void stopPropagation();
public:
  typedef v8::juice::cw::ClassWrap<self_type> CW;
  
  static CW& getCW();
protected:
  virtual RocketT* getRocket();
private:
  friend class v8::juice::cw::WeakWrap<self_type>;
  RocketScope<RocketT> rocket;
};

} } } }//namespaces Rocket::Core::JS::juice

#include <Rocket/Core/JS/detail/v8/glue/Event.h>

#endif
