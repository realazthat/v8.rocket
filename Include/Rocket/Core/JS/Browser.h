#ifndef ROCKET_CORE_JS_BROWSER_H
#define ROCKET_CORE_JS_BROWSER_H

#include <Rocket/Core.h>
#include <Rocket/Core/JS/detail/rocket/RocketScope.h>

#include <v8.h>

namespace Rocket{ namespace Core{ namespace JS{

namespace{

void Initialize();

}//anonymous namespace

struct Browser{
  Browser(const RocketScope<Core::Context>& context, const RocketScope<Core::ElementDocument>& body);
public:
//Access to rocket
  /**
   * Access the rocket context.
   */
  Rocket::Core::Context& rocketContext();
  /**
   * Access the rocket context.
   */
  const Rocket::Core::Context& rocketContext() const;
public:
//JS stuff
  /**
   * Utility JS exception reporter, outputs to a stream of type OutT.
   * Use together with boost::bind, to make a valid function object.
   */
  template<typename OutT>
  static void ReportException(const v8::TryCatch& try_catch, OutT& out);
  
  /**
   * Utility JS exception reporter, doesn't report anything.
   * Use together with boost::bind, to make a valid function object.
   */
  template<typename OutT>
  static void ReportException(const v8::TryCatch& try_catch);

  /**
   * Compiles a script, and returns a handle to the result.
   *
   * @param script_source A v8 string handle containing the javascript.
   * @param script_name The name of the script; usually a filename etc.
   * @param handleTryCatch a function object that takes a v8::TryCatch,
   *        for reporting exceptions.
   */
  template<typename HandleTryCatch>
  v8::Handle<v8::Script>
  compile(const v8::Handle<v8::String> script_source,
    const v8::Handle<v8::String> script_name,
    HandleTryCatch handleTryCatch);
  

  /**
   * Runs a script, and returns a handle to the result.
   *
   * @param script A compiled script to run.
   * @param handleTryCatch a function object that takes a v8::TryCatch,
   *        for reporting exceptions.
   */
  template<typename HandleTryCatch>
  v8::Handle<v8::Value> run(v8::Handle<v8::Script> script, HandleTryCatch handleTryCatch);
  
  /**
   * Returns the v8::Context handle.
   */
  v8::Handle<v8::Context> v8Context() const;
  
  /**
   * Returns a handle to the HTMLDocument object.
   */
  v8::Handle<v8::Value> document() const;
private:
//Rocket stuff
  JS::RocketScope<Rocket::Core::Context> m_rocketContext;
  JS::RocketScope<Rocket::Core::ElementDocument> m_rocketBody;
private:
//v8 stuff
  v8::Persistent<v8::Context> m_v8Context;
  v8::Persistent<v8::Value> m_v8HTMLDocument;
};



} } }//namespaces Rocket::Core::JS


#endif
