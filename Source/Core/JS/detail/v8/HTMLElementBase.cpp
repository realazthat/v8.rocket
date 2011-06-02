#ifndef ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTBASE_INL
#define ROCKET_CORE_JS_DETAIL_V8_HTMLELEMENTBASE_INL


#include <Rocket/Core/JS/detail/v8/HTMLElementBase.h>
#include <Rocket/Core/JS/detail/v8/HTMLElementList.h>
#include <Rocket/Core/JS/detail/rocket/ElementDocumentWrapper.h>
#include <Rocket/Core/JS/detail/rocket/EventListener.h>
#include <Rocket/Core/JS/detail/rocket/Utility.h>

#include <v8.h>

#include <stdexcept>

namespace Rocket{ namespace Core{ namespace JS{ namespace juice{




HTMLElementBase::CW&
HTMLElementBase::getCW() {

  CW & cw( CW::Instance() );
  if( cw.IsSealed() )
  {
      return cw;
  }

  populate(cw);
  cw.Seal(); // ends the binding process
  return cw;
}

template<typename T>
v8::juice::cw::ClassWrap<T>&
HTMLElementBase::populate(v8::juice::cw::ClassWrap<T>& cw) {
  typedef typename v8::juice::convert::MemFuncInvocationCallbackCreator<T> ICM;
  

  cw.template BindGetter<Core::String,
                &HTMLElementBase::tagName>
                ("tagName");
               
  cw.template BindGetter<v8::Handle<v8::Value>,
                &HTMLElementBase::childNodes>
                ("childNodes");
               
  cw.template BindGetter<v8::Handle<v8::Value>,
                &HTMLElementBase::firstChild>
                ("firstChild");
               
  cw.template BindGetter<v8::Handle<v8::Value>,
                &HTMLElementBase::lastChild>
                ("lastChild");
               
  cw.template BindGetter<v8::Handle<v8::Value>,
                &HTMLElementBase::nextSibling>
                ("nextSibling");
               
  cw.template BindGetter<Core::String,
                &HTMLElementBase::nodeName>
                ("nodeName");
               
  cw.template BindGetter<int,
                &HTMLElementBase::nodeType>
                ("nodeType");
               
  cw.template BindGetter<v8::Handle<v8::Value>,
                &HTMLElementBase::ownerDocument>
                ("ownerDocument");
               
  cw.template BindGetter<v8::Handle<v8::Value>,
                &HTMLElementBase::parentNode>
                ("parentNode");
               
  cw.template BindGetter<v8::Handle<v8::Value>,
                &HTMLElementBase::previousSibling>
                ("previousSibling");






  cw.template BindGetterSetter<Core::String,
                   &HTMLElementBase::innerHTML,
                   void, const Core::String&,&HTMLElementBase::innerHTML>
                   ( "innerHTML");
                   
  cw.template BindGetterSetter<const Core::String&,
                   &HTMLElementBase::id,
                   void,const Core::String&,&HTMLElementBase::id>
                   ( "id");
  
  cw.template BindGetterSetter<Core::String,
                   &HTMLElementBase::className,
                   void,const Core::String&,&HTMLElementBase::className>
                   ( "className");
  
  cw.Set( "addEventListener", ICM::M3::template Invocable<void,
    const Core::String&,
    v8::Handle<v8::Value>,
    bool,
    &HTMLElementBase::addEventListener>);
  cw.Set( "appendChild", ICM::M1::template Invocable<void, HTMLElementBase*, &HTMLElementBase::appendChild>);
  cw.Set( "blur", ICM::M0::template Invocable<void, &HTMLElementBase::blur>);
  cw.Set( "click", ICM::M0::template Invocable<void, &HTMLElementBase::click>);
  cw.Set( "cloneNode", ICM::M1::template Invocable<v8::Handle<v8::Value>, bool, &HTMLElementBase::cloneNode>);
  cw.Set( "focus", ICM::M0::template Invocable<void, &HTMLElementBase::focus>);
  cw.Set( "getAttribute",
    ICM::M1::template Invocable<v8::Handle<v8::Value>, const Core::String&, &HTMLElementBase::getAttribute>);
  cw.Set( "getElementById",
    ICM::M1::template Invocable<v8::Handle<v8::Value>, const Core::String&, &HTMLElementBase::getElementById>);
  cw.Set( "getElementsByTagName",
    ICM::M1::template Invocable<v8::Handle<v8::Value>, const Core::String&, &HTMLElementBase::getElementsByTagName>);
  cw.Set( "hasAttribute", ICM::M1::template Invocable<bool, const Core::String&, &HTMLElementBase::hasAttribute>);
  
  cw.Set( "hasChildNodes", ICM::M0::template Invocable<bool, &HTMLElementBase::hasChildNodes>);
  
  cw.Set( "insertBefore", ICM::M2::template Invocable<void, HTMLElementBase*, HTMLElementBase*, &HTMLElementBase::insertBefore>);
  cw.Set( "insertAfter", ICM::M2::template Invocable<void, HTMLElementBase*, HTMLElementBase*, &HTMLElementBase::insertAfter>);
  cw.Set( "item", ICM::M1::template Invocable<v8::Handle<v8::Value>, int, &HTMLElementBase::item>);

  cw.Set( "replaceChild", ICM::M2::template Invocable<void, HTMLElementBase*, HTMLElementBase*, &HTMLElementBase::replaceChild>);
  cw.Set( "removeChild", ICM::M1::template Invocable<v8::Handle<v8::Value>, HTMLElementBase*, &HTMLElementBase::removeChild>);
  cw.Set( "scrollIntoView", ICM::M1::template Invocable<void, bool, &HTMLElementBase::scrollIntoView>);
  cw.Set( "setAttribute", ICM::M2::template Invocable<void, const Core::String&, const Core::String&, &HTMLElementBase::setAttribute>);
  
  return cw;
}




//-----------------------------------------------------------//
//Read Only properties
//-----------------------------------------------------------//

  Core::String
  HTMLElementBase::
  tagName()
  {
    return getRocket()->GetTagName();
  }
  
  v8::Handle<v8::Value>
  HTMLElementBase::
  childNodes()
  {
    int n = getRocket()->GetNumChildren();
    
    v8::HandleScope handle_scope;
    
    Core::ElementList elements;

    elements.reserve(n);
    
    for ( int i = 0; i < n; ++i )
      elements.push_back(getRocket()->GetChild(i));
    
    
    v8::Handle<v8::Value> v8NodeList = JS::juice::create<JS::juice::HTMLElementList>();
    
    assert(!v8NodeList.IsEmpty());
    
    JS::juice::HTMLElementList* nodeList = v8::juice::convert::CastFromJS<JS::juice::HTMLElementList>(v8NodeList);
    
    *nodeList = JS::juice::HTMLElementList(elements);
    
    return handle_scope.Close(v8NodeList);
  }
  
  v8::Handle<v8::Value>
  HTMLElementBase::
  firstChild()
  {
    v8::HandleScope handle_scope;
// std::cout << __FILE__ ":" << __LINE__ << std::endl;
// std::cout << "firstChild" << std::endl;
// std::cout << "TagName: " << getRocket()->GetTagName().CString() << std::endl;
// std::cout << "ptr: " << getRocket() << std::endl;
// std::cout << "firstChild ptr: " << getRocket()->GetFirstChild() << std::endl;
// std::cout << "lastChild ptr: " << getRocket()->GetLastChild() << std::endl;
// std::cout << "v8::Null()->IsNull(): " << v8::Null()->IsNull() << std::endl;
// std::cout << "JS::getJSFromRocket(getRocket()->GetFirstChild(), v8::Null())->IsNull(): "
  // << JS::getJSFromRocket(getRocket()->GetFirstChild(), v8::Null())->IsNull() << std::endl;
    return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetFirstChild(), v8::Null()));
  }
  
  v8::Handle<v8::Value>
  HTMLElementBase::
  lastChild()
  {
// std::cout << __FILE__ ":" << __LINE__ << std::endl;
// std::cout << "lastChild" << std::endl;
// std::cout << "TagName: " << getRocket()->GetTagName().CString() << std::endl;
// std::cout << "ptr: " << getRocket() << std::endl;
// std::cout << "firstChild ptr: " << getRocket()->GetFirstChild() << std::endl;
// std::cout << "lastChild ptr: " << getRocket()->GetLastChild() << std::endl;
    v8::HandleScope handle_scope;
    
    v8::Handle<v8::Value> result = JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetLastChild(), v8::Null());
// std::cout << __FILE__ ":" << __LINE__ << std::endl;
    return handle_scope.Close(result);
  }
  
  
  v8::Handle<v8::Value>
  HTMLElementBase::
  nextSibling()
  {
// std::cout << __FILE__ ":" << __LINE__ << std::endl;
    v8::HandleScope handle_scope;
    return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetPreviousSibling(), v8::Null()));
  }
  
  Core::String
  HTMLElementBase::
  nodeName()
  {
// std::cout << __FILE__ ":" << __LINE__ << std::endl;
    ///FIXME: #text for text nodes
    /// https://developer.mozilla.org/En/DOM/Node.nodeName
    return getRocket()->GetTagName();
  }
  
  int HTMLElementBase::nodeType()
  {
// std::cout << __FILE__ ":" << __LINE__ << std::endl;
    ///FIXME: https://developer.mozilla.org/En/DOM/Node.nodeType
    // return ELEMENT_NODE;
    return 1;
  }
  
  v8::Handle<v8::Value>
  HTMLElementBase::
  ownerDocument()
  {
    v8::HandleScope handle_scope;
    Core::ElementDocument* rocket_body = getRocket()->GetOwnerDocument();
std::cout << "rocket_body" << rocket_body << std::endl;
    if (rocket_body) {
      assert(dynamic_cast<ElementDocumentWrapper*>(rocket_body));
      
      ElementDocumentWrapper* rocket_body_wrapper = static_cast<ElementDocumentWrapper*>(rocket_body);
      
      //fixme:?
      assert(rocket_body_wrapper);
      
      if ( rocket_body_wrapper ) {
        HTMLDocument* document = rocket_body_wrapper->getDOMHTMLDocument();
std::cout << "document" << document << std::endl;
        if (document) {
        
          v8::Handle<v8::Value> v8document = v8::juice::convert::CastToJS(document);
          
          assert(!v8document.IsEmpty());
          
          return handle_scope.Close(v8document);
        }
      }
    }
    
    return handle_scope.Close(v8::Null());
  }
  
  v8::Handle<v8::Value>
  HTMLElementBase::
  parentNode()
  {
// std::cout << __FILE__ ":" << __LINE__ << std::endl;
// std::cout << "getRocket()->GetParentNode(): " << getRocket()->GetParentNode() << std::endl;
// if ( getRocket()->GetParentNode() ) {
// std::cout << "getRocket()->GetParentNode()->GetTagName(): " << getRocket()->GetParentNode()->GetTagName().CString() << std::endl;



// }

    v8::HandleScope handle_scope;
    
    
    
    // return handle_scope.Close(v8::Null());
    return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetParentNode(), v8::Null()));
  }
  
  v8::Handle<v8::Value>
  HTMLElementBase::
  previousSibling()
  {
// std::cout << __FILE__ ":" << __LINE__ << std::endl;
    v8::HandleScope handle_scope;
    

    return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetPreviousSibling(), v8::Null()));
  }


//-----------------------------------------------------------//
//Getters/setters
//-----------------------------------------------------------//


  void HTMLElementBase::id(const Core::String& rml) {
    getRocket()->SetId(rml);
  }

  const Core::String&
  HTMLElementBase::id(){
    return getRocket()->GetId();
  }



  void
  HTMLElementBase::
  innerHTML(const Core::String& rml) {
    getRocket()->SetInnerRML(rml);
  }

  Core::String
  HTMLElementBase::
  innerHTML(){
    Core::String result;
    getRocket()->GetInnerRML(result);
    return result;
  }

  v8::Handle<v8::Value>
  HTMLElementBase::
  nodeValue() {
    ///FIXME: https://developer.mozilla.org/En/DOM/Node.nodeValue
    return v8::Null();
  }
  
  void
  HTMLElementBase::
  nodeValue(const Core::String& value) {
    ///FIXME: https://developer.mozilla.org/En/DOM/Node.nodeValue
  }


  Core::String HTMLElementBase::className() {
    return getRocket()->GetClassNames();
  }
  
  void HTMLElementBase::className(const Core::String& value) {
    getRocket()->SetClassNames(value);
  }










//-----------------------------------------------------------//
//Methods
//-----------------------------------------------------------//

  void
  HTMLElementBase::
  addEventListener(const Core::String& type, v8::Handle<v8::Value> listener, bool useCapture)
  {
    v8::HandleScope handle_scope;

    if (listener->IsFunction()) {
      v8::Handle<v8::Function> listenerFunction(v8::Handle<v8::Function>::Cast(listener));
      
      getRocket()->AddEventListener(type,
        new JS::EventListener(listenerFunction, v8::Context::GetCurrent()), useCapture);
    }
  }


  void
  HTMLElementBase::
  appendChild(self_type* nodePtr)
  {
    assert(nodePtr != NULL);
    self_type& node = *nodePtr;
    
    
    getRocket()->AppendChild(node.getRocket(), true);
    return;
  }

  void HTMLElementBase::blur() {
    
    getRocket()->Blur();
    return;
  }

  void HTMLElementBase::click() {
    
    getRocket()->Click();
    return;
  }

  v8::Handle<v8::Value>
  HTMLElementBase::
  cloneNode(bool deep) {
    if (!deep)
      ///FIXME:TODO
      throw std::runtime_error("Element.clone(false) not implemented");
    
    v8::HandleScope handle_scope;
    
    Core::ElementReference clone( getRocket()->Clone() );
    
    assert(clone);
    
    v8::Handle<v8::Value> jsClone = JS::juice::getV8HandleFromRocketWrapper(*clone, v8::Handle<v8::Value>());
    
    assert(!jsClone.IsEmpty());
    
    return handle_scope.Close(jsClone);
  }


  void HTMLElementBase::focus() {
    
    getRocket()->Focus();
    return;
  }


  v8::Handle<v8::Value>
  HTMLElementBase::getAttribute(const Core::String& name) {
    v8::HandleScope handle_scope;
    if (getRocket()->HasAttribute(name)) {
      return handle_scope.Close(v8::juice::convert::CastToJS(getRocket()->GetAttribute(name, Core::String())));
    }
    return handle_scope.Close(v8::Null());
  }

  v8::Handle<v8::Value>
  HTMLElementBase::
  getElementsByTagName(const Core::String& tagname) {
    v8::HandleScope handle_scope;
    
    //FIXME: switch to the overloaded create()
    v8::Handle<v8::Value> v8ElementList = JS::juice::create<JS::juice::HTMLElementList>();
    {
      assert(!v8ElementList.IsEmpty());
      
      //Retrieve the native pointer
      JS::juice::HTMLElementList* jsElementList = v8::juice::convert::CastFromJS<JS::juice::HTMLElementList>(v8ElementList);
      
      assert(jsElementList);
      
      //Retreive the native list, and fill it
      Core::ElementList elements;
      
      getRocket()->GetElementsByTagName(elements, tagname);
      
      *jsElementList = HTMLElementList(elements);
    }
    return handle_scope.Close(v8ElementList);
  }

  v8::Handle<v8::Value> HTMLElementBase::getElementById(const Core::String& id)
  {
    v8::HandleScope handle_scope;
std::cout << "getRocket()->GetElementById(id): " << getRocket()->GetElementById(id) << std::endl;
    return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetElementById(id), v8::Null()));
  }

  bool HTMLElementBase::hasAttribute(const Core::String& attributename) {
    return getRocket()->HasAttribute(attributename);
  }

  bool HTMLElementBase::hasChildNodes() {
    return getRocket()->HasChildNodes();
  }

  void HTMLElementBase::insertBefore(self_type* newElementPtr, self_type* targetElementPtr){
    if (!newElementPtr)
      throw std::runtime_error("newElementPtr is null");
    
    if (!targetElementPtr)
      throw std::runtime_error("targetElementPtr is null");
    
    {
      assert(newElementPtr);
      assert(targetElementPtr);
    }
    
    self_type& jsNewElement = *newElementPtr;
    self_type& jsTargetElement = *targetElementPtr;
    
    
    getRocket()->InsertBefore(
      jsNewElement.getRocket(),
      jsTargetElement.getRocket() );
    return;
  }

  void HTMLElementBase::insertAfter(self_type* newElementPtr, self_type* targetElementPtr){
    assert(newElementPtr != NULL);
    assert(targetElementPtr != NULL);
    self_type& jsNewElement = *newElementPtr;
    self_type& jsTargetElement = *targetElementPtr;
    
    Core::Element* next = jsTargetElement.getRocket()->GetNextSibling();
    
    if ( next == NULL ) {
      getRocket()->AppendChild(jsNewElement.getRocket());
      return;
    }
    
    getRocket()->InsertBefore(
      jsNewElement.getRocket(),
      next );
    return;
  }

  v8::Handle<v8::Value>
  HTMLElementBase::item(int index) {
    v8::HandleScope handle_scope;
    if ( index < getRocket()->GetNumChildren() )
      return handle_scope.Close(v8::Null());
    
    return handle_scope.Close(JS::juice::getV8HandleFromRocketWrapper(getRocket()->GetChild(index), v8::Null()));
  }

  v8::Handle<v8::Value>
  HTMLElementBase::removeChild(self_type* childreference) {
    v8::HandleScope handle_scope;
    
    assert(childreference != NULL);
    self_type& jsChildElement = *childreference;

    ///FIXME: see below; this is to retain a reference to the child
    ///FIXME: is this necessary? this is being called from v8; which has a reference to the child
    v8::Handle<v8::Value> jsChild = JS::juice::getV8HandleFromRocketWrapper(jsChildElement.getRocket(), v8::Handle<v8::Value>());
    assert(!jsChild.IsEmpty());
    
    assert(jsChildElement.getRocket()->GetReferenceCount() > 1);
    
    if (getRocket()->RemoveChild(jsChildElement.getRocket())) {
      
      ///FIXME: if u remove a child, is it deleted? or must u dereference once more
      
      return handle_scope.Close(jsChild);
    }
    
    return handle_scope.Close(v8::Null());
  }


  void HTMLElementBase::replaceChild(self_type* newChildPtr, self_type* oldChildPtr) {
    assert(newChildPtr != NULL);
    assert(oldChildPtr != NULL);
    self_type& jsNewElement = *newChildPtr;
    self_type& jsTargetElement = *oldChildPtr;
    
    
    getRocket()->ReplaceChild(
      jsNewElement.getRocket(),
      jsTargetElement.getRocket() );
    return;
  }

  void HTMLElementBase::scrollIntoView(bool top) {
    getRocket()->ScrollIntoView(top);
  }

  void HTMLElementBase::scrollIntoView() {
    getRocket()->ScrollIntoView(true);
  }

  void HTMLElementBase::setAttribute(const Core::String& name, const Core::String& value)
  {
    getRocket()->SetAttribute(name, value);
  }

  void HTMLElementBase::removeAttribute(const Core::String& name)
  {
    getRocket()->RemoveAttribute(name);
  }

} } } }//namespaces Rocket::Core::JS::juice

#endif
