/**
 * \file helper.c
 * \brief Game engine functions
 * \author Mélanie, Yasmine, Nour, Tidiane, Massi, Ziri
 * \date 25 Octobre 2019 
*/

#include <stdio.h>
#include <time.h>
#include "../include/helper.h"

/**
 * \fn int *initialize(int size, int nbBombs)
 * \brief Function to initialize the grid
 * 
 * \param size Size of the grid
 * \param nbBombs number of mines to place in the grid
 * \return return the grid
*/
int *initialize(int size, int nbBombs) {
	int * grid = malloc(size * size * sizeof(int));
	
	/* Initialisation de toutes les cases à une valeur neutre (-10) */
	for (int i = 0; i < size*size; i++)
		grid[i] = EMPTY;

	/* Pose des mines à des positions aléatoires ( Une mine a la valeur -11 )*/ 
	srand((unsigned)time(NULL)); 
	for (int i = 0; i < nbBombs; i++)
		grid[rand() % (size*size)] = BOMB;
	
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
        	printf("%d   ", i + 1);
		else	
			printf("%d  ", i + 1);
			
	}
	printf("\n");

  // Display grid
	for(int row = 0; row < size; ++row){
		makeBorders(size);
		if(row < 9)	
			printf("%d  ", row + 1);
		else
			printf("%d ", row + 1);
		for(int col = 0; col < size; ++col){
			int val = grid[row * size + col];
			printf("|");
			if(val < 0 /*|| val == -EMPTY*/){
                printf("   ");
            }
			else if(val == BOMB){
                printf(" B ");
            }
            else{
            	int dispVal = (val == EMPTY) ? 0 : val;
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
	int neighbours[] = {-size - 1, -size, -size + 1,  -1, 1,  size - 1,  size, size + 1};
	int nbBombs = 0;
	int gridSize = size * size;
	for(int i = 0; i < gridSize; ++i, nbBombs = 0){
		if(grid[i] != BOMB){
			for(int neigh = 0; neigh < NB_NEIGHBOURS; ++neigh){
				int pos = i + neighbours[neigh];
				int r = pos / size, c = pos % size;
				if(r >= 0 && r < size && c >= 0 && c < size)
					nbBombs += (grid[pos] == BOMB )? 1 : 0;	
			}
		}
		grid[i] = (nbBombs > 0) ? nbBombs : EMPTY; 	
	}
}

/**
 * \fn void rules(int size)
 * \brief show the rules
 * 
 
 * \param size Size of the grid 
*/
void rules(int size){
	printf( "\t\tRègles du jeu\n\n"
			"Le but du jeu est de repérer toutes les mines cachées sous les tuiles d'une grille carrée.\n"
			"Vous aurez besoin de réflexion et d'un peu de chance pour les trouver toutes sans provoquer d'explosion.\n\n"
	);
}

/**
 * \fn int getPosClickedCell()
 * \brief get the position of click cell
 * 
 * \return return the position of click
*/
int getPosClickedCell(){
	int r, c;
	do{
	
		printf("Veuillez taper le numéro de ligne\n");
		int val = scanf("%d", r);
	
	}while(val != 1);

	
	do{
	
		printf("Veuillez taper le numéro de colonne\n");
		int val = scanf("%d", c);
	
	}while(val != 1);	

	return r * size + c;
}
/**
 * \fn gridParam getGridParam()
 * \brief get the param of the grid
 * 
 * \return return param of the grid
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
 * \fn gridParam menu()
 * \brief show the menu game
 * 
 * \return return param of the grid
*/
gridParam menu(){
	int choice;

	printf( "\t\t\t*******************\n\t\t\tDémineur\n\t\t\t*******************\n\n\n"
			"Veuillez taper votre choix\n\n"
			"1)- Jouer\n"
			"2)- Règles du jeu\n";
			"3)- Quitter\n"
	);

	do{

		int val = scanf("%d", &choice);

	}while(val != 1 && choice < 1 && choice > 3);

	gridParam gp;
	gp.size = -1; 
	switch(choice){
		case 1: gp = getGridParam();
				break;
		case 2: rules();
				break;
		default:
			break;	
	}	

	return gp;
}
/**
 * \fn void showNumbers(int  *grid, int size,int pos)
 * \brief on click uncovers the cell and adjacent cells (if any) if there is no bomb on said cell, also displays the numbers in each cell of its adjacent bombs
 *
 * \param grid Grid of the game
 * \param size Size of the grid
 * \param pos Position of the grid
*/
void showNumbers(int  *grid, int size,int pos){
	int neighbours[] = {-size - 1, -size, -size + 1,  -1, 1,  size - 1,  size, size + 1};
	int curCell = grid[pos];
    cuCell *= -1;
	if (curCell > 0 || curCell < EMPTY)
		return;

	for(int i = 0; i < NB_NEIGHBOURS; ++i){
		int r = (pos + neighbours[i]) / size;
		int c = (pos + neighbours[i]) % size;
		i(r >=0 && r < size && c  >= 0 && c < size)
		showNumbers(grid, size, r, c);  
	}
}


 /* \fn int parcours(int *grid, int size, int nb_Bomb)
 * \brief ****
 *
 * \param grid Grid of the game
 * \param size Size of the grid
 * \param nb_bomb number of mines
 * \return ***
*/
int parcours(int *grid, int size, int nb_Bomb){


	int	s= size*size;
	int cmpt=0;
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
 * \brief ****
 *
 * \param grid Grid of the game
 * \param size Size of the grid
 * \param pos Position of the grid
 * \param nb_bomb number of mines
 * \return ***
*/
int checkStatus(int *grid, int size, int pos, int nb_Bomb){


	int curCell = grid[pos];
	
	if (curCell == BOMB)
		return GAME_OVER;

	if(curCell > EMPTY){
		grid[pos] *= -1;
		if(parcours(grid, size,nb_Bomb) == CONTINUE)
			return CONTINUE;
		else
			return WIN;
	}
	else{
		showNumbers(grid, size, pos);
		if(parcours(grid, size,nb_Bomb) == CONTINUE)
			return CONTINUE;
		else
			return WIN;
	}
}
/**
 * \fn void lastShow(int *grid, int size)
 * \brief ****
 *
 * \param grid Grid of the game
 * \param size Size of the grid
*/
void lastShow(int *grid, int size){

	int s = size * size;

	for(int i = 0; i < s; ++i){
		if(grid[i]<0)
			grid[i] * = -1;
	}
}
