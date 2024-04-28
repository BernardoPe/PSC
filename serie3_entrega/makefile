CC = gcc
CFLAGS = -Wall -pedantic -g -Og -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LFLAGS = -lglib-2.0
STRUCT_PATH = structs
HEADER_FILES = $(STRUCT_PATH)/dictionary.h 

TARGET = spell_check

all: $(TARGET)

$(TARGET): spellchecker.o $(STRUCT_PATH)/dictionary.o
	$(CC) -o $@ $^ $(LFLAGS)

spellchecker.o: spell.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c -o $@ $<

$(STRUCT_PATH)/dictionary.o: $(STRUCT_PATH)/dictionary.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(TARGET) $(STRUCT_PATH)/*.o
