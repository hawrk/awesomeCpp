TARGET = tran md5_main
CPPINC=/usr/local/include
WORK_PATH=..

INCLUDES = -I./inc -I$(CPPINC) \
					 
SYSLIB=-lpthread

PUBFUN_LIB=${WORK_PATH}/lib

CC=g++ -fPIC
CCR=g++
CPPFLAGS=-c -Wno-deprecated -std=c++11
DEBUG_FLAG= -DH_DEBUG

ENCRYPT_LIB=-L$(PUBFUN_LIB)/ -lencrypt

SRCDIR=../encrypt/src
OBJDIR=../encrypt
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.cpp))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo $<
	$(CC) $(INCLUDES)  $(CPPFLAGS) $(DEBUG_FLAG) $< -o $@ 
	
	
all:tran md5_main

tran:$(OBJS)
	rm -f $(PUBFUN_LIB)/libencrypt.a
	ar -rv $(PUBFUN_LIB)/libencrypt.a ${OBJS}
	g++ -shared $(OBJS) -o $(PUBFUN_LIB)/libencrypt.so
	
md5_main:md5_main.o 
	$(CCR) -o md5_main $(ENCRYPT_LIB) md5_main.o

clean:
	-rm $(OBJDIR)/*.o
