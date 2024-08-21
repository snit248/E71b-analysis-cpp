CXX           = g++
CXXFLAGS      = -O2 -pipe -Wall -W -Woverloaded-virtual -fPIC

ROOTCONFIG = root-config
ROOTCFLAGS:= $(shell $(ROOTCONFIG) --cflags)
ROOTLIBS  := $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS := $(shell $(ROOTCONFIG) --glibs)
MAKEDIR=${PWD}/../library

CXXFLAGS+= $(ROOTCFLAGS)
CXXFLAGS+= -g
LIBS     = $(ROOTLIBS)

all: BMBasicRecon BMBeaminfo BMBSD

BMBasicRecon:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp ${CXXFLAGS} -o ${MAKEDIR}/lib$(@).so

BMBeaminfo:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp ${CXXFLAGS} -o ${MAKEDIR}/lib$(@).so

BMBSD:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp ${CXXFLAGS} -o ${MAKEDIR}/lib$(@).so

move:
	mv ./*pcm ${MAKEDIR}/

clean:
	$(RM) -f *.o *~ *Dict.* *pcm ${MAKEDIR}/*.pcm ${MAKEDIR}/*.so  ${OBJS} chkfort
