OBJS = ./src/main.o ./src/rbt.o ./src/crud.o ./src/logger.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : main

main : $(OBJS)
		gcc $(LOPTS) $(OBJS) -o ./bin/main -lncurses

download : 
		if [ ! -d "./log" ]; then mkdir ./log; fi
		if [ ! -d "./log" ]; then mkdir ./log; fi
		if [ ! -d "./bin" ]; then mkdir ./bin; fi
		if [ ! -d "./data/movie_records.tsv" ]; then \
			wget https://datasets.imdbws.com/title.basics.tsv.gz -P ./data/; \
			gunzip ./data/title.basics.tsv.gz; \
			grep "movie" ./data/title.basics.tsv > ./data/movie_records.tsv; \
			rm ./data/title.basics.tsv; \
		fi

main.o : ./src/main.c
		gcc $(OOPTS) ./src/main.c

rbt.o : ./src/rbt.c ./lib/rbt.h
		gcc $(OOPTS) ./src/rbt.c

crud.o : ./src/crud.c ./lib/crud.h
		gcc $(OOPTS) ./src/crud.c

logger.o : ./src/logger.c ./lib/logger.h
		gcc $(OOPTS) ./src/logger.c

run : main
		./bin/main

valgrind : main
		valgrind ./bin/main

clean :
		rm -f $(OBJS) ./bin/main
		rm -f ./logs/*.log
		rm -f ./.log
