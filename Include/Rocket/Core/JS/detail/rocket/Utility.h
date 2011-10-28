#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_UTILITY_H
#define ROCKET_CORE_JS_DETAIL_ROCKET_UTILITY_H

#include <Rocket/Core.h>

#include <v8.h>

#include <v8/juice/ClassWrap.h>
#include <v8/juice/convert.h>


#include <Rocket/Core/JS/detail/rocket/RocketWrapperInterface.h>

namespace Rocket{ namespace Core { namespace JS{ namespace juice{
namespace {

/**
 * Creates a v8::Handle in a v8 context of the specified type. The
 * object will be default constructed.
 *
 * V8WrapperT must have v8::juice::ClassWrap glue.
 */
template<typename V8WrapperT>
v8::Handle<v8::Object>
create() {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Object> v8Instance = V8WrapperT::getCW().Instance().NewInstance(0,0);

  assert(!v8Instance.IsEmpty());
  assert(v8::juice::convert::CastFromJS<V8WrapperT>(v8Instance));
  return handle_scope.Close(v8Instance);
}

/**
 * Creates a v8::Handle in a v8 context of the specified type. First, a
 * temporary object will be constructed on the stack, using a constructor that
 * takes @param rocketNative. Then another object of type V8WrapperT will
 * be created in the v8 context, default constructed. Using the assignment
 * operator, the object in the v8 context will obtain the same value is the
 * one on the stack.
 *
 * Summary: Use this to create v8 wrappers, that take a native rocket
 * value in the ctor.
 *
 * V8WrapperT must have v8::juice::ClassWrap glue.
 */
template<typename V8WrapperT, typename RocketT>
v8::Handle<v8::Object>
create(const RocketT& rocketNative) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Object> v8Instance = create<V8WrapperT>();
  {
    V8WrapperT* instance = v8::juice::convert::CastFromJS<V8WrapperT>(v8Instance);

    assert(instance);

    *instance = V8WrapperT(rocketNative);
  }
  return handle_scope.Close(v8Instance);
}




/**
 * Utility function for returning: either a v8::Handle representing a native
 * rocket object, or a specified default v8::Handle upon failure.
 *
 * @param rocket A native rocket pointer (must be derived by the wrapper of course)
 *               Can be NULL; in which case, @param default_handle will be returned.
 */
template<typename RocketT>
v8::Handle<v8::Value>
getV8HandleFromRocketWrapper( RocketT* rocket, v8::Handle<v8::Value> default_handle )
{
  v8::HandleScope handle_scope;
  if (rocket) {
    v8::Handle<v8::Object> result = RocketWrapperInterface::CastToJS(rocket);
    assert(!result.IsEmpty());
    return handle_scope.Close(result);
  }
  return default_handle;
}

/**
 * This overload returns a v8::Handle<v8::Object> for the native
 * (but derived by wrapper) rocket type. If @param rocket is null, then
 * an empty (default constructed) handle  is returned.
 */
template<typename RocketT>
v8::Handle<v8::Object>
getV8HandleFromRocketWrapper( RocketT* rocket )
{
  v8::HandleScope handle_scope;
  if (rocket) {
    v8::Handle<v8::Object> result = RocketWrapperInterface::CastToJS(rocket);
    assert(!result.IsEmpty());
    return handle_scope.Close(result);
  }
  return v8::Handle<v8::Object>();
}

/**
 * Utility function to obtain the c-string value of a v8 utf8 string.
 * Note that the result probably only lasts as long as @param value
 * itself is alive.
 */
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

}//anonymous namespace
} } } }//namespaces Rocket::Core::JS::juice

#endif
