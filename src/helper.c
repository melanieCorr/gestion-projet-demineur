/**
 * \file helper.c
 * \brief Game engine functions
 * \author Mélanie, Yasmine, Nour, Tidiane, Massi, Ziri
 * \date 25 Octobre 2019 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../include/helper.h"



/**
 * \fn int existsAlready(int *grid, int size, int val)
 * \brief Check the existence of a value in an array
 * 
 * \param grid the grid
 * \param size Size of the grid
 * \param nbBombs number of bombs to put in the grid
 * \return returns 1 if value exists in grid, 0 otherwise
*/
int existsAlready(int *grid, int size, int val){
	for(int i = 0; i < size; ++i)
		if(grid[i] == val)
			return 1;
	return 0;
}

/**
 * \fn int *initialize(int size, int nbBombs)
 * \brief Function to initialize the grid
 * 
 * \param size Size of the grid
 *  \param nbBombs number of bombs to put in the grid
 * \return returns a grid
*/
int *initialize(int size, int nbBombs) {
	int * grid = malloc(size * size * sizeof(int));
	assert(grid);
	int *bombsPositions = calloc(nbBombs, nbBombs * sizeof *bombsPositions);
	assert(bombsPositions);

	int gridSize = size * size;
	/* Initialisation de toutes les cases à une valeur neutre (-10) */
	for (int i = 0; i < gridSize; i++)
		grid[i] = EMPTY;

	/* Pose des mines à des positions aléatoires ( Une mine a la valeur -11 )*/ 
	srand((unsigned)time(NULL)); 
	for (int i = 0; i < nbBombs; i++){
		int pos;
		do{

			pos = rand() % gridSize;
	
		}while(existsAlready(bombsPositions, nbBombs, pos));
		bombsPositions[i] = pos;
		grid[pos] = BOMB;
	}
	
	return grid;
}


/**
 * \fn void makeBorders(int size)
 * \brief Function to create the borders of any grid
 * 
 * \param size Size of the grid
*/
void makeBorders(int size){
    printf("   ");
    for(int i = 0; i < size; i++){
        printf("____");
    }
    printf("\n");
}


/**
 * \fn void displayGrid(int *grid, int size)
 * \brief Grid display
 * 
 * \param grid Grid of the game
 * \param size Size of the grid 
*/
void displayGrid(int *grid, int size){
    // Display columns numbers
    printf("\n     ");     
	for(int i = 0; i < size; ++i){
		if(i < 8)
        	printf("%d   ", i);
		else	
			printf("%d  ", i);
			
	}
	printf("\n");

  // Display grid
	for(int row = 0; row < size; ++row){
		makeBorders(size);
		if(row < 9)	
			printf("%d  ", row);
		else
			printf("%d ", row);
		for(int col = 0; col < size; ++col){
			int val = grid[row * size + col];
			printf("|");
			if(val < 0 /*|| val == -EMPTY*/){
                printf("   ");
            }
			else if(val == -BOMB){
                printf("B  ");
            }
            else{
            	int dispVal = (val == -EMPTY) ? 0 : val;
            	if(dispVal < 10)
                	printf("%d  ", dispVal);
            	else
            		printf("%d ", dispVal);
            }	
		}
		printf("|\n");
	}
	makeBorders(size);
	printf("\n");	
}


/**
 * \fn putNumbers(int *grid, int size)
 * \brief Number of mines in the surrounding areas
 * 
 * \param grid Grid of the game
 * \param size Size of the grid
*/
void putNumbers(int *grid, int size){
	int neighboursRow[] = {-1, -1, -1,  0, 0,  1, 1, 1};
	int neighboursCol[] = {-1, 0, 1,   -1, 1,  -1, 0, 1};
	int nbBombs = 0;
	int gridSize = size * size;
	for(int i = 0; i < gridSize; ++i, nbBombs = 0){
		if(grid[i] != BOMB){
			for(int neigh = 0; neigh < NB_NEIGHBOURS; ++neigh){
				int r = i / size; 
				int c = i % size;
				
				int rNeigh = r + neighboursRow[neigh];
				int cNeigh = c + neighboursCol[neigh];

				if(rNeigh >= 0 && rNeigh < size && cNeigh >= 0 && cNeigh < size)
					nbBombs += (grid[rNeigh * size + cNeigh] == BOMB )? 1 : 0;	
			}
			grid[i] = (nbBombs > 0) ? -nbBombs : EMPTY; 	
		}
		
	}
}




/**
 * \fn void showNumbers(int  *grid, int size,int pos)
 * \brief on click uncovers the cell and adjacent cells (if any) if there is no bomb on said cell, also displays the numbers in each cell of its adjacent bombs
 *
 * \param grid Grid of the game
 * \param size Size of the grid
 * \param pos Position of the grid
*/
void showNumbers(int  *grid, int size, int pos){
	
	int neighboursRow[] = {-1, -1, -1,  0, 0,  1, 1, 1};
	int neighboursCol[] = {-1, 0, 1,   -1, 1,  -1, 0, 1};

	int curCell = grid[pos];    

	if (curCell > 0 ||curCell == BOMB)
		return;

    if (curCell > EMPTY){
    	grid[pos] *= -1;
    	return;
    }


	grid[pos] *= -1;

	for(int i = 0; i < NB_NEIGHBOURS; ++i){
		int r = pos / size; 
		int c = pos % size;
		
		int rNeigh = r + neighboursRow[i];
		int cNeigh = c + neighboursCol[i];

		if(rNeigh >= 0 && rNeigh < size && cNeigh >= 0 && cNeigh < size)
			showNumbers(grid, size, rNeigh * size + cNeigh);  
	}
}



 /* \fn int parcours(int *grid, int size, int nb_Bomb)
 * \brief Checks the grid to see if all non-bomb cells have been uncovered and returns WIN if so, otherwise the game continues
 *
 * \param grid Grid of the game
 * \param size Size of the grid
 * \param nb_bomb number of mines
 * \return WIN if all the grid was uncovered without touching any bombs, CONTINUE otherwise
*/

int parcours(int * grid, int size, int nb_Bomb){

	int	s= size*size;
	int cmpt = 0;
	for(int i = 0; i < s; ++i){
		if(grid[i]  < 0)
			cmpt++;
	}
	if(cmpt == nb_Bomb)
		return WIN;
	return CONTINUE; 	
}



/**
 * \fn int checkStatus(int *grid, int size, int pos, int nb_Bomb)
 * \brief Checks the status of currently clicked cell to see if it's a bomb or a cell the number of adjecent bombs (if any, otherwise an empty cell) 
 *
 * \param grid Grid of the game
 * \param size Size of the grid
 * \param pos Position of the grid
 * \param nb_bomb number of mines
 * \return WIN if grid has been won according to the "parcours" function, CONTINUE if not
*/

int checkStatus(int *grid, int size, int pos, int nb_Bomb){


	int curCell = grid[pos];
	
	if (curCell == BOMB)
		return GAME_OVER;

	showNumbers(grid, size, pos);
	return parcours(grid, size, nb_Bomb);

}


/**
 * \fn void lastShow(int *grid, int size)
 * \brief Shows the grid's final status (either won or lost)
 *
 * \param grid Grid of the game
 * \param size Size of the grid
*/
void lastShow(int *grid, int size){

	int s = size * size;

	for(int i = 0; i < s; ++i){
		if(grid[i] < 0)
			grid[i] *= -1;
	}
}


/**
 * \fn void displayEndGame(int size)
 * \brief Shows a final message whether the user won or lost
 *
 * \param size Size of the grid
*/
void displayEndGame(int status){
	switch(status){
		case WIN:
			printf("Bravo!!!\nVous avez trouvé toutes les mines dissimulées\n");
			break;

		default:
			printf("BOUM !!!\nVous venez de toucher une mine");
			break;	
	}
}


/**
 * \fn void rules(int size)
 * \brief show the rules
*/
void rules(){
	printf( "\t\tRègles du jeu\n\n"
			"Le but du jeu est de repérer toutes les mines cachées sous les tuiles d'une grille carrée.\n"
			"Vous aurez besoin de réflexion et d'un peu de chance pour les trouver toutes sans provoquer d'explosion.\n\n"
	);
}


/**
 * \fn int getPosClickedCell()
 * \brief get the position of chosen cell
 * 
 * \return returns the position of the chosen cell
*/
int getPosClickedCell(int size){
	int r, c, val;
	do{
	
		printf("Veuillez taper le numéro de ligne\n");
		val = scanf("%d", &r);
	
	}while(val != 1 && r < 0 && r >= size);

	
	do{
	
		printf("Veuillez taper le numéro de colonne\n");
		val = scanf("%d", &c);
	
	}while(val != 1 && c < 0 && c >= size);	

	return r * size + c;
}


/**
 * \fn gridParam getGridParam()
 * \brief get the param of the grid
 * 
 * \return returns a structure that contains the size and the number of bombs of the grid
*/
gridParam getGridParam(){
	gridParam gp;
	int val;

	do{
		printf("Veuillez saisir la taille de votre grille (ex: 8 ==> grille de 8*8)\n");
		val = scanf("%d", &gp.size);
	}while(val != 1);

	printf("A présent\n");
	
	do{
		printf("Veuillez entrer le nombre de mines souhaité\n");
		val = scanf("%d", &gp.nbBombs);
	}while(val != 1);

	return gp;
} 


/**
 * \fn int displayGameMenu()
 * \brief displays the game's menu
 * 
 * \return returns the user's choice whether playing, or read rules or quit the game
*/
int displayGameMenu(){

	int choice, val;

	do{
		printf(	"Veuillez taper votre choix\n\n"
				"1)- Jouer\n"
				"2)- Règles du jeu\n"
				"3)- Quitter\n\n\n"
		);
		val = scanf("%d", &choice);

	}while(val != 1 && choice < 1 && choice > 3);

	return choice;
}


/**
 * \fn gridParam menu()
 * \brief show the menu game
 * 
 * \return return param of the grid
*/
gridParam menu(){
	int choice;

	printf( "\t\t\t**************************\n\t\t\t\tDÉMINEUR\n\t\t\t**************************\n\n\n");
	
	gridParam gp;
	gp.size = -1; 

	do{
		choice = displayGameMenu();
		switch(choice){
			case 1: gp = getGridParam();
					break;
			case 2: rules();
					break;
			default:
				break;	
		}
	}while(choice == 2);

	return gp;
}



