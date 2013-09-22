CC=gcc
LDFLAGS=-g `pkg-config --libs gtk+-2.0`
CFLAGS=-Wall `pkg-config --cflags gtk+-2.0`
PROG=test-gtk-frame-hig

all: $(PROG)

test-gtk-frame-hig: gtk-frame-hig.o test-gtk-frame-hig.o
	$(CC) -o $@ gtk-frame-hig.o test-gtk-frame-hig.o $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(PROG)
