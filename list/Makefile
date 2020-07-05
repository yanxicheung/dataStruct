CC = g++
LIBS+= -lgtest -lpthread
INCLUDE= -I ./inc

SRC  = $(wildcard ./src/*.c)
SRCOBJ = $(patsubst %.c, %.o, $(SRC))

TESTCASESRC = $(wildcard ./test/*.cpp)
CASEOBJ = $(patsubst %.cpp,%.o, $(TESTCASESRC))

TARGET = main.out

.PHONY: all clean


all: $(TARGET)

$(TARGET): $(SRCOBJ) $(CASEOBJ) 
	$(CC)  -o $@ $^  $(LIBS)  $(INCLUDE)

.c.o:$(SRCOBJ)
	$(CC) -c $(INCLUDE) -o $@ $< 

.cpp.o:$(TESTCASESRC)
	$(CC) -c $(INCLUDE) -o $@ $<


SUBDIR = $(shell ls ./ -R | grep /)
SUBDIRS  = $(subst :,/,$(SUBDIR))
SOURCE = $(foreach dir, $(SUBDIRS),$(wildcard $(dir)*.o))
clean:
	-rm -rf *~ $(SOURCE) $(TARGET)

