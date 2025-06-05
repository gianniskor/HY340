all: bison flex gcc

gcc: 
	g++ -std=c++11 -Wno-write-strings lexLib.cpp al.cpp comment.cpp syntax.cpp main.cpp expressions.cpp quad.cpp instruction.cpp

flex:
	flex --outfile=al.cpp al.l

bison:
	bison --defines  --output=syntax.cpp syntax.y

bisonC:
	bison --defines  -v --output=syntax.cpp syntax.y
	
clean:
	rm -f *.o a.out al.cpp yacc_output.txt syntax.hpp syntax.cpp al.hpp 
	rm -rf outputs/
