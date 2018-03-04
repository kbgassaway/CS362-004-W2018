/* --------------------------------------------------------------------------------
 * randomtestcard1.c
 * Random tester for villageFnc() called in cardEffect() in dominion.c, which 
 * should add 1 card to the currentPlayer's hand from their deck,
 * should add 2 actions, and should discard village card. 
 * No other state changes should be made to other players or to the victory or 
 * kingdom cards.
 * Source: this automated random test generator and oracle test was modified 
 * from cardtest4.c (given to the CS362 400 W2018 class for reference).
 *
 * Include the following lines in your makefile:
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "village"

int checkVillageFnc(int choice1, int choice2, int choice3, struct gameState *preG, int thisPlayer, int handpos, int *bonus){
	
	struct gameState postG;
	int newCards = 1;
    int discarded = 1;
	int passing = 1;
	int i;

	// copy the pregame state to a test case
	memcpy(&postG, preG, sizeof(struct gameState));
	//postgame state calls village card
	cardEffect(village, choice1, choice2, choice3, &postG, handpos, bonus);


	// ----------- TEST 1: +1 card to hand - played village card--------------
	//printf("test 1\n");
	if(postG.handCount[thisPlayer] != (preG->handCount[thisPlayer]+newCards-discarded)){
		passing = 0;
		printf("currentPlayer hand count = %d, expected = %d\n", postG.handCount[thisPlayer], preG->handCount[thisPlayer] + newCards - discarded);
	}

	// ----------- TEST 2: If pre deckCount is 0, then post deckCount should be pre discardCount -1, and discardCount =1 --------------
	// ----------- TEST 2: Else, deckCount should -1, and discardCount +1 --------------
	//printf("test 2\n");	
	if(preG->deckCount[thisPlayer] <= 0){
		if(postG.deckCount[thisPlayer] != preG->discardCount[thisPlayer]-newCards){
			passing = 0;
			printf("currentPlayer deck count = %d, expected = %d\n", postG.deckCount[thisPlayer], preG->discardCount[thisPlayer] - newCards);
		}
		if(postG.discardCount[thisPlayer] != discarded){
			passing = 0;
			printf("currentPlayer discard count = %d, expected = %d", postG.discardCount[thisPlayer], discarded);
		}
	}		
	else {
		if(postG.deckCount[thisPlayer] != (preG->deckCount[thisPlayer]-newCards)){
			passing = 0;
			printf("currentPlayer deck count = %d, expected = %d\n", postG.deckCount[thisPlayer], preG->deckCount[thisPlayer] - newCards);
		}
		if(postG.discardCount[thisPlayer] != (preG->discardCount[thisPlayer]+discarded)){
			passing = 0;
			printf("currentPlayer discard count = %d, expected = %d\n", postG.discardCount[thisPlayer], preG->discardCount[thisPlayer]+discarded);
		}
	}

	// ----------- TEST 3: +2 actions --------------
	//printf("test 3\n");
	if(postG.numActions != (preG->numActions+2)){
		passing = 0;
		printf("currentPlayer number of actions = %d, expected = %d\n", postG.numActions, preG->numActions+2);	
	}
	
	// ----------- TEST 4: No state changes for other player --------------
	//printf("test 4\n");
	for(i = 0; i < postG.numPlayers; i++){
		if(i != thisPlayer){
			if(postG.handCount[i] != preG->handCount[i]){
				passing = 0;
				printf("other player hand count = %d, expected = %d\n", postG.handCount[i], preG->handCount[i]);
			}
			if(postG.deckCount[i] != preG->deckCount[i]){
				passing = 0;	
				printf("other player deck count = %d, expected = %d\n", postG.deckCount[i], preG->deckCount[i]);
			}
			if(postG.discardCount[i] != preG->discardCount[i]){
				passing = 0;	
				printf("other player discard count = %d, expected = %d\n", postG.discardCount[i], preG->discardCount[i]);
			}
		}
	}

	// ----------- TEST 5: No state changes to victory or kingdom cards --------------
	//printf("test 5\n");

	// cycle through each card supply
	for(i = 0; i < 27; i++) {
		if(postG.supplyCount[i] != preG->supplyCount[i]){
			passing = 0;
			printf("Supply for CARD enum[%d] is %d, expected %d\n", i, postG.supplyCount[i], preG->supplyCount[i]);
		}
	}
	
	return passing;
}	


int main() {

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int i, j;
    int numPlayers, thisPlayer;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			gardens, tribute, smithy, council_room};
	int passing = 1;

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf ("RANDOM TESTS.\n");
	
	srand(time(NULL));
	
	for (i = 0; i < 100; i++) {
		numPlayers = 2 + rand() % 3;
		//printf("\n numPlayers = %d\n", numPlayers);
		memset(&G, 23, sizeof(struct gameState));
		initializeGame(numPlayers, k, 1, &G);
		thisPlayer = rand() % numPlayers;
		//printf("thisPlayer: %d\n", thisPlayer);
		G.whoseTurn = thisPlayer;
		G.deckCount[thisPlayer] = rand() % MAX_DECK;
		G.discardCount[thisPlayer] = rand() % MAX_DECK;
		G.handCount[thisPlayer] = 1 + rand() % 499;
		
		//fill players deck
		for(j = 0; j < G.deckCount[thisPlayer]; j++){
			G.deck[thisPlayer][j] = rand() % 28;
		}
		//fill players discard
		for(j = 0; j < G.discardCount[thisPlayer]; j++){
			G.discard[thisPlayer][j] = rand() % 28;
		}
		//fill players hand
		for(j = 0; j < G.handCount[thisPlayer]; j++){
			G.hand[thisPlayer][j] = rand() % 28;
		}
				
		printf("\ncall %d to checkVillageFnc\n", i+1);
		passing = checkVillageFnc(choice1, choice2, choice3, &G, thisPlayer, handpos, &bonus);
	}
		
	
	if(passing == 1)
		printf("\nAll village tests passed!\n");
	else
		printf("\nAt least one village test failed.\n");


	return 0;
}


