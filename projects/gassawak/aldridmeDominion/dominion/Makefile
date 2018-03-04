CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)	

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)	
	
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)	

randomtestcard1.out: randomtestcard1 
	echo "Results for running random tests:" > randomtestcard1.out
	
	rm -f dominion.gcda
	echo "randomtestcard1:" >> randomtestcard1.out
	randomtestcard1 >> randomtestcard1.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p; n;p;}' >> randomtestcard1.out

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
	gcov -abcfu dominion.c | sed -n '/play_adventurer/{n;p; n;p; n;p; n;p;}' >> randomtestadventurer.out
	
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "Results for running unit tests:" > unittestresults.out
	
	rm -f dominion.gcda
	echo "unittest1:" >> unittestresults.out
	unittest1 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/getCost/{n;p; n;p; n;p; n;p;}' >> unittestresults.out

	rm -f dominion.gcda	
	echo "unittest2:" >> unittestresults.out
	unittest2 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/scoreFor/{n;p; n;p; n;p; n;p;}' >> unittestresults.out
	
	rm -f dominion.gcda	
	echo "unittest3:" >> unittestresults.out
	unittest3 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/getWinners/{n;p; n;p; n;p; n;p;}' >> unittestresults.out
	
	rm -f dominion.gcda
	echo "unittest4:" >> unittestresults.out
	unittest4 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/isGameOver/{n;p; n;p; n;p; n;p;}' >> unittestresults.out

	rm -f dominion.gcda
	echo "cardtest1:" >> unittestresults.out
	cardtest1 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/play_smithy/{n;p; n;p; n;p; n;p;}' >> unittestresults.out
	
	rm -f dominion.gcda	
	echo "cardtest2:" >> unittestresults.out
	cardtest2 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/play_adventurer/{n;p; n;p; n;p; n;p;}' >> unittestresults.out

	rm -f dominion.gcda	
	echo "cardtest3:" >> unittestresults.out
	cardtest3 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p; n;p;}' >> unittestresults.out
	
	rm -f dominion.gcda	
	echo "cardtest4:" >> unittestresults.out
	cardtest4 >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p; n;p;}' >> unittestresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out randomtestcard1 randomtestcard1.out randomtestcard2 randomtestcard2.out randomtestadventurer randomtestadventurer.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out unittest1  
	rm -f *.o unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f *.o unittestresults.out
	rm -f *.o randomtestcard1 randomtestcard2 randomtestadventurer