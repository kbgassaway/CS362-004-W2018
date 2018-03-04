/* ---------------------------------------------------------------------------------
 * unittest4.c
 * Unit test for isGameOver() in dominion.c, which should return 1 if game
 * is over (either province pile has no cards left, or 3 supplypiles
 * are empty). Should return 0 if game is not over.
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * Source: several of the variables and initialization of the game was
 * taken from testUpdateCoins.c (given to the CS362 400 W2018 class for reference.
 * --------------------------------------------------------------------------------
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
	int gameOver;
    int k[10] = {adventurer, feast, gardens, mine, remodel
               , smithy, village, great_hall, sea_hag, treasure_map};
    struct gameState G;
	int passing = 1;
   

    printf ("\nTESTING isGameOver():\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
/*	   
	gameOver = isGameOver(&G);
	if (gameOver == 1){
		printf("\nTest isGameOver() when supplyCount for province is >0 and \n");
		printf("all other supplyCounts are >0. Game should not be over.\n");
		printf("isGameOver(): FAIL for >0 province cards and all kingdom cards are >0. Game should continue. \n");
		printf("isGameOver returned 1, expected 0\n");
		passing = 0;
	}
	

	G.supplyCount[province] = 0;   
	gameOver = isGameOver(&G);
	if (gameOver == 0){
		printf("\nTest isGameOver() when supplyCount for province is 0 and \n");
		printf("all other supplyCounts are >0. Game should be over.\n");
		printf("isGameOver(): FAIL when supplyCount for province is 0 and all kingdom cards are >0. Game should be over.\n");
		printf("isGameOver returned 0, expected 1\n");
		passing = 0;
	}
*/	

	G.supplyCount[province] = 10; 
    G.supplyCount[mine] = 0;
	G.supplyCount[treasure_map] = 0;
	G.supplyCount[sea_hag] = 0;	
	gameOver = isGameOver(&G);
	if (gameOver == 0){
		printf("\nTest isGameOver() when supplyCount for province >0, for mine is 0, \n");
		printf("for sea_hag is 0, and for treasure_map is 0. Game should be over.\n");
		printf("isGameOver(): FAIL when supplyCount for province >0, and for mine, sea_hag, and treasure_map is 0. Game should be over.\n");
		printf("isGameOver returned 0, expected 1\n");
		passing = 0;
	}
	
/*
	G.supplyCount[province] = 10; 
    G.supplyCount[mine] = 10;
	G.supplyCount[treasure_map] = 10;
	G.supplyCount[sea_hag] = 10;
    G.supplyCount[adventurer] = 0;
	G.supplyCount[feast] = 0;
	G.supplyCount[gardens] = 0;	
	gameOver = isGameOver(&G);
	if (gameOver == 0){
		printf("\nTest isGameOver() when supplyCount for province >0, for adventurer is 0, \n");
		printf("for feast is 0, and for gardens is 0. Game should be over.\n");
		printf("isGameOver(): FAIL when supplyCount for province >0, and for adventurer, feast, and gardens is 0. Game should be over.\n");
		printf("isGameOver returned 0, expected 1\n");
		passing = 0;
	}
*/

	if(passing == 1)
		printf("\nAll isGameOver() tests passed!\n");
	else
		printf("\nAt least one of the isGameOver() tests failed.\n");

    return 0;
}