#
#description: make the app GM02-LTE02
#Auther	:HDWei
#time	:2019-11-20
#

DIR_CUR=$(shell pwd)
DIR_BIN = ./bin
DIR_MODBUSINC = ./include
DIR_LIBMODBUS = ./libmodbus
DIR_TARGET = ./target
DIR_SENSOR = ./sensors

LIBVAR = -static -lmodbus
LIB = -L${DIR_LIBMODBUS} 

INC = -I${DIR_MODBUSINC}\
      -I${DIR_SENSOR}

SRC = ${wildcard  ${DIR_TARGET}/*.c}\
	  ${wildcard  ${DIR_SENSOR}/*.c} 



OBJS = ${patsubst %.c, %.o, ${SRC}}

TARGET=${DIR_BIN}/modbus-rtu
ARCH = "x86"

ifeq ("arm",${ARCH})
     CC=arm-linux-gnueabihf-gcc
	@echo ${CC}
else
     CC=gcc
endif

CFLAGS = -g -O -Wall 

${TARGET}: ${OBJS} 
	${CC} ${OBJS} ${LIB} ${LIBVAR} -o $@
	@echo "compile done..."

$(OBJS):%.o:%.c
	@echo "compiling $< ==> $@"
	${CC} ${CFLAGS} ${INC} -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
	@echo "clean done"

