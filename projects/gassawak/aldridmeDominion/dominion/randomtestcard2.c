/* -----------------------------------------------------------------------
 * randomtestcard2.c
 * Unit test for council_room passed to cardEffect() in dominion.c, which 
 * should add 4 cards to the currentPlayer's hand from their deck, and
 * should add 1 buy. Each other player draws 1 card from their deck.
 * No state changes should be made to the victory or kingdom cards.
 * Source: this unit test was modified from randomtestcard2.c 
 * (given to the CS362 400 W2018 class for reference).
 *
 * Include the following lines in your makefile:
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "council_room"


int checkCouncilRoom(int choice1, int choice2, int choice3, struct gameState *preG, int thisPlayer, int handpos, int *bonus){
	
	struct gameState postG;
	int newCards = 4;
    int discarded = 1;
	int otherNewCards = 1;
	int passing = 1;
	int i;
	
	// copy the pregame state to a test case
	memcpy(&postG, preG, sizeof(struct gameState));
	//postgame state calls council_room card
	cardEffect(council_room, choice1, choice2, choice3, &postG, handpos, bonus);

	// ----------- TEST 1: +4 cards to hand --------------
	//printf("\nTEST 1: handCount= +4 - discarded, \n");
	
	if(postG.handCount[thisPlayer] != (preG->handCount[thisPlayer]+newCards-discarded)){
		passing = 0;
		printf("currentPlayer hand count = %d, expected = %d\n", postG.handCount[thisPlayer], preG->handCount[thisPlayer] + newCards - discarded);
	}

	// ----------- TEST 2: -4 card from deck+discard, discard council_room card --------------
	//printf("\nTEST 2: -4 card from deck + discard, discard 1 card\n");
	if(preG->deckCount[thisPlayer] < 4){
		if(postG.deckCount[thisPlayer] != (preG->deckCount[thisPlayer] + preG->discardCount[thisPlayer] -4)){
			passing = 0;
			printf("currentPlayer deck count = %d, expected = %d\n", postG.deckCount[thisPlayer], (preG->deckCount[thisPlayer] + preG->discardCount[thisPlayer] -4));
		}
		if(postG.discardCount[thisPlayer] != discarded){
			passing = 0;
			printf("currentPlayer discard count = %d, expected = %d\n", postG.discardCount[thisPlayer], discarded);
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

	// ----------- TEST 3: +1 buy --------------
	//printf("\nTEST 3: +1 buy\n");
	if(postG.numBuys != (preG->numBuys+1)){
		passing = 0;
		printf("currentPlayer number of buys = %d, expected = %d\n", postG.numBuys, preG->numBuys+1);	
	}
	
	// ----------- TEST 4: Each other player draws 1 card from their deck --------------
	//printf("\nTEST 4: Each other player draws 1 card from their deck\n");
	for(i = 0; i < postG.numPlayers; i++){
		if(i != thisPlayer){
			if(postG.handCount[i] != (preG->handCount[i]+otherNewCards)){
				passing = 0;
				printf("other player hand count = %d, expected = %d\n", postG.handCount[i], preG->handCount[i]+otherNewCards);
			}
			if(postG.deckCount[i] != (preG->deckCount[i]-otherNewCards)){
				passing = 0;	
				printf("other player deck count = %d, expected = %d\n", postG.deckCount[i], (preG->deckCount[i]-otherNewCards));
			}
			if(postG.discardCount[i] != preG->discardCount[i]){
				passing = 0;	
				printf("other player discard count = %d, expected = %d\n", postG.discardCount[i], preG->discardCount[i]);
			}
		}
	}
	
	// ----------- TEST 5: No state changes to victory or kingdom cards --------------
	//printf("\nTEST 5: No state changes to victory or kingdom cards\n");

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
		memset(&G, 23, sizeof(struct gameState));
		initializeGame(numPlayers, k, 1, &G);
		thisPlayer = rand() % numPlayers;
		//printf("\nnumPlayers = %d; thisPlayer = %d \n", numPlayers, thisPlayer);
		G.whoseTurn = thisPlayer;
		G.deckCount[thisPlayer] = rand() % MAX_DECK;
		G.discardCount[thisPlayer] = rand() % MAX_DECK;
		G.handCount[thisPlayer] = 1 + rand() % 499;
		//printf("thisPlayer deckCount = %d, discardCount = %d, handCount = %d \n", G.deckCount[thisPlayer], G.discardCount[thisPlayer], G.handCount[thisPlayer]);
		
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
				
		printf("\ncall %d to checkCouncilRoom\n", i+1);
		passing = checkCouncilRoom(choice1, choice2, choice3, &G, thisPlayer, handpos, &bonus);
	}	
	
	if(passing == 1)
		printf("\nAll council_room tests passed!\n");
	else
		printf("\nAt least one council_room test failed.\n");

	return 0;
}


