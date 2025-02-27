all: flex gcc

gcc: 
	gcc lexLib.c al.c

flex:
	flex --outfile=al.c al.l

clean:
	rm a.out