#ifndef ROCKET_CORE_JS_DETAIL_V8_CSS2PROPERTIES_H
#define ROCKET_CORE_JS_DETAIL_V8_CSS2PROPERTIES_H

#include <Rocket/Core.h>

#include <Rocket/Core/JS/detail/v8/CSS2Properties.h>
#include <Rocket/Core/JS/detail/rocket/RocketScope.h>

#include <v8.h>
#include <v8/juice/ClassWrap.h>

namespace Rocket{ namespace Core{ namespace JS{ namespace juice{

struct CSS2Properties{
  typedef CSS2Properties self_type;
  typedef Core::Element RElement;
  
  CSS2Properties();
  CSS2Properties(RElement* e);
  self_type& operator=(const self_type& other);
  virtual ~CSS2Properties();
public:
  virtual Core::String azimuth();
  virtual void azimuth(const Core::String& v);
  
  virtual Core::String background();
  virtual void background(const Core::String& v);
  
  virtual Core::String backgroundAttachment();
  virtual void backgroundAttachment(const Core::String& v);
  
  virtual Core::String backgroundColor();
  virtual void backgroundColor(const Core::String& v);
  
  virtual Core::String backgroundImage();
  virtual void backgroundImage(const Core::String& v);
  
  // virtual Core::String backgroundPosition() const;
  // virtual Core::String backgroundRepeat() const;
  // virtual Core::String border() const;
  // virtual Core::String borderCollapse() const;
  // virtual Core::String borderColor() const;
  // virtual Core::String borderSpacing() const;
  // virtual Core::String borderStyle() const;
  // virtual Core::String borderTop() const;
  // virtual Core::String borderRight() const;
  // virtual Core::String borderBottom() const;
  // virtual Core::String borderLeft() const;
  // virtual Core::String borderTopColor() const;
  // virtual Core::String borderRightColor() const;
  // virtual Core::String borderBottomColor() const;
  // virtual Core::String borderLeftColor() const;
  // virtual Core::String borderTopStyle() const;
  // virtual Core::String borderRightStyle() const;
  // virtual Core::String borderBottomStyle() const;
  // virtual Core::String borderLeftStyle() const;
  // virtual Core::String borderTopWidth() const;
  // virtual Core::String borderRightWidth() const;
  // virtual Core::String borderBottomWidth() const;
  // virtual Core::String borderLeftWidth() const;
  // virtual Core::String borderWidth() const;
  // virtual Core::String bottom() const;
  // virtual Core::String captionSide() const;
  // virtual Core::String clear() const;
  // virtual Core::String clip() const;
  // virtual Core::String color() const;
  // virtual Core::String content() const;
  // virtual Core::String counterIncrement() const;
  // virtual Core::String counterReset() const;
  // virtual Core::String cue() const;
  // virtual Core::String cueAfter() const;
  // virtual Core::String cueBefore() const;
  // virtual Core::String cursor() const;
  // virtual Core::String direction() const;
  virtual Core::String display();
  virtual void display(const Core::String& v);
  // virtual Core::String elevation() const;
  // virtual Core::String emptyCells() const;
  // virtual Core::String cssFloat() const;
  // virtual Core::String font() const;
  // virtual Core::String fontFamily() const;
  // virtual Core::String fontSize() const;
  // virtual Core::String fontSizeAdjust() const;
  // virtual Core::String fontStretch() const;
  // virtual Core::String fontStyle() const;
  // virtual Core::String fontVariant() const;
  // virtual Core::String fontWeight() const;
  // virtual Core::String height() const;
  // virtual Core::String left() const;
  // virtual Core::String letterSpacing() const;
  // virtual Core::String lineHeight() const;
  // virtual Core::String listStyle() const;
  // virtual Core::String listStyleImage() const;
  // virtual Core::String listStylePosition() const;
  // virtual Core::String listStyleType() const;
  // virtual Core::String margin() const;
  // virtual Core::String marginTop() const;
  // virtual Core::String marginRight() const;
  // virtual Core::String marginBottom() const;
  // virtual Core::String marginLeft() const;
  // virtual Core::String markerOffset() const;
  // virtual Core::String marks() const;
  // virtual Core::String maxHeight() const;
  // virtual Core::String maxWidth() const;
  // virtual Core::String minHeight() const;
  // virtual Core::String minWidth() const;
  // virtual Core::String orphans() const;
  // virtual Core::String outline() const;
  // virtual Core::String outlineColor() const;
  // virtual Core::String outlineStyle() const;
  // virtual Core::String outlineWidth() const;
  // virtual Core::String overflow() const;
  // virtual Core::String padding() const;
  // virtual Core::String paddingTop() const;
  // virtual Core::String paddingRight() const;
  // virtual Core::String paddingBottom() const;
  // virtual Core::String paddingLeft() const;
  // virtual Core::String page() const;
  // virtual Core::String pageBreakAfter() const;
  // virtual Core::String pageBreakBefore() const;
  // virtual Core::String pageBreakInside() const;
  // virtual Core::String pause() const;
  // virtual Core::String pauseAfter() const;
  // virtual Core::String pauseBefore() const;
  // virtual Core::String pitch() const;
  // virtual Core::String pitchRange() const;
  // virtual Core::String playDuring() const;
  // virtual Core::String position() const;
  // virtual Core::String quotes() const;
  // virtual Core::String richness() const;
  // virtual Core::String right() const;
  // virtual Core::String size() const;
  // virtual Core::String speak() const;
  // virtual Core::String speakHeader() const;
  // virtual Core::String speakNumeral() const;
  // virtual Core::String speakPunctuation() const;
  // virtual Core::String speechRate() const;
  // virtual Core::String stress() const;
  // virtual Core::String tableLayout() const;
  // virtual Core::String textAlign() const;
  // virtual Core::String textDecoration() const;
  // virtual Core::String textIndent() const;
  // virtual Core::String textShadow() const;
  // virtual Core::String textTransform() const;
  // virtual Core::String top() const;
  // virtual Core::String unicodeBidi() const;
  // virtual Core::String verticalAlign() const;
  virtual Core::String visibility();
  virtual void visibility(const Core::String& v);
  // virtual Core::String voiceFamily() const;
  // virtual Core::String volume() const;
  // virtual Core::String whiteSpace() const;
  // virtual Core::String widows() const;
  // virtual Core::String width() const;
  // virtual Core::String wordSpacing() const;
  // virtual Core::String zIndex;
public:
  typedef v8::juice::cw::ClassWrap<self_type> CW;
  
  static
  CW&
  getCW();
protected:
  RElement* getRocket();
  const RElement* getRocket() const;
  
  virtual Core::String getProperty(const Core::String& n);
  virtual void setProperty(const Core::String& n, const Core::String& v);
private:
  Core::JS::RocketScope<RElement> rocket;
};

} } } }//namespaces Rocket::Core::JS::juice

#include <Rocket/Core/JS/detail/v8/glue/CSS2Properties.h>

#endif
