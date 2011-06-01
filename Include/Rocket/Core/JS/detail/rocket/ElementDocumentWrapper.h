#ifndef ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTDOCUMENTWRAPPER_H
#define ROCKET_CORE_JS_DETAIL_ROCKET_ELEMENTDOCUMENTWRAPPER_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/detail/rocket/RocketWrapper.h>

#include <Rocket/Core/JS/detail/v8/HTMLDocument.h>


namespace Rocket{ namespace Core { namespace JS{

/**
 * This is a special wrapper for Core::ElementDocument,
 * to give access to the DOM HTMLDocument, which is
 * *not* really the BODY tag, although rocket returns
 * the BODY tag for GetOwnerDocument(). Instead, we
 * create a separate object representing the HTMLDocument,
 * and give the BODY tag (Core::ElementDocument) the ability
 * to obtain it.
 */
struct ElementDocumentWrapper : public Core::ElementDocument
{
  typedef Core::ElementDocument super;
  typedef ElementDocumentWrapper self_type;
  typedef Core::ElementDocument RElementT;

  ElementDocumentWrapper(const Core::String& tag);
public:
  /**
   * Obtain the HTMLDocument object.
   */
  virtual JS::juice::HTMLDocument* getDOMHTMLDocument();
  /**
   * Set the HTMLDocument object
   */
  virtual void setDOMHTMLDocument(JS::juice::HTMLDocument* doc);
public:
private:
  //FIXME: check lifetime of this??
  JS::juice::HTMLDocument* document;
};

} } }//namespaces Rocket::Core::JS

#endif
