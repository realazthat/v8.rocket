#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTDOCUMENTWRAPPER_CPP
#define ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTDOCUMENTWRAPPER_CPP


#include <Rocket/Core/JS/detail/rocket/ElementDocumentWrapper.h>

namespace Rocket{ namespace Core{ namespace JS{



ElementDocumentWrapper::ElementDocumentWrapper(const Core::String& tag)
  : super(tag), document(NULL)
{

}

JS::juice::HTMLDocument*
ElementDocumentWrapper::
getDOMHTMLDocument()
{
  return document;
}

void
ElementDocumentWrapper::
setDOMHTMLDocument(JS::juice::HTMLDocument* doc)
{
  document = doc;
}


} } }//namespaces Rocket::Core::JS

#endif
