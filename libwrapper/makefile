TARGET = tran
CPPINC=/usr/local/include
WORK_PATH=..

INCLUDES = -I./inc -I$(CPPINC) \
					 
SYSLIB=-lpthread

PUBFUN_LIB=${WORK_PATH}/lib

CC=g++ -fPIC
CCR=g++
CPPFLAGS=-c -Wno-deprecated -std=c++11
DEBUG_FLAG= -DH_DEBUG

SRCDIR=../libwrapper/src
OBJDIR=../libwrapper
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.cpp))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo $<
	$(CC) $(INCLUDES)  $(CPPFLAGS) $(DEBUG_FLAG) $< -o $@ 
	
	
all:tran

tran:$(OBJS)
	rm -f $(PUBFUN_LIB)/libwrapper.a
	ar -rv $(PUBFUN_LIB)/libwrapper.a ${OBJS}
	g++ -shared $(OBJS) -o $(PUBFUN_LIB)/libwrapper.so
	
clean:
	-rm $(OBJDIR)/*.o
