#ifndef ROCKET_CORE_JS_DETAIL_V8_EVENT_CPP
#define ROCKET_CORE_JS_DETAIL_V8_EVENT_CPP


#include <Rocket/Core/JS/detail/v8/Event.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <v8.h>

#include <stdexcept>


namespace Rocket{ namespace Core{ namespace JS{ namespace juice{


Event::CW&
Event::getCW() {
  typedef typename v8::juice::convert::MemFuncInvocationCallbackCreator<Event> ICM;
  CW & cw( CW::Instance() );
  
  if( cw.IsSealed() )
  {
      return cw;
  }
  
  cw.BindGetter<bool,&Event::bubbles>( "bubbles" );
  cw.BindGetter<bool,&Event::cancelable>( "cancelable" );
  cw.BindGetter<v8::Handle<v8::Value>,&Event::currentTarget>( "currentTarget" );
  ///FIXME: bind CAPTURING_PHASE etc. enumerations
  cw.BindGetter<int,&Event::eventPhase>( "eventPhase" );
  cw.BindGetter<v8::Handle<v8::Value>,&Event::target>( "target" );
  cw.BindGetter<Core::String,&Event::type>( "type" );
  
  cw.Set( "stopPropagation", ICM::M0::Invocable<void, &Event::stopPropagation>);

  
  cw.Seal(); // ends the binding process
  
  return cw;
}


Event::Event()
  : rocket(NULL)
{
}

Event::~Event()
{
  assert(rocket);
}


Event::Event(Event::RocketT* rocket)
  : rocket(rocket)
{
  assert(rocket);
}

Event::self_type&
Event::operator=(const Event::self_type& other) {
  assert(!rocket);
  rocket = other.rocket;
  return *this;
}

Event::RocketT*
Event::getRocket() {
  return &(*rocket);
}

bool
Event::bubbles() {
  //FIXME: ??
  return getRocket()->GetPhase() == RocketT::PHASE_BUBBLE;
}

bool
Event::cancelable() {
  //FIXME: ?? I don't know how to "cancel" a rocket event
  return false;
}

v8::Handle<v8::Value>
Event::currentTarget() {
  v8::HandleScope handle_scope;
  return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetCurrentElement(), v8::Null()));
}

int
Event::eventPhase() {
  switch( getRocket()->GetPhase() ) {
    case ( RocketT::PHASE_CAPTURE ):
      return CAPTURING_PHASE;
    case ( RocketT::PHASE_TARGET ):
      return AT_TARGET;
    case ( RocketT::PHASE_BUBBLE ):
      return BUBBLING_PHASE;
    case ( RocketT::PHASE_UNKNOWN ):
      throw std::runtime_error( "Event::eventPhase(): PHASE_UNKNOWN" );
    default:
      throw std::runtime_error( "Event::eventPhase(): default" );
  }
}

v8::Handle<v8::Value>
Event::target() {
  v8::HandleScope handle_scope;
  return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetTargetElement(), v8::Null()));
}

Core::String
Event::type() {
  return getRocket()->GetType();
}



void
Event::stopPropagation() {
  return getRocket()->StopPropagation();
}


} } } }//namespaces Rocket::Core::JS::juice

#endif
