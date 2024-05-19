#include "tank_T-39.h"

int main(void) {
  menu();

  return 0;
}

int menu(void) {
  INITNCURSES();
  Key *key = getStaticKey();
  inclusionOfColors();
  int gg = 1, tank = 1, reset = 2, exit = 3;
  while (*key != Quit) {
    setKey(key);
    drawPhone(10);
    drawButtonTank(gg == tank ? 9 : 8);
    drawButtonEmpty(gg == reset ? 9 : 8);
    drawButtonExit(gg == exit ? 9 : 8);
    if (*key == Play) {
      if (gg == tank) {
        game();
      } else if (gg == reset) {
        write_level(1);
      } else if (gg == exit) {
        *key = Quit;
      }
    } else if (*key == Down) {
      gg++;
      if (gg == 4) gg = 1;
    } else if (*key == Up) {
      gg--;
      if (gg == 0) gg = 3;
    }
  }

  // FREE_ALL();
  ENDNCURSES();
  free(key);

  return 0;
}

void game(void) {
  Key *key = getStaticKey();
  int field[MAX_Y][MAX_X];
  int field_for_enemy[MAX_Y][MAX_X];

  int level = read_level(), initial_y = 0, initial_x = 0;
  initField(field, level, &initial_y, &initial_x);
  initFieldForEnemy(field_for_enemy, field);
  Tank tank;
  initTank(field, &tank);
  tank.ammunitions = 3;
  tank.lives = 3;
  tank.dir = UP;

  int game = true, step = 0, max_step = 5, apple = 0,
      max_apple = checkApples(field);
  while (*key != Quit && game) {
    setKey(key);
    drawGame(field, field_for_enemy);
    drawAmminitions(tank.ammunitions);
    drawApples((double)apple / (double)max_apple * 100);
    drawLives(tank.lives);
    drawLevel(level);
    int res_turn = turn(&tank, field, field_for_enemy);
    if (res_turn) {
      if (res_turn == 1) level++;
      if (initField(field,
                    (res_turn == 1)   ? level
                    : (res_turn == 2) ? 0
                                      : -1,
                    &initial_y, &initial_x))
        break;
      initFieldForEnemy(field_for_enemy, field);
      initTank(field, &tank);
      max_apple = checkApples(field);
    }
    if (tank.ammunitions > 0)
      if (toFire(&tank, field_for_enemy)) tank.ammunitions--;
    stepFire(field, field_for_enemy);
    stepEnimy(&step, field_for_enemy, field, max_step);
    if (checkTankCollision(&tank, field, field_for_enemy, step, max_step,
                           initial_y, initial_x))
      game = false;
    apple = max_apple - checkApples(field);
    if (apple == max_apple) {
      clearField(field, field_for_enemy);
    }
    if (level == 3) max_step = 4;
    if (level == 5) max_step = 3;
    if (level == 7) max_step = 2;
    if (level == 9) max_step = 1;

    napms(40);
  }

  if (tank.lives > 0) {
    write_level(level);
  } else {
    write_level(1);
  }

  *key = Pass;
}
