/**
 * \file helper.h
 * \brief prototypes of functions
 * \author Mélanie, Yasmine, Nour, Tidiane, Massi, Ziri
 * \date 25 Octobre 2019 
*/

#define NB_NEIGHBOURS 8
#define BOMB -11
#define EMPTY -10
#define GAME_OVER 0


int menu();
int * initialize(int size, int nbBombs);
void putNumbers(int *grid, int size);
int showNumbers(int *grid, int size);
void displayGrid(int *grid, int size);


