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
#define CONTINUE 200
#define WIN 100


typedef struct gridParam{
	int size, nbBombs;
} gridParam;

gridParam menu();
int * initialize(int size, int nbBombs);
void putNumbers(int *grid, int size);
void showNumbers(int  *grid, int size, int pos);
void displayGrid(int *grid, int size);
int getPosClickedCell(int size);
void lastShow(int *grid, int size);
void displayGame(int status);
int checkStatus(int *grid, int size, int pos, int nb_Bomb);
void displayEndGame(int status);

// Debug
void disp(int *grid, int size);
