par-shell: list.o commandlinereader.o par-shell.o
	gcc -o par-shell list.o commandlinereader.o par-shell.o

list.o: list.c list.h
	gcc -Wall -g -c list.c

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc -Wall -g -c commandlinereader.c

par-shell.o: par-shell.c commandlinereader.h
	gcc -Wall -g -c par-shell.c

clean: 
	rm -f *.o par-shell