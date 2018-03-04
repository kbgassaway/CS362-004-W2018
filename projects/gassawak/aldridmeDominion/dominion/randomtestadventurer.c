/* -----------------------------------------------------------------------
 * randomtestadventurer.c
 * Unit test for adventurerFnc() called in cardEffect() in dominion.c, which 
 * should add 2 treasure cards to the current Player's hand from their deck and/or 
 * discard pile. No other state changes should be made to other players
 * or to the victory or kingdom cards. 
 * Source: this unit test was modified from cardtest4.c 
 * (given to the CS362 400 W2018 class for reference).
 *
 * Include the following lines in your makefile:
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "adventurer"

int checkAdventurerFnc(int choice1, int choice2, int choice3, struct gameState *preG, int thisPlayer, int handpos, int *bonus){
	
	struct gameState postG;
	int newCards = 2;
    int discarded = 1;
	int passing = 1;
	int i;

	// copy the pregame state to a test case
	memcpy(&postG, preG, sizeof(struct gameState));
	//postgame state calls village card
	cardEffect(adventurer, choice1, choice2, choice3, &postG, handpos, bonus);

	// ----------- TEST 1: 2 treasure cards to hand, if 2 are in deck or discard --------------
	//printf("\nTEST 1: add up to 2 treasure cards to hand from deck + discard\n");
	
	if((postG.handCount[thisPlayer] > (preG->handCount[thisPlayer]+newCards-discarded)) || (postG.handCount[thisPlayer] < preG->handCount[thisPlayer])){
		passing = 0;
		printf("currentPlayer hand count = %d, expected = %d\n", postG.handCount[thisPlayer], preG->handCount[thisPlayer] + newCards - discarded);
	}
	
	//count number of treasure cards in hand before adventurer is played
	int cardInHand;
	int pretreasureCount = 0;
	for(i = 0; i < preG->handCount[thisPlayer]; i++){
		cardInHand =  preG->hand[thisPlayer][i];
		if (cardInHand == copper || cardInHand == silver || cardInHand == gold)
		pretreasureCount++;
	}
	
	//count number of treasure cards in hand after adventurer is played
	int posttreasureCount = 0;
	for(i = 0; i < postG.handCount[thisPlayer]; i++){
		cardInHand =  postG.hand[thisPlayer][i];
		if (cardInHand == copper || cardInHand == silver || cardInHand == gold)
		posttreasureCount++;
	}
	
	if((posttreasureCount > (pretreasureCount+2)) || (posttreasureCount < pretreasureCount)){
		passing = 0;
		printf("currentPlayer treasure cards in hand = %d, expected = %d\n", posttreasureCount, pretreasureCount+2);
	}
	
	// ----------- TEST 2: deck + discard should decrease 1, discardCount should be at least 1 --------------
	//printf("\nTEST 2: deck + discard should decrease 1, \n");
	//printf("discardCount should be at least 1\n");
	
	if((postG.deckCount[thisPlayer] + postG.discardCount[thisPlayer]) != (preG->deckCount[thisPlayer] + preG->discardCount[thisPlayer] -1)){
		passing = 0;
		printf("currentPlayer deck + discard count = %d, expected = %d\n", (postG.deckCount[thisPlayer] + postG.discardCount[thisPlayer]), (preG->deckCount[thisPlayer] + preG->discardCount[thisPlayer] -1));
	}
	if(postG.discardCount[thisPlayer] < discarded){
		passing = 0;
		printf("currentPlayer discard count = %d, expected = %d\n", postG.discardCount[thisPlayer], discarded);
	}
	
	// ----------- TEST 3: No state changes for other player --------------
	//printf("\nTEST 3: No state changes for other player\n");
	
	for(i=0; i < postG.numPlayers; i++){
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

	// ----------- TEST 4: No state changes to victory or kingdom cards --------------
	//printf("\nTEST 4: No state changes to victory or kingdom cards\n");

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
	
	for(i = 0; i < 100; i++) {
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
		
		printf("\ncall %d to checkAdventurerFnc\n", i+1);
		passing = checkAdventurerFnc(choice1, choice2, choice3, &G, thisPlayer, handpos, &bonus);
	}
	
	if(passing == 1)
		printf("\nAll adventurer tests passed!\n");
	else
		printf("\nAt least one adventurer test failed.\n");


	return 0;
}


