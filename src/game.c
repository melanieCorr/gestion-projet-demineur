/**
 * \file game.c
 * \brief Main function
 * \author Mélanie, Yasmine, Nour, Tidiane, Massi, Ziri
 * \date 25 Octobre 2019 
*/


#include <stdio.h>
#include "../include/helper.h"

/**
 * \fn int main(void)
 * \brief Main function of the game
 * 
 * \return 0 - normal program termination 
*/
int main(void){
	gridParam gp = menu();
	if(gp.size != -1){
		int *gameGrid = initialize(gp.size, gp.nbBombs);
		int gameStatus = CONTINUE;
		do{
			displayGrid(gameGrid, gp.size);
			int pos = getPosClickedCell();
						


		}while(gameStatus == CONTINUE);

	}

	printf("\n\nA bientôt\n");

	return 0;
}