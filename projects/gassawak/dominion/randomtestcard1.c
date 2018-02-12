/* --------------------------------------------------------------------------------
 * randomtestcard1.c
 * Random tester for villageFnc() called in cardEffect() in dominion.c, which 
 * should add 1 cards to the currentPlayer's hand from their deck,
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

int checkVillageFnc(int choice1, int choice2, int choice3, &preG, handpos, &bonus){
	
	struct gameState postG;
	
	int newCards = 1;
    int discarded = 1;
	int passing;
	
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);


	// copy the game state to a test case
	memcpy(&postG, &preG, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &postG, handpos, &bonus);


	// ----------- TEST 1: +1 card to hand - played village card--------------
	//printf("\nTEST 1: handCount= +1 - discarded, \n");	
	if(postG.handCount[thisPlayer] != (preG.handCount[thisPlayer]+newCards-discarded)){
		passing = 0;
		printf("currentPlayer hand count = %d, expected = %d\n", postG.handCount[thisPlayer], preG.handCount[thisPlayer] + newCards - discarded);
	}

	// ----------- TEST 2: If pre deckCount is 0, then post deckCount should be pre discardCount -1, and discardCount =1 --------------
	// ----------- TEST 2: Else, deckCount should -1, and discardCount +1 --------------
	
	if(preG.deckCount[thisPlayer] <= 0){
		if(postG.deckCount[thisPlayer] != preG.discardCount[thisPlayer]-newCards){
			passing = 0;
			printf("currentPlayer deck count = %d, expected = %d\n", postG.deckCount[thisPlayer], preG.discardCount[thisPlayer] - newCards);
		}
		if(postG.discardCount[thisPlayer] != discarded){
			passing = 0;
			printf("currentPlayer discard count = %d, expected = %d", postG.discardCount[thisPlayer], discarded);
		}
	}		
	else {
		if(postG.deckCount[thisPlayer] != (preG.deckCount[thisPlayer]-newCards)){
			passing = 0;
			printf("currentPlayer deck count = %d, expected = %d\n", postG.deckCount[thisPlayer], preG.deckCount[thisPlayer] - newCards);
		}
		if(postG.discardCount[thisPlayer] != (preG.discardCount[thisPlayer]+discarded)){
			passing = 0;
			printf("currentPlayer discard count = %d, expected = %d\n", postG.discardCount[thisPlayer], preG.discardCount[thisPlayer]+discarded);
		}
	}

	// ----------- TEST 3: +2 actions --------------
	//printf("\nTEST 3: +2 actions\n");
	if(postG.numActions != (preG.numActions+2)){
		passing = 0;
		printf("currentPlayer number of actions = %d, expected = %d\n", postG.numActions, preG.numActions+2);	
	}
	
	// ----------- TEST 4: No state changes for other player --------------
	//printf("\nTEST 4: No state changes for other player\n");
	if(postG.handCount[thisPlayer+1] != preG.handCount[thisPlayer+1]){
		passing = 0;
		printf("other player hand count = %d, expected = %d\n", postG.handCount[thisPlayer+1], preG.handCount[thisPlayer+1]);
	}
	if(postG.deckCount[thisPlayer+1] != preG.deckCount[thisPlayer+1]){
		passing = 0;	
		printf("other player deck count = %d, expected = %d\n", postG.deckCount[thisPlayer+1], preG.deckCount[thisPlayer+1]);
	}
	if(postG.discardCount[thisPlayer+1] != preG.discardCount[thisPlayer+1]){
		passing = 0;	
		printf("other player discard count = %d, expected = %d\n", postG.discardCount[thisPlayer+1], preG.discardCount[thisPlayer+1]);
	}

	// ----------- TEST 5: No state changes to victory or kingdom cards --------------

	//printf("\nTEST 5: No state changes to victory or kingdom cards\n");

	// cycle through each card supply
	for(i = 0; i < 27; i++) {
		if(postG.supplyCount[i] != preG.supplyCount[i]){
			passing = 0;
			printf("Supply for CARD enum[%d] is %d, expected %d\n", i, postG.supplyCount[i], preG.supplyCount[i]);
		}
	}
	
	return passing;
}	


int main() {

	
	//randomize seed
	int seed = time(NULL);
	
	
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int i;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState preG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int passing = 1;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &preG);
	passing = checkVillageFnc(choice1, choice2, choice3, &preG, handpos, &bonus);
	
	
	if(passing == 1)
		printf("\nAll village tests passed!\n");
	else
		printf("\nAt least one village test failed.\n");


	return 0;
}


