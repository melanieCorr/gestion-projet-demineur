/**
 * \file game.c
 * \brief Main function
 * \author Mélanie, Yasmine, Nour, Tidiane, Massi, Ziri
 * \date 25 Octobre 2019 
*/


#include <stdio.h>
#include <stdlib.h>
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
		
		printf("initialize: \n");
		disp(gameGrid, gp.size);
		
		putNumbers(gameGrid, gp.size);
		
		printf("putNumbers\n");
		disp(gameGrid, gp.size);
		

		int gameStatus = CONTINUE;
		

		do{
			displayGrid(gameGrid, gp.size);

			printf("In the game\n");
			disp(gameGrid, gp.size);

			
			int pos = getPosClickedCell(gp.size);
			printf("Position : %d\n", pos);
			showNumbers(gameGrid, gp.size, pos);
			//gameStatus = checkStatus(gameGrid, gp.size, pos, gp.nbBombs);		


		}while(gameStatus == CONTINUE);

		lastShow(gameGrid, gp.size);
		displayGrid(gameGrid, gp.size);
		displayEndGame(gameStatus);
	
		free(gameGrid);
	}


	printf("\n\nA bientôt\n");

	return 0;
}