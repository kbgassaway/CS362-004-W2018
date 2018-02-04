/* -----------------------------------------------------------------------
 * unittest1.c
 * Unit test for getCost() in dominion.c, which should return the
 * correct cost of the card passed.
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main() {
    
	printf("\nTESTING getCost():\n");
	int i;
	int passing = 1;
    
    for (i = -1; i < 28; i++)
    {
		int cost = getCost(i);
		switch(i)
		{
			case -1:
				if (cost == -1)
					printf("\ngetCost(): PASS when test cardNumber doesn't exist\n");
				else {
					printf("\ngetCost(): FAIL when test cardNumber doesn't exist\n");
					passing = 0;
				}
				break;
			
			case 0:
				if (cost == 0)
					printf("getCost(): PASS when test cardNumber is Curse\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Curse\n");
					passing = 0;
				}
				break;
			
			case 1:
				if (cost == 2)
					printf("getCost(): PASS when test cardNumber is Estate\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Estate\n");
					passing = 0;
				}
				break;
				
			case 2:
				if (cost == 5)
					printf("getCost(): PASS when test cardNumber is Duchy\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Duchy\n");
					passing = 0;
				}
				break;
				
			case 3:
				if (cost == 8)
					printf("getCost(): PASS when test cardNumber is Province\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Province\n");
					passing = 0;
				}
				break;
				
			case 4:
				if (cost == 0)
					printf("getCost(): PASS when test cardNumber is Copper\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Copper\n");
					passing = 0;
				}
				break;
				
			case 5:
				if (cost == 3)
					printf("getCost(): PASS when test cardNumber is Silver\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Silver\n");
					passing = 0;
				}
				break;
				
			case 6:
				if (cost == 6)
					printf("getCost(): PASS when test cardNumber is Gold\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Gold\n");
					passing = 0;
				}
				break;
				
			case 7:
				if (cost == 6)
					printf("getCost(): PASS when test cardNumber is Adventurer\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Adventurer\n");
					passing = 0;
				}
				break;
				
			case 8:
				if (cost == 5)
					printf("getCost(): PASS when test cardNumber is Council Room\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Council Room\n");
					passing = 0;
				}
				break;
			
			case 9:
				if (cost == 4)
					printf("getCost(): PASS when test cardNumber is Feast\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Feast\n");
					passing = 0;
				}
				break;
			
			case 10:
				if (cost == 4)
					printf("getCost(): PASS when test cardNumber is Gardens\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Gardens\n");
					passing = 0;
				}
				break;
			
			case 11:
				if (cost == 5)
					printf("getCost(): PASS when test cardNumber is Mine\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Mine\n");
					passing = 0;
				}
				break;
		
			case 12:
				if (cost == 4)
					printf("getCost(): PASS when test cardNumber is Remodel\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Remodel\n");
					passing = 0;
				}
				break;
				
			case 13:
				if (cost == 4)
					printf("getCost(): PASS when test cardNumber is Smithy\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Smithy\n");
					passing = 0;
				}
				break;
				
			case 14:
				if (cost == 3)
					printf("getCost(): PASS when test cardNumber is Village\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Village\n");
					passing = 0;
				}
				break;
				
			case 15:
				if (cost == 4)
					printf("getCost(): PASS when test cardNumber is Baron\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Baron\n");
					passing = 0;
				}
				break;
				
			case 16:
				if (cost == 3)
					printf("getCost(): PASS when test cardNumber is Great Hall\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Great Hall\n");
					passing = 0;
				}
				break;
				
			case 17:
				if (cost == 5)
					printf("getCost(): PASS when test cardNumber is Minion\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Minion\n");
					passing = 0;
				}
				break;
				
			case 18:
				if (cost == 3)
					printf("getCost(): PASS when test cardNumber is Steward\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Steward\n");
					passing = 0;
				}
				break;
				
			case 19:
				if (cost == 5)
					printf("getCost(): PASS when test cardNumber is Tribute\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Tribute\n");
					passing = 0;
				}
				break;
			
			case 20:
				if (cost == 3)
					printf("getCost(): PASS when test cardNumber is Ambassador\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Ambassador\n");
					passing = 0;
				}
				break;
			
			case 21:
				if (cost == 4)
					printf("getCost(): PASS when test cardNumber is Cutpurse\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Cutpurse\n");
					passing = 0;
				}
				break;
			
			case 22:
				if (cost == 2)
					printf("getCost(): PASS when test cardNumber is Embargo\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Embargo\n");
					passing = 0;
				}
				break;
				
			case 23:
				if (cost == 5)
					printf("getCost(): PASS when test cardNumber is Outpost\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Outpost\n");
					passing = 0;
				}
				break;
				
			case 24:
				if (cost == 4)
					printf("getCost(): PASS when test cardNumber is Salvager\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Salvager\n");
					passing = 0;
				}
				break;
				
			case 25:
				if (cost == 4)
					printf("getCost(): PASS when test cardNumber is Sea Hag\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Sea Hag\n");
					passing = 0;
				}
				break;
				
			case 26:
				if (cost == 4)
					printf("getCost(): PASS when test cardNumber is Treasure Map\n");
				else {
					printf("getCost(): FAIL when test cardNumber is Treasure Map\n");
					passing = 0;
				}
				break;
				
			case 27:
				if (cost == -1)
					printf("getCost(): PASS when test cardNumber doesn't exist\n");
				else {
					printf("getCost(): FAIL when test cardNumber doesn't exist\n");
					passing = 0;
				}
				break;
				
		}
	}


	if(passing == 1)
		printf("\nAll getCost() tests passed!\n");
	else
		printf("\nAt least one getCost() test failed.\n");

    return 0;
}