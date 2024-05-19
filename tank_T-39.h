#ifndef TANK_T39_H
#define TANK_T39_H

/**
 * author: laraeter
 * date: 2021-04-08
 * telegram: @Shahvali_Magomedov
 */

#include <ncurses.h>
#include <stdlib.h>

#define MAX_X 27
#define MAX_Y 25

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define ENIMYGOINGUP 'u'
#define ENIMYGOINGDOWN 'd'
#define ENIMYGOINGLEFT '<'
#define ENIMYGOINGRIGHT '>'

#define FIREGOINGUP 'U'
#define FIREGOINGDOWN 'D'
#define FIREGOINGLEFT 'L'
#define FIREGOINGRIGHT 'R'

#define WALL '/'
#define WEAKWALL '='
#define EMPTY ' '
#define PLAYER '@'
#define FOOD '1'
#define LIFE '+'
#define DOOR '*'
#define DOORBOSS '!'
#define MONEY '7'
#define AMMUNITION '2'

#define INITNCURSES()    \
  initscr();             \
  cbreak();              \
  noecho();              \
  keypad(stdscr, TRUE);  \
  nodelay(stdscr, TRUE); \
  curs_set(0);

#define ENDNCURSES() endwin();

typedef struct {
  int x;
  int y;
  int dir;
  int lives;
  int keel;
  int ammunitions;
} Tank;

typedef struct {
  int x;
  int y;
  int dir;
} typeFire;

typedef enum { Up, Down, Left, Right, Fire, Quit, Pause, Play, Pass } Key;

int menu(void);
void game(void);

int stepEnimy(int *step, int field_for_enemy[MAX_Y][MAX_X],
              int field[MAX_Y][MAX_X], int max_step);
int stepFire(int field[MAX_Y][MAX_X], int field_for_enemy[MAX_Y][MAX_X]);
int toFire(Tank *tank, int field_for_enemy[MAX_Y][MAX_X]);
int turn(Tank *tank, int field[MAX_Y][MAX_X],
         int field_for_enemy[MAX_Y][MAX_X]);
bool checkTankCollision(Tank *tank, int field[MAX_Y][MAX_X],
                        int field_for_enemy[MAX_Y][MAX_X], int step,
                        int max_step, int initial_y, int initial_x);
void clearField(int field[MAX_Y][MAX_X], int field_for_enemy[MAX_Y][MAX_X]);
int checkApples(int field[MAX_Y][MAX_X]);
int read_level(void);
void write_level(int score);
int initTank(int field[MAX_Y][MAX_X], Tank *tank);
int initField(int field[MAX_Y][MAX_X], int level, int *initial_y,
              int *initial_x);
int initFieldForEnemy(int field_for_enemy[MAX_Y][MAX_X],
                      int field[MAX_Y][MAX_X]);
Key *getStaticKey(void);
void setKey(Key *key);

void inclusionOfColors(void);
void drawPhone(int color);
void drawButtonTank(int color);
void drawButtonEmpty(int color);
void drawButtonExit(int color);
void drawGame(int field[MAX_Y][MAX_X], int field_for_enemy[MAX_Y][MAX_X]);
void drawAmminitions(int ammunitions);
void drawApples(int apples);
void drawLives(int lives);
void drawLevel(int level);

int **createMatrix(int rows, int cols);

#endif
