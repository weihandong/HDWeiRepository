#
#description: make the app GM02-LTE02
#Auther	:HDWei
#time	:2019-11-20
#

DIR_CUR=$(shell pwd)
DIR_MODBUSINC= ./include
DIR_LIBMODBUS= ./libmodbus
DIR_TARGET= ./target

LIBVAR = ${DIR_LIBMODBUS}/libmodbus.a
INC = -I${DIR_MODBUSINC}
LIB = -L${DIR_LIBMODBUS}  

SRC =  ${wildcard  ${DIR_LIBMODBUS}/*.cpp}\
       ${wildcard  ${DIR_TARGET}/*.cpp}



OBJS = ${patsubst %.cpp, %.o, ${SRC}}

TARGET=modbus-rtu
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
	${CC} -o $@ ${OBJS} ${LIB} ${LIBVAR}
	@echo "compile done..."

$(OBJS):%.o:%.cpp
	@echo "compiling $< ==> $@"
	${CC} ${CFLAGS} ${INC} -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
	@echo "clean done"

