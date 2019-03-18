OBJS = ./src/main.o ./src/rbt.o ./src/crud.o ./src/logger.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : main

main : $(OBJS)
		gcc $(LOPTS) $(OBJS) -o ./src/main -lncurses

download : 
		# if the 'movie_records.tsv' file does NOT exist, download and parse
		if [ -d "./src/data/movie_records.tsv" ]; then \
			wget https://datasets.imdbws.com/title.basics.tsv.gz -P ./src/data/; \
			gunzip ./src/data/title.basics.tsv.gz; \
			grep "movie" ./src/data/title.basics.tsv > ./src/data/movie_records.tsv; \
			rm ./src/data/title.basics.tsv; \
		fi
		#if ./logs directory does not exist, create the directory
		if [ ! -d "./src/logs" ]; then mkdir ./src/logs; fi

main.o : ./src/main.c
		gcc $(OOPTS) ./src/main.c

rbt.o : ./src/rbt.c ./src/rbt.h
		$(SRC) gcc $(OOPTS) ./src/rbt.c

crud.o : ./src/crud.c ./src/crud.h
		$(SRC) gcc $(OOPTS) ./src/crud.c

logger.o : ./src/logger.c ./src/logger.h
		$(SRC) gcc $(OOPTS) ./src/logger.c

run : main
		$(SRC) ./src/main

valgrind : main
		$(SRC) valgrind ./src/main

clean :
		# clean outputted files
		rm -f $(OBJS) ./src/main
		rm -f ./src/logs/*.log
