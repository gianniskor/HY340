all: flex gcc

gcc: 
	gcc lexLib.c al.c

flex:
	flex --outfile=al.c

clean:
	rm a.out