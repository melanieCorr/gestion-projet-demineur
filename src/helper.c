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
		grid[i] = -10;

	/* Pose des mines à des positions aléatoires ( Une mine a la valeur -11 )*/ 
	srand((unsigned)time(NULL)); 
	for (int i = 0; i < nbBombs; i++)
		grid[rand() % (size*size)] = -11;
	
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
			printf("|");
			if(grid[row * size + col] < 0 || grid[row * size + col] == -EMPTY){
                printf("   ");
            }
			else if(grid[row * size + col] == BOMB){
                printf(" B ");
            }
            else{
                printf("%d ", grid[row * size + col]);
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
	for(int i = 0; i < size; ++i, nbBombs = 0){
		if(grid[i] != BOMB){
			for(int neigh = 0; neigh < NB_NEIGHBOURS; ++neigh){
				nbBombs += (grid[i + neighbours[neigh]] == BOMB )? 1 : 0;
			}
		}
		grid[i] = (nbBombs > 0) ? nbBombs : EMPTY; 	
	}
}


