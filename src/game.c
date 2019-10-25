#include <stdio.h>
#include "helper.h"




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