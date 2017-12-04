all: joshell.c parse_in.c
	gcc -o joshell joshell.c parse_in.c 
run: all
	./joshell

clean:
	touch joshell
	rm joshell

