/* --------------------------------------------------------------------------
 * unittest3.c
 * Unit test for getWinners() in dominion.c, which should assign 1 to winners
 * in player array, and 0 to losers
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * Source: several of the variables and initialization of the game was
 * taken from testUpdateCoins.c (given to the CS362 400 W2018 class for reference.
 * --------------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
    int seed = 1000;
    int numPlayer = 4;
    int p;
//	int score;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int players[MAX_PLAYERS];
	int passing = 1;
   

    printf ("\nTESTING getWinners():\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	printf("\nTest getWinners() for 4 players, all with a score of 0, and 4th player had 1 less turn (+1).\n");
	printf("4th Player should win.\n");
	//set number card counts all 4 players to 0
	for(p = 0; p < numPlayer; p++){
	G.handCount[p] = 0;                 // set the number of cards in hand
	G.discardCount[p] = 0;				// set the number of cards in discard
	G.deckCount[p] = 0;					// set the number of cards in deck
	}
	G.whoseTurn = 2;				//set the turn to 2nd to last player
	getWinners(players, &G);
	for(p = 0; p < 3; p++){
		if(players[p] == 0) 
			printf("getWinners(): PASS Player %d did not win.\n", p+1);
		else {
			printf("getWinners(): FAIL Player %d should have lost.\n", p+1);
			passing = 0;
		}
	}
	if(players[3] == 1) 
		printf("getWinners(): PASS 4th Player did win.\n");
	else {
		printf("getWinners(): FAIL 4th Player should have won.\n");
		passing = 0;
	}
	
		
	printf("\nTest getWinners() for 4 players, all with a score of 1, and had same number of turns.\n");
	printf("All 4 players should win.\n");
	p = 0;
	//set number card counts and cards so each player has score of 1
	for(p = 0; p < numPlayer; p++){
	G.handCount[p] = 1;                 // set the number of cards in hand
	G.hand[p][0] = estate;				// set score to 1
	G.discardCount[p] = 0;				// set the number of cards in discard
	G.deckCount[p] = 0;					// set the number of cards in deck
	}
	G.whoseTurn = 3;				//set the turn to 2nd to last player
	getWinners(players, &G);
	for(p = 0; p < numPlayer; p++){
		if(players[p] == 1) 
			printf("getWinners(): PASS Player %d did win.\n", p+1);
		else {
			printf("getWinners(): FAIL Player %d should have won.\n", p+1);
			passing = 0;
		}
	}

	printf("\nTest getWinners() for 2 players, 1st player has score of 2 and should win.\n");
	printf("2nd player has a score of 1 and should lose. Both played same amount of turns.\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G); 	// initialize a new game
	G.numPlayers = 2;							//set to 2 players
	p = 0;
	//set cards for 1st player with score of 2
	G.handCount[p] = 2;                 // set the number of cards in hand
	G.hand[p][0] = estate;
	G.hand[p][1] = estate;
	G.discardCount[p] = 0;				// set the number of cards in discard
	G.deckCount[p] = 0;					// set the number of cards in deck
	
	p = 1;
	//set cards for 2nd player with score of 1
	G.handCount[p] = 1;                 // set the number of cards in hand
	G.hand[p][0] = estate;
	G.discardCount[p] = 0;				// set the number of cards in discard
	G.deckCount[p] = 0;					// set the number of cards in deck
	
	G.whoseTurn = 1;				//set the turn to 2nd player
	getWinners(players, &G);
	if(players[0] == 1) 
			printf("getWinners(): PASS 1st Player did win.\n");
		else {
			printf("getWinners(): FAIL 1st Player should have won.\n");
			passing = 0;
		}
	
	if(players[1] == 0) 
		printf("getWinners(): PASS 2nd Player did not win.\n");
	else {
		printf("getWinners(): FAIL 2nd Player should have lost.\n");
		passing = 0;
	}
	
	if(players[2] == -9999) 
		printf("getWinners(): PASS Only 2 players, so 3rd player was assigned -9999 correctly.\n");
	else {
		printf("getWinners(): FAIL Only 2 players, so 3rd player should be assigned -9999.\n");
		printf("Expected -9999, players[2] = %d\n", players[2]);
		passing = 0;
	}

	if(passing == 1)
		printf("\nAll getWinners() tests passed!\n");
	else
		printf("\nAt least one of the getWinners() tests failed.\n");

    return 0;
}