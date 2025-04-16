all: bison flex gcc

gcc: 
	g++ -std=c++11 lexLib.cpp al.cpp comment.cpp syntax.cpp main.cpp

flex:
	flex --outfile=al.cpp al.l

bison:
	bison --defines  --output=syntax.cpp syntax.y

bisonC:
	bison --defines  -v --output=syntax.cpp syntax.y
	
clean:
	rm -f a.out al.cpp
