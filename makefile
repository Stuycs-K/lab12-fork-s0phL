run: runme
	@./runme

compile runme: main.c
	@gcc -o runme main.c

clean:
	rm -f *.o runme
