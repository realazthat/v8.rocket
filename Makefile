


###############################################################
##Input Variables
###############################################################
ROCKET_HOME = .
ROCKET_CXXFLAGS = -I"$(ROCKET_HOME)/Include"
ROCKET_SRCPATH = $(ROCKET_HOME)/Source

V8_HOME = .
V8_CXXFLAGS = -I"$(V8_HOME)/include"

V8JUICE_HOME = .
V8JUICE_CXXFLAGS = -I"$(V8JUICE_HOME)/src/include"

V8ROCKET_HOME = .
V8ROCKET_OBJPATH = .
V8ROCKET_LIBPATH = .
###############################################################

###############################################################
##Variables
###############################################################
V8ROCKET_INTERNAL_CXXFLAGS = $(CXXFLAGS) \
  $(ROCKET_CXXFLAGS) \
  -I"$(ROCKET_SRCPATH)" \
  $(V8_CXXFLAGS)  \
  $(V8JUICE_CXXFLAGS)  \
  -I"$(V8ROCKET_HOME)/Include" \

V8ROCKET_CXXFLAGS = -I"$(V8ROCKET_HOME)/Include"
V8ROCKET_SRCPATH = $(V8ROCKET_HOME)/Source

LIBV8ROCKET = $(V8ROCKET_LIBPATH)/libv8rocket.a

V8ROCKET_OBJECTS = \
  $(V8ROCKET_OBJPATH)/Browser.o \
  $(V8ROCKET_OBJPATH)/Initialise.o \
  $(V8ROCKET_OBJPATH)/ElementDocumentWrapper.o \
  $(V8ROCKET_OBJPATH)/HTMLDocument.o \
  $(V8ROCKET_OBJPATH)/Event.o \
  $(V8ROCKET_OBJPATH)/HTMLElementList.o \
  $(V8ROCKET_OBJPATH)/HTMLElementBase.o \
  $(V8ROCKET_OBJPATH)/HTMLElementGeneric.o \
  $(V8ROCKET_OBJPATH)/HTMLFormElement.o \
  $(V8ROCKET_OBJPATH)/HTMLInputElement.o \

###############################################################






###############################################################
##Library Targets
###############################################################
$(LIBV8ROCKET): $(V8ROCKET_OBJECTS)
	ar cr "$@" $^
###############################################################

###############################################################
##Object Targets
###############################################################

$(V8ROCKET_OBJPATH)/Browser.o: $(V8ROCKET_SRCPATH)/Core/JS/Browser.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

$(V8ROCKET_OBJPATH)/Initialise.o: $(V8ROCKET_SRCPATH)/Core/JS/Initialise.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

$(V8ROCKET_OBJPATH)/ElementDocumentWrapper.o: $(V8ROCKET_SRCPATH)/Core/JS/detail/rocket/ElementDocumentWrapper.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

$(V8ROCKET_OBJPATH)/HTMLElementList.o: $(V8ROCKET_SRCPATH)/Core/JS/detail/v8/HTMLElementList.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

$(V8ROCKET_OBJPATH)/HTMLElementGeneric.o: $(V8ROCKET_SRCPATH)/Core/JS/detail/v8/HTMLElementGeneric.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

$(V8ROCKET_OBJPATH)/HTMLElementBase.o: $(V8ROCKET_SRCPATH)/Core/JS/detail/v8/HTMLElementBase.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

$(V8ROCKET_OBJPATH)/HTMLInputElement.o: $(V8ROCKET_SRCPATH)/Core/JS/detail/v8/HTMLInputElement.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

$(V8ROCKET_OBJPATH)/HTMLDocument.o: $(V8ROCKET_SRCPATH)/Core/JS/detail/v8/HTMLDocument.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

$(V8ROCKET_OBJPATH)/HTMLFormElement.o: $(V8ROCKET_SRCPATH)/Core/JS/detail/v8/HTMLFormElement.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

$(V8ROCKET_OBJPATH)/Event.o: $(V8ROCKET_SRCPATH)/Core/JS/detail/v8/Event.cpp
	$(CXX) -c -o"$@" $^ $(V8ROCKET_INTERNAL_CXXFLAGS)

###############################################################

###############################################################
##Cleanup Targets
###############################################################
clean.v8rocket:
	rm -f $(V8ROCKET_OBJECTS) $(LIBV8ROCKET)

###############################################################
