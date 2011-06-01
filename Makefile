


###############################################################
##Input Variables
###############################################################
ROCKET_HOME = .
ROCKET_CXXFLAGS = -I"$(ROCKET_HOME)/Include"

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
  $(V8_CXXFLAGS)  \
  $(V8JUICE_CXXFLAGS)  \
  -I"$(V8ROCKET_HOME)/Include" \

V8ROCKET_CXXFLAGS = -I"$(V8ROCKET_HOME)/Include"
V8ROCKET_SRCPATH = $(V8ROCKET_HOME)/Source

V8ROCKET_OBJECTS = \
  $(V8ROCKET_OBJPATH)/Browser.o

LIBV8ROCKET = $(V8ROCKET_LIBPATH)/libv8.a
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

###############################################################

###############################################################
##Cleanup Targets
###############################################################
clean.v8rocket:
	rm -f $(V8ROCKET_OBJECTS) $(LIBV8ROCKET)

###############################################################
