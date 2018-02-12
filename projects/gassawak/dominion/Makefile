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

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)


cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittestresults.out: randomtestcard1 cardtest2 cardtest4
	echo "Results for running unit tests:" > unittestresults.out
	
	rm -f dominion.gcda
	echo "randomtestcard1:" >> unittestresults.out
	randomtestcard1 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/smithyFnc/{n;p; n;p; n;p; n;p;}' >> unittestresults.out
	
	rm -f dominion.gcda	
	echo "cardtest2:" >> unittestresults.out
	cardtest2 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/adventurerFnc/{n;p; n;p; n;p; n;p;}' >> unittestresults.out
	
	rm -f dominion.gcda	
	echo "cardtest4:" >> unittestresults.out
	cardtest4 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p; n;p;}' >> unittestresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randomtestcard1 cardtest2 cardtest4 unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out 
	rm -f *.o randomtestcard1 cardtest2 cardtest4 unittestresults.out


