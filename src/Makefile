files= mt.c mt.h io.c io.h Makefile main.c
repository= MT_BEAULIEU_SCHWEISTHAL

.PHONY: run
run: mt
	./mt

mt: mt.o main.o io.o
	gcc -Wall $^ -o $@

main.o: main.c io.h mt.h
	gcc -Wall -c main.c

io.o: io.c io.h
	gcc -Wall -c io.c

mt.o: mt.c mt.h
	gcc -Wall -c mt.c


.PHONY: debug
debug:
	gcc -g main.c io.h io.c mt.c mt.h -o mt
	gdb mt


.PHONY:clean
clean:
	rm -fv mt mt.o main.o io.o


.PHONY: zip
zip: 
	rm -rf $(repository)
	mkdir $(repository)
	cp $(files) $(repository)/
	zip -r $(repository).zip $(repository)
	rm -rf $(repository)
