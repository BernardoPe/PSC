# makefile to generate static and dynamic libraries

CFLAGS = -Wall -pedantic -c -Og -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LFLAGS = -lglib-2.0
STRUCT_PATH = ../structs
HEADER_FILES = $(STRUCT_PATH)/dictionary.h

LIB_STATIC = libdictionary.a

LIB_DYNAMIC = libdictionary.so

ALL = $(LIB_STATIC) $(LIB_DYNAMIC)

all: $(ALL)

static: $(LIB_STATIC)

dynamic: $(LIB_DYNAMIC)

$(LIB_STATIC): dictionary.o
	ar rcs $@ $^

$(LIB_DYNAMIC): dictionaryshared.o
	gcc -fpic -shared -o $@ $^ $(LFLAGS)

dictionary.o: $(STRUCT_PATH)/dictionary.c $(HEADER_FILES)
	gcc $(CFLAGS) $< 

dictionaryshared.o: $(STRUCT_PATH)/dictionary.c $(HEADER_FILES)
	gcc $(CFLAGS) -fpic -o dictionaryshared.o $< 
	
clean:
	rm -f *.o $(ALL)