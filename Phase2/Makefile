all: calc

bison:
	bison --yacc --defines --output=parser.cpp parser.y

flex:
	flex --outfile=al.c al.l

lexLib.o:
	gcc -c lexLib.c -o lexLib.o

al.o:
	gcc -c al.c -o al.o

comment.o:
	gcc -c comment.c -o comment.o

parser.o:
	g++ -c parser.cpp -o parser.o

analysis.o:
	g++ -c analysis.cpp -o analysis.o

calc: bison flex lexLib.o al.o comment.o parser.o analysis.o
	g++ -o calc lexLib.o al.o comment.o parser.o analysis.o

clean:
	rm -f *.o calc al.c parser.cpp parser.h
