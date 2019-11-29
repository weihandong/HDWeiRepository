#
#description: make the app GM02-LTE02
#Auther	:HDWei
#time	:2019-11-20
#

DIR_CUR=$(shell pwd)
DIR_MODBUSINC= ./include
DIR_LIBMODBUS= ./lib
DIR_TARGET= ./target

LIBVAR = libcurl.a  -lrt 
INC = -I${DIR_MODBUSINC}
LIB = -L${DIR_LIBMODBUS}  

SRC =  ${wildcard  ${DIR_LIBMODBUS}/*.C}\
       ${wildcard  ${DIR_TARGET}/*.c}



OBJS = ${patsubst %.c, %.o, ${SRC}}

TARGET=curl
ARCH = "x86"

ifeq ("arm",${ARCH})
     CC=arm-linux-gnueabihf-gcc
	@echo ${CC}
else
     CC=gcc
endif

CFLAGS = -g -O -Wall 

${TARGET}: ${OBJS} 
	@echo ${OBJS}
	${CC} ${OBJS}  ${LIB} ${LIBVAR} -o $@
	@echo "compile done..."

$(OBJS):%.o:%.c
	@echo "compiling $< ==> $@"
	${CC} -c $< -o $@ ${CFLAGS} ${INC}

clean:
	rm -rf $(TARGET) $(OBJS)
	@echo "clean done"

