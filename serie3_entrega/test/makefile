
CFLAGS = -Wall -pedantic -Og -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LFLAGS = -lglib-2.0
STRUCT_PATH = ../structs
HEADER_FILES = $(STRUCT_PATH)/dictionary.h

LIB_DIR = ../libraries

ALL = dictionarytest-static dictionarytest-dynamic

all: $(ALL)

dictionarytest-static: dictionarytest.o $(LIB_DIR)/libdictionary.a
	gcc -o $@ $^ $(LIB_DIR) $(LFLAGS)

dictionarytest-dynamic: dictionarytest.o $(LIB_DIR)/libdictionary.so
	gcc -o $@ $^ $(LIB_DIR) $(LFLAGS)

clean:
	rm -f *.o $(ALL)
