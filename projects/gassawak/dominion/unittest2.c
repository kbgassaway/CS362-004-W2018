/* --------------------------------------------------------------------------
 * unittest2.c
 * Unit test for scoreFor() in dominion.c, which should return the
 * correct score of the player passed.
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
    int numPlayer = 2;
    int p;
	int score;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int passing = 1;
   

    printf ("\nTESTING scoreFor():\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	printf("\nTest score for player with 0 total hand, discard, and deck cards.\n");
	p = 0;
	//set number card counts and cards for 1st player
	G.handCount[p] = 0;                 // set the number of cards in hand
	G.discardCount[p] = 0;				// set the number of cards in discard
	G.deckCount[p] = 0;					// set the number of cards in deck
	score = scoreFor(p, &G);
	if (score == 0){
		printf("scoreFor(): PASS when player has no hand, discard, or deck cards. Score = 0.\n");
	}
	else{
		printf("scoreFor(): FAIL when player has no hand, discard, or deck cards.\n");
		printf("Score = %d, expected = 0\n", score);
		passing = 0;
	}
		
	printf("\nTest score for player with 0 cards in hand, 0 cards in discard,\n");
	printf("and 1 estate in deck.\n");
	p = 0;
	//set number card counts and cards for 1st player 
	G.handCount[p] = 0;                 // set the number of cards in hand
	G.discardCount[p] = 0;				// set the number of cards in discard
	G.deckCount[p] = 1;					// set the number of cards in deck
	G.deck[p][0] = estate;
	score = scoreFor(p, &G);
	if (score == 1){
		printf("scoreFor(): PASS when player has no hand cards, no discard cards,\n");
		printf("and only 1 estate card in deck. Score = 1.\n");
	}
	else{
		printf("scoreFor(): FAIL when player has no hand cards, no discard cards, \n");
		printf("and only 1 estate card in deck. Score = %d, expected = 1\n", score);
		passing = 0;
	}
		
	printf("\nTest score for player with 0 cards in hand, 1 estate card in discard, \n");
	printf("and 0 cards in deck.\n");
	p = 0;
	//set number card counts and cards for 1st player 
	G.handCount[p] = 0;                 // set the number of cards in hand
	G.discardCount[p] = 1;				// set the number of cards in discard
	G.deckCount[p] = 0;					// set the number of cards in deck
	G.discard[p][0] = estate;
	score = scoreFor(p, &G);
	if (score == 1){
		printf("scoreFor(): PASS when player has no hand cards, only 1 estate card in discard pile, \n");
		printf("and no deck. Score = 1.\n");
	}
	else {
		printf("scoreFor(): FAIL when player has no hand cards, only 1 estate card in discard pile, \n");
		printf("and no deck. Score = %d, expected = 1\n", score);
		passing = 0;
	}
		
	printf("\nTest score for player with 1 estate card in hand, 0 cards in discard, \n");
	printf("and 0 cards in deck.\n");
	p = 0;
	//set number card counts and cards for 1st player 
	G.handCount[p] = 1;                 // set the number of cards in hand
	G.discardCount[p] = 0;				// set the number of cards in discard
	G.deckCount[p] = 0;					// set the number of cards in deck
	G.hand[p][0] = estate;
	score = scoreFor(p, &G);
	if (score == 1){
		printf("scoreFor(): PASS when player has 1 estate card in hand, 0 cards in discard,\n");
		printf(" and 0 cards in deck. Score = 1.\n");
	}
	else {
		printf("scoreFor(): FAIL when player 1 estate card in hand, 0 cards in discard, \n");
		printf("and 0 cards in deck. Score = %d, expected = 1\n", score);
		passing = 0;
	}
		
	printf("\nTest score for player with 1 of each curse, estate, duchy, province, great_hall, \n");
	printf("and gardens in each hand, discard, and deck.\n");
	p = 0;
	//set number card counts and cards for 1st player 
	G.handCount[p] = 6;                 // set the number of cards in hand
	G.discardCount[p] = 6;				// set the number of cards in discard
	G.deckCount[p] = 6;					// set the number of cards in deck
	//set hand cards
	G.hand[p][0] = curse;
	G.hand[p][1] = estate;
	G.hand[p][2] = duchy;
	G.hand[p][3] = province;
	G.hand[p][4] = great_hall;
	G.hand[p][5] = gardens;
	//set discard cards
	G.discard[p][0] = curse;
	G.discard[p][1] = estate;
	G.discard[p][2] = duchy;
	G.discard[p][3] = province;
	G.discard[p][4] = great_hall;
	G.discard[p][5] = gardens;
	//set deck cards
	G.deck[p][0] = curse;
	G.deck[p][1] = estate;
	G.deck[p][2] = duchy;
	G.deck[p][3] = province;
	G.deck[p][4] = great_hall;
	G.deck[p][5] = gardens;
	score = scoreFor(p, &G);
	if (score == 33){
		printf("scoreFor(): PASS when player has 1 of each curse, estate, duchy, province, great_hall,\n");
		printf(" and gardens in each hand, discard, and deck. Score = 33.\n");
	}
	else {
		printf("scoreFor(): FAIL when player has 1 of each curse, estate, duchy, province, great_hall,\n");
		printf(" and gardens in each hand, discard, and deck. Score = %d, expected = 33\n", score);
		passing = 0;
	}
		
	printf("\nTest score for player with 1 of each curse, estate, duchy, province, great_hall, \n");
	printf("but no gardens in each hand, discard, and deck.\n");
	p = 0;
	//set number card counts and cards for 1st player 
	G.handCount[p] = 5;                 // set the number of cards in hand
	G.discardCount[p] = 5;				// set the number of cards in discard
	G.deckCount[p] = 5;					// set the number of cards in deck
	//set hand cards
	G.hand[p][0] = curse;
	G.hand[p][1] = estate;
	G.hand[p][2] = duchy;
	G.hand[p][3] = province;
	G.hand[p][4] = great_hall;
	//set discard cards
	G.discard[p][0] = curse;
	G.discard[p][1] = estate;
	G.discard[p][2] = duchy;
	G.discard[p][3] = province;
	G.discard[p][4] = great_hall;
	//set deck cards
	G.deck[p][0] = curse;
	G.deck[p][1] = estate;
	G.deck[p][2] = duchy;
	G.deck[p][3] = province;
	G.deck[p][4] = great_hall;
	score = scoreFor(p, &G);
	if (score == 30){
		printf("scoreFor(): PASS when player has 1 of each curse, estate, duchy, province, great_hall,\n");
		printf(" but no gardens in each hand, discard, and deck. Score = 30.\n");
	}
	else {
		printf("scoreFor(): FAIL when player has 1 of each curse, estate, duchy, province, great_hall,\n");
		printf(" but no gardens in each hand, discard, and deck. Score = %d, expected = 30\n", score);
		passing = 0;
	}

	if(passing == 1)
		printf("\nAll scoreFor() tests passed!\n");
	else
		printf("\nAt least one of the scoreFor() tests failed.\n");

    return 0;
}