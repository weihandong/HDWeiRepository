#
#description: make the app GM02-LTE02
#Auther	:HDWei
#time	:2019-11-20
#

DIR_CUR = $(shell pwd)
DIR_INC = ./include
DIR_SRC = ./src
DIR_LIB = ./lib
DIR_OBJ = ./obj
DIR_DEPS= ./deps
DIR_BIN = ./bin
LIBVAR = ${DIR_LIB}/libcurl.a

#vpath %.c src2
###################include头文件路径##################################
INC = -I${DIR_INC}
###################lib文件及路径######################################
LIB = -L${DIR_LIB}  
###################OBJ文件及路径######################################
#SRC = ${wildcard  ${DIR_SRC}/*.cpp}
#OBJS = ${patsubst %.cpp, ${DIR_OBJ}/%.o, ${SRC}}
#SRC = $(wildcard *.cpp) $(notdir $(wildcard ${DIR_SRC}/*.cpp))

OBJS=$(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.o,$(wildcard $(DIR_SRC)/*.cpp))
DEPS=$(patsubst $(DIR_OBJ)/%.o, $(DIR_DEPS)/%.d, $(OBJS))

###################编译选项及编译器###################################
ARCH = "x86"
ifeq ("arm",${ARCH})
     CC=arm-linux-gnueabihf-g++
	@echo ${CC}
else
     CC=g++
endif
CFLAGS = -g -O -Wall -lpthread 
###################编译目标###########################################
TARGET=${DIR_BIN}/test

${TARGET}: ${OBJS} 
	@echo "compil $< ==> $@  <-- ${DIR_OBJ}"
	${CC} -o $@ ${DIR_OBJ} ${LIBVAR}

${DIR_OBJ}/%.o : ${SRC}%.cpp
	@echo "compiling $< ==> $@  <---${OBJS}
	${CC} -c $< -o $@ ${CFLAGS} ${INC}

clean:
	rm -rf $(OBJS) $(DIR_BIN)/*
	
	@echo "clean done"

