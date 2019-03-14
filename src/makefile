OBJS = main.o queue.o rbt.o crud.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : main

main : $(OBJS)
		gcc $(LOPTS) $(OBJS) -o main -lncurses

download : 
		wget https://datasets.imdbws.com/title.basics.tsv.gz -P ./data/
		gunzip ./data/title.basics.tsv.gz
		grep "movie" ./data/title.basics.tsv > ./data/movie_records
		rm ./data/title.basics.tsv

main.o : main.c
		gcc $(OOPTS) main.c

n.o : n.c n.h
		gcc -o n n.c -lncurses

queue.o : queue.c queue.h
		gcc $(OOPTS) queue.c

rbt.o : rbt.c rbt.h
		gcc $(OOPTS) rbt.c

crud.o : crud.c crud.h
		gcc $(OOPTS) crud.c

run : main
		./main

runn : n
		./n

valgrind : main
		valgrind ./main

clean	:
		rm -f $(OBJS) main
		rm -f n
