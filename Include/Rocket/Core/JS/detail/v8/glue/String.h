#ifndef ROCKET_CORE_JS_GLUE_STRING_H
#define ROCKET_CORE_JS_GLUE_STRING_H

#include <Rocket/Core.h>

#include <v8/juice/convert.h>
#include <v8.h>

namespace v8 { namespace juice {  namespace convert {

    template <>
    struct NativeToJS<Rocket::Core::String>
    {
      v8::Handle<v8::Value> operator()( Rocket::Core::String const & v ) const
      {
          /** This use of v.data() instead of v.c_str() is highly arguable. */
          return String::New( v.CString(), static_cast<int>( v.Length() ) );
      }
    };

    template <>
    struct JSToNative<Rocket::Core::String>
    {
      typedef Rocket::Core::String ResultType;
      ResultType operator()( v8::Handle<v8::Value> const & h ) const
      {
        static const ResultType emptyString;
        v8::String::Utf8Value utf8String( h );
        const char* s = *utf8String;
        if (s)
        {
          return ResultType(s, s + utf8String.length());
        }
        return emptyString;
      }
    };

} } }//namespaces v8::juice::convert

#endif
