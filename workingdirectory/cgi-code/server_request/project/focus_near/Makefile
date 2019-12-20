
#description: make the app GM02-LTE02
#Auther	:HDWei
#time	:2019-11-20
#

ARCH = "x86"
#CXX  =
CXXFLAGS = -g -Wall 
DIR_CUR=$(shell pwd)

DIR_BIN = ../../bin/Control
DIR_LIB = ../../lib
DIR_INC = ../../include
DIR_SRC = ../../src/focus_near
DIR_COMMON = ../../common

LIBVAR = -static -lcjson

INC = -I${DIR_INC}

LIB = -L${DIR_LIB}

SRC = ${wildcard  ${DIR_SRC}/*.cpp}\
	  ${wildcard  ${DIR_COMMON}/*.cpp}

OBJS = ${patsubst %.cpp, %.o, ${SRC}}

TARGET = ${DIR_BIN}/FocusNear

ifeq ("arm",${ARCH})
     CXX=arm-linux-gnueabihf-g++
	@echo ${CXX}
else
     CXX = g++
endif


$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LIB) $(LIBVAR) -o $@
	@echo "compile done..."

$(OBJS):%.o : %.cpp
	@echo "compiling $< ==> $@"
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
	@echo "clean done"

