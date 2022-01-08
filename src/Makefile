files= Makefile main.c partie1.c partie1.h partie2.c partie2.h partie3.c partie3.h
repository= YS_BEAULIEU_SCHWEISTHAL

.PHONY: run
run: mt
	./mt

mt:  main.o partie1.o partie2.o partie3.o
	gcc -Wall $^ -o $@

main.o: main.c partie1.h partie2.h partie3.h
	gcc -Wall -c main.c

partie1.o: partie1.c partie1.h
	gcc -Wall -c partie1.c

partie2.o: partie2.c partie2.h partie1.h
	gcc -Wall -c partie2.c

partie3.o: partie3.c partie3.h partie2.h
	gcc -Wall -c partie3.c

.PHONY: test
test: mt
	./mt ../mt/mt1 000
	./mt -6 ../mt/mtQ6 mtQuestion6
	./mt mtQuestion6 111


.PHONY: debug
debug:
	gcc -g main.c io.h io.c mt.c mt.h -o mt
	gdb mt


.PHONY:clean
clean:
	rm -fv mt *.o sortieMT

.PHONY: zip
zip: 
	rm -rf $(repository)
	mkdir $(repository)
	cp $(files) $(repository)/
	zip -r $(repository).zip $(repository)
	rm -rf $(repository)
