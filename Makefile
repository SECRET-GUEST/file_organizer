CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Isrc
LDFLAGS = `pkg-config --libs gtk+-3.0` -ljson-c

SOURCES = $(shell find src -name '*.c')

all: File_organizer

File_organizer: $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f File_organizer
