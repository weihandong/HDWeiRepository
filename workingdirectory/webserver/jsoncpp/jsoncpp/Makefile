#
#description: make the app GM02-LTE02
#Auther	:HDWei
#time	:2019-11-20
#

DIR_CUR=$(shell pwd)
DIR_INC=./include
DIR_LIB= ./lib
DIR_TARGET=./target

LIBVAR = ${DIR_LIB}/libjsoncpp.a
INC = -I${DIR_INC}
LIB = -L${DIR_LIB}  

SRC =  ${wildcard  ${DIR_TARGET}/*.cpp}



OBJS = ${patsubst %.cpp, %.o, ${SRC}}

TARGET=jsoncpp-test
ARCH = "x86"

ifeq ("arm",${ARCH})
     CC=arm-linux-gnueabihf-g++
	@echo ${CC}
else
     CC=g++
endif

CFLAGS = -g -O -Wall 

${TARGET}: ${OBJS} 
	@echo ${OBJS}
	${CC} ${OBJS} -o $@ ${LIB} ${LIBVAR}
	@echo "compile done..."

$(OBJS):%.o:%.cpp
	@echo "compiling $< ==> $@"
	${CC} ${CFLAGS} ${INC} -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
	@echo "clean done"

