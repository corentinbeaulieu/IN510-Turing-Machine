src= src/main.c src/partie1.c src/partie1.h src/partie2.c src/partie2.h
files= Makefile compte_rendu.pdf
MT= MT/mt1 MT/mt2 MT/mt3 MT/mtQ6 MT/mtQ7
repository= YS_BEAULIEU_Corentin-SCHWEISTHAL_Victor

.PHONY: run
run: mt
	./mt MT/mt3 100

mt:  main.o partie1.o partie2.o
	gcc -Wall $^ -o $@

main.o: src/main.c src/partie1.h src/partie2.h
	gcc -Wall -c src/main.c

partie1.o: src/partie1.c src/partie1.h
	gcc -Wall -c src/partie1.c

partie2.o: src/partie2.c src/partie2.h src/partie1.h
	gcc -Wall -c src/partie2.c

.PHONY: test
test: mt
	./mt MT/mt1 000
	./mt MT/mt2 10101
	./mt MT/mt3 1000
	./mt -6 MT/mtQ6 mtQuestion6
	./mt mtQuestion6 111
	./mt -7 MT/mtQ7 mtQuestion7
	./mt mtQuestion7 00011110111100 #abdcdda


.PHONY: debug
debug:
	gcc -g main.c partie1.c partie1.h partie2.c partie2.h -o mt
	gdb ./mt


.PHONY:clean
clean:
	rm -fv mt *.o sortieMT mtQuestion6 mtQuestion7

.PHONY: zip
zip: 
	rm -rf $(repository)
	mkdir $(repository)
	mkdir $(repository)/src $(repository)/MT
	cp $(src) $(repository)/src/
	cp $(MT) $(repository)/MT/
	cp $(files) $(repository)/
	zip -r $(repository).zip $(repository)
	rm -rf $(repository)
