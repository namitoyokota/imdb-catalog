OBJS = main.o parse.o queue.o bst.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : main

main : $(OBJS)
		gcc $(LOPTS) $(OBJS) -o main

n : n.c
		cc -o n n.c -lncurses 
		./n

main.o : main.c
		gcc $(OOPTS) main.c

parse.o : parse.c parse.h
		gcc $(OOPTS) parse.c

queue.o : queue.c queue.h
		gcc $(OOPTS) queue.c

bst.o : bst.c bst.h
		gcc $(OOPTS) bst.c

run : main
		./main

runn : n
		./n

valgrind : main
		valgrind ./main

clean	:
		rm -f $(OBJS) main
		rm -f n
