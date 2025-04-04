all: calc

bison:
	bison  --yacc --defines --output=parser.cpp parser.y

flex:
	flex --outfile=al.cpp al.l

lexLib.o:
	g++ -c lexLib.cpp -o lexLib.o

al.o:
	g++ -std=c++11 -c al.cpp -o al.o

comment.o:
	g++ -c comment.cpp -o comment.o

parser.o:
	g++ -std=c++11 -c parser.cpp -o parser.o

analysis.o:
	g++ -c analysis.cpp -o analysis.o

symtable.o:
	g++ -c symtable.cpp -o symtable.o

calc: flex bison lexLib.o al.o comment.o parser.o analysis.o symtable.o
	g++ -o calc lexLib.o al.o comment.o parser.o analysis.o symtable.o

clean:
	rm -f *.o calc al.cpp parser.cpp parser.hpp


