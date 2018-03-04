/* -----------------------------------------------------------------------
 * cardtest3.c
 * Unit test for villageFnc() called in cardEffect() in dominion.c, which 
 * should add 1 cards to the currentPlayer's hand from their deck, and
 * should add 2 actions.No other state changes should be made to other 
 * players or to the victory or kingdom cards.
 * Source: this unit test was modified from cardtest4.c 
 * (given to the CS362 400 W2018 class for reference).
 *
 * Include the following lines in your makefile:
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"


int main() {
    int newCards = 1;
    int discarded = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int passing = 1;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: +1 card to hand --------------
	printf("\nTEST 1: handCount= +1 - discarded, \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	if(testG.handCount[thisPlayer] != (G.handCount[thisPlayer]+newCards-discarded))
		passing = 0;
	printf("currentPlayer hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	

	// ----------- TEST 2: -1 card from deck, discardCount should +1 --------------
	printf("\nTEST 2: -1 card from deck, discardCount should +1\n");
	if(testG.deckCount[thisPlayer] != (G.deckCount[thisPlayer]-newCards))
		passing = 0;
	printf("currentPlayer deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	
	if(testG.discardCount[thisPlayer] != (G.discardCount[thisPlayer]+1))
		passing = 0;
	printf("currentPlayer discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+1);


	// ----------- TEST 3: +2 actions --------------
	printf("\nTEST 3: +2 actions\n");
	if(testG.numActions != (G.numActions+2))
		passing = 0;
	printf("currentPlayer number of actions = %d, expected = %d\n", testG.numActions, G.numActions+2);	
	
	// ----------- TEST 4: No state changes for other player --------------
	printf("\nTEST 4: No state changes for other player\n");
	if(testG.handCount[thisPlayer+1] != G.handCount[thisPlayer+1])
		passing = 0;
	printf("other player hand count = %d, expected = %d\n", testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1]);
	
	if(testG.deckCount[thisPlayer+1] != G.deckCount[thisPlayer+1])
		passing = 0;	
	printf("other player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1]);
	
	if(testG.discardCount[thisPlayer+1] != G.discardCount[thisPlayer+1])
		passing = 0;	
	printf("other player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer+1], G.discardCount[thisPlayer+1]);


	// ----------- TEST 5: No state changes to victory or kingdom cards --------------

	printf("\nTEST 5: No state changes to victory or kingdom cards\n");

	// cycle through each card supply
	for(i = 0; i < 27; i++) {
		if(testG.supplyCount[i] != G.supplyCount[i])
			passing = 0;
		printf("Supply for CARD enum[%d] is %d, expected %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
	}	
	
	if(passing == 1)
		printf("\nAll village tests passed!\n");
	else
		printf("\nAt least one village test failed.\n");


	return 0;
}


