all: flex gcc

gcc: 
	gcc lexLib.c al.c comment.c

flex:
	flex --outfile=al.c al.l

clean:
	rm a.out