CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
	
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)	
	
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randomtestcard1.out: randomtestcard1 
	echo "Results for running random tests:" > randomtestcard1.out
	
	rm -f dominion.gcda
	echo "randomtestcard1:" >> randomtestcard1.out
	randomtestcard1 >> randomtestcard1.out
	gcov -abcfu dominion.c | sed -n '/villageFnc/{n;p; n;p; n;p; n;p;}' >> randomtestcard1.out

randomtestcard2.out: randomtestcard2 
	echo "Results for running random tests:" > randomtestcard2.out
	
	rm -f dominion.gcda
	echo "randomtestcard2:" >> randomtestcard2.out
	randomtestcard2 >> randomtestcard2.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p; n;p;}' >> randomtestcard2.out	
	
randomtestadventurer.out: randomtestadventurer
	echo "Results for running random tests:" > randomtestadventurer.out
	
	rm -f dominion.gcda
	echo "randomtestadventurer:" >> randomtestadventurer.out
	randomtestadventurer >> randomtestadventurer.out
	gcov -abcfu dominion.c | sed -n '/adventurerFnc/{n;p; n;p; n;p; n;p;}' >> randomtestadventurer.out

	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randomtestcard1 randomtestcard1.out randomtestcard2 randomtestcard2.out randomtestadventurer randomtestadventurer.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out 
	rm -f *.o randomtestcard1 randomtestcard2 randomtestadventurer


