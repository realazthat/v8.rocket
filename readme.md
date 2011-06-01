# v8rocket - The HTML/CSS/JS User Interface Library

***v8rocket*** (this project) is a library for integrating v8 with libRocket, and to expose the HTML DOM to Javascript.

libRocket (http://librocket.com) is a ***renderer agnostic*** HTML/CSS renderer, useful for creating UIs for games and the like. Hopefully makes assembling a UI a breeze, using existing technology, and thus allowing existing, well used, thoroughly tested tools to be used. It allows easy "theming" via CSS, or even changing the HTML, without having to recompile the game code etc. It allows a fully dynamic layout, that can grow/shrink etc. as needed. The HTML allows the simple CSS Box Model to be used for UI.

v8 (http://code.google.com/p/v8/) is a ***fast*** Javascript engine, used by the Chromium browser to execute Javascript.

My goal and wish is to be able to leverage existing Javascript libraries that have revolutionized web development over the years, such as jQuery (http://jquery.com/).

## 3rd-party libraries

* libRocket (http://librocket.com), (https://github.com/lloydw/libRocket)
 * That's what this is all about
* v8 (http://code.google.com/p/v8/)
 * The v8 Javascript engine
* v8-juice (http://code.google.com/p/v8-juice/)
 * Exposes C++ classes to v8
* v8rocket (https://github.com/realazthat/v8.rocket)
 * This project, exposes libRocket's DOM to v8
* boost
 * for boost::bind, otherwise be prepared to create function objects (or use std::bind)

## Building v8rocket

To build:
<pre>
make v8rocket &lt;VARS&gt;
</pre>

VARS should be:

* ROCKET_HOME=&lt;rocket project directory&gt;
 * Defaults to cwd
 * Alternatively, you can directly specify ROCKET_CXXFLAGS and ROCKET_SRCPATH, in which case make sure ROCKET_CXXFLAGS has the include path for rocket, and ROCKET_SRCPATH is the Source sub-directory in the project's directory
* V8_HOME=&lt;v8 project directory&gt;
 * Defaults to cwd
 * Alternatively, you can directly specify V8_CXXFLAGS, in which case make sure V8_CXXFLAGS has the include path for v8
* V8JUICE_HOME=&lt;v8-juice project directory&gt;
 * Alternatively, you can directly specify V8JUICE_CXXFLAGS, in which case make sure V8JUICE_CXXFLAGS has the include path for v8-juice
* V8ROCKET_HOME=&lt;v8rocket project directory&gt;
 * Defaults to cwd, no need to set it if executing from within the project directory
* V8ROCKET_OBJPATH=&lt;v8rocket object output directory&gt;
 * Defaults to cwd
* V8ROCKET_LIBPATH=&lt;v8rocket library output directory&gt;
 * Defaults to cwd
* CXXFLAGS=&lt;additional C++ FLAGS to be used&gt;
 * Add things like -DSTATIC_LIB here etc., see libRocket docs for more info
 * Add any additional flags for v8, v8-juice etc.

To clean:
<pre>
make clean.v8rocket &lt;SAME VARS AS WHEN BUILDING&gt;
</pre>

Example:
<pre>
#Clean the project
make clean.v8rocket V8_HOME=../projects/v8 V8JUICE_HOME=../projects/v8-juice V8ROCKET_HOME=./ CXXFLAGS="-DSTATIC_LIB"
#Build the project
make v8rocket V8_HOME=../projects/v8 V8JUICE_HOME=../projects/v8-juice V8ROCKET_HOME=./ CXXFLAGS="-DSTATIC_LIB"
</pre>

You can easily compile this in MSVC:

1. Add all the files in the Source directory into a project.
1. Add the include directories of v8, v8-juice, v8rocket and libRocket to the project's include directories.
1. Add the libRocket Source directory to the include path. Normally you wouldn't do this, but it contains some header files that are not supposed to be exposed in the Include directory, but since we are implementating a wrapper, we need access to. No need to do this for projects that **use** v8rocket, just when compiling v8rocket itself.
1. Add any definitions, such as /DSTATIC_LIB etc.


## Integrating into your project
Make sure your project has access to the following project's include directores:

* v8
* v8-juice
 * Warning: There is/was a major bug in v8-juice in certain versions that would result in v8 catching unreaped v8 objects and asserting (and thus crashing). See http://code.google.com/p/v8-juice/issues/detail?id=27.
* libRocket
* v8rocket (this project)

And of course link with libv8rocket.a (or w/e you name it if in MSVC), and the other libs: v8 , v8-juice libRocket, order might matter.

## Example usage

Initalize Rocket as usual. Then call Rocket::Core::JS::Initialise() immediately afterward:
<pre>
  
  Rocket::Core::Initialise();
  Rocket::Controls::Initialise();
  Rocket::Core::JS::Initialise();
  
</pre>

Create your Core::Context and load your document as usual.

The main v8/rocket glue is the Rocket::Core::JS::Browser object. Create a Browser with your Core::Context and Core::ElementDocument. The Browser object should stay alive longer than the Context object (since the JS might have installed callback EventListener's into the DOM).

Create the Browser object like so:
<pre>
  Rocket::Core::Context* rocketContext = Rocket::Core::CreateContext(
    Rocket::Core::String("Test"),
    Rocket::Core::Vector2i(mWindow->getWidth(), mWindow->getHeight()),
    &(*render_interface));
  assert(r);
  
  rocketContext->LoadMouseCursor("cursor.rml")->RemoveReference();
  rocketContext->ShowMouseCursor(true)
  
  Rocket::Core::ElementDocument* rocketDocument = rocketContext->LoadDocument("demo.rml");
  assert(rocketDocument);
  
  rocketDocument->Show();
  
  Rocket::Core::JS::Browser* browser = new Rocket::Core::JS::Browser(rocketContext, rocketDocument);
  
  //Browser will increase the ref counts of both, so u can safely remove their references
  rocketContext->RemoveReference();
  rocketDocument->RemoveReference();
  
</pre>

And finally, to execute Javascript:
<pre>
//You can probably put this anywhere, I put this in my keyboard handler, and execute it on a certain key
  {
    typedef Rocket::Core::JS::Browser Browser;
    
    //I think this must be somewhere up the stack in order to do anything v8, dunno
    v8::Locker locker;
    
    //All handles created below will be reaped when this is destroyed
    v8::HandleScope handle_scope;
    
    //In order to do anything v8, we must be inside a valid v8 context, this will make the rest
    // of this cope in our browser's v8 context
    v8::Context::Scope context_scope(browser->v8Context());
    
    //I load this string from a file, see v8 docs and examples on how to create strings etc.
    v8::Handle<v8::String> script_source = v8::String::New("document.getElementById('output').innerHTML = \"CAN YOU SEE ME\"");
    
    assert(!script_source.IsEmpty());
    
    //Compile the script
    v8::Handle<v8::Script> script = browser->compile(ReadFile(filename),
      v8::String::New(filename),
      //This is using boost::bind to make a function object that takes a v8::TryCatch
      //The utility function Browser::ReportException is provided; it outputs to the specified
      // output stream, and takes the TryCatch as the first argument. You can provide your
      // own function object as well, and/or create them using boost::bind, or std::bind etc.
      boost::bind(BrowserT::ReportException&lt;std::ostream&gt;, _1, boost::ref(std::cout)));
    
    //Run the script
    v8::Handle<v8::Value> result = browser->run(script,
      //See above for explanation of this parameter
      boost::bind(Browser::ReportException&lt;std::ostream&gt;, _1, boost::ref(std::cout)) );
  }
  //Now that we are out of scope, all the Handles will be reaped.
  //Don't just store a copy of one of the above Handles; it will be invalid.
  //If you want to store a compiled script accross calls, or otherwise outside this scope,
  // you would need to use a Persistent handle, and allocate it using
  // v8::Persistent&lt;v8::Script&gt;::New(script)
</pre>

As for the Javascript itself, only the following are provided:

- The global document object
- A global log() function is provided; it will output to std::cout

It is easier to emulate the rest of the global objects within Javascript for now.
For example, to emulate the window object etc., I currently preempt code with the following in my Javascript file:
<pre>
var window = this;
window.navigator = 
  {
    appName : "Netscape",
    appVersion :"5.0 (Windows NT 6.1; WOW64) AppleWebKit/534.30 (KHTML, like Gecko) Chrome/12.0.742.60 Safari/534.30",
    cookieEnabled: false,
    userAgent : "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/534.30 (KHTML, like Gecko) Chrome/12.0.742.60 Safari/534.30"
  };

window.location =
  {
    href : "http://wabcradio.com/article.asp?id=531472"
  };



function superParent(element){
  var result = element;
  while(result.parentNode != null){
    result = result.parentNode;
  }
  
  return result;
}

document.createDocumentFragment = function(){
  //This is almost certainly incorrect, but for now we'll try and get away with it
  //Emulating this in actuality would probably be a pain for librocket :|
  return document.createElement('div');
};

//Notice, I can't just do document.addEventListener = document.body.addEventListener
//This is because the wrapped functions depend on the This ptr to find the native "this" pointer
document.addEventListener = function(a,b,c){
  //This is probably incorrect, but for now we'll try and get away with it 
  document.body.addEventListener(a,b,c);
};

window.addEventListener = function(a,b,c) {
  //This is probably incorrect, but for now we'll try and get away with it 
  document.addEventListener(a,b,c);
};

console = { log : this.log };
</pre>

When I am satisfied that this seems to work for different Javascript libraries and tests suites, I might "freeze" this into v8 wrapped native objects, or perhaps simply provide some default Javascript that executes before any script.

## Do's:
- Call Rocket::Core::Initialise(), then Rocket::Controls::Initialise(), then Rocket::Core::JS::Initialise(), if you fail to do this, undefined behavior (BAD) will result

## Don'ts:
- Don't use rocket debugger (don't include Core/Debugger.h), or perhaps that ok, but don't initalize the context with the debugger


## Status
I am currently trying to get jQuery selectors running. Loading jQuery finally does not give errors, however only by-id and perhaps by-tag selectors are working right now. Also events like click() seem to be working.

So for now, I am sort of using jQuery as a benchmark of the DOM implementation.

Note that input elements etc. are not specialized above HTMLElement, so setting their value property is useless for now (Wrap controls TODO).

## TODO

- Warn about v8-juice version
- Wrap controls
- Implement removeEventListener
- Implement/Use EventListenerInstancer?
- Finish DOM (of course)
- Test suites?
- Example
- Example html/javascript
- Script tag

## WORKAROUNDS
- I don't think it is possible to get access to the HEAD tag etc. in libRocket
- In libRocket, ElementDocument is the BODY tag; in DOM, HTMLDocument is usually an HTML tag (equivelent to #root, which here is a generic element)
- In libRocket, GetOwnerDocument() returns the BODY tag, in DOM, ownerDocument points to the HTMLDocument

## License (MIT)
 Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 
 Copyright (c) 2011 Azriel Fasten
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
  
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
