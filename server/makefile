TARGET = main
CPPINC=/usr/local/include
WORK_PATH=..
PUBFUNINC=$(WORK_PATH)/pubfun/inc

INCLUDES = -I./inc -I$(CPPINC) \
					 -I$(PUBFUNINC) \
					 
SYSLIB=-lpthread

PUBFUN_LIB=${WORK_PATH}/lib

CC=g++ -fPIC
CCR=g++
CPPFLAGS=-c -Wno-deprecated -std=c++0x
DEBUG_FLAG=-DH_DEBUG

GLOG_LIB=-lglog
MEMCACHED_LIB=-lmemcached
PUBFUN_LIB=$(WORK_PATH)/lib

SER_LIB=-L$(PUBFUN_LIB)/ -lpubfun
	
.SUFFIXES:
.SUFFIXES: .cpp .hpp .c .h .o .so .ec .C


.cpp.o:
	@echo $<
	$(CC)  $(INCLUDES) $(CPPFLAGS) $< -c -o $@
.c.o:
	@echo $<
	$(CC)  $(INCLUDES) $(CPPFLAGS) $< -c -o $@
.C.o:
	@echo $<
	$(CC)  $(INCLUDES) $(CPPFLAGS) $< -c -o $@
	
all: $(TARGET)
	
clean:
	-rm -f *.o main
	
main:main.o $(PUBFUN_LIB)
		$(CCR) -o main $(SER_LIB) $(GLOG_LIB) $(MEMCACHED_LIB) main.o
	
	