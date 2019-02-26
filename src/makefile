OBJS = main.o bst.o movie.o parse.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : main

main : $(OBJS)
		gcc $(LOPTS) $(OBJS) -o main

main.o : main.c
		gcc $(OOPTS) main.c

bst.o : bst.c bst.h
		gcc $(OOPTS) bst.c

movie.o : movie.c movie.h
		gcc $(OOPTS) movie.c

parse.o : parse.c parse.h
		gcc $(OOPTS) parse.c

run : main
		./main

valgrind : main
		valgrind ./main

assembly : main.o
		otool -tv main.o

clean	:
		rm -f $(OBJS) main
