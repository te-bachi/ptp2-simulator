
PROGRAM=gtk-paned-move
SOURCE=main.c
OBJECT=$(SOURCE:%.c=%.o)
CFLAGS=`pkg-config --cflags gtk+-3.0`
LDFLAGS=`pkg-config --libs gtk+-3.0`

all: $(PROGRAM)
	

$(PROGRAM): $(OBJECT)
	gcc -o $(PROGRAM) $(OBJECT) $(LDFLAGS)

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(PROGRAM) $(OBJECT)
