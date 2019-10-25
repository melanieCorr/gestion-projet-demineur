

#define NB_NEIGHBOURS 8
#define BOMB -11
#define EMPTY -10
#define GAME_OVER 0
#define CONTINUE 200
#define WIN 100


int menu();
int * initialize(int size, int nbBombs);
void putNumbers(int *grid, int size);
int showNumbers(int *grid, int size);
void displayGrid(int *grid, int size);


