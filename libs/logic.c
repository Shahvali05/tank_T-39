#include "../tank_T-39.h"

void moveEnemy(int i, int j, int next_i, int next_j,
               int field_for_enemy[MAX_Y][MAX_X], int field[MAX_Y][MAX_X],
               int direction, int reverse_direction) {
  if (next_i >= 0 && next_i < MAX_Y && next_j >= 0 && next_j < MAX_X &&
      (field[next_i][next_j] == EMPTY || field[next_i][next_j] == '@' ||
       field[next_i][next_j] == FOOD)) {
    field_for_enemy[i][j] = ' ';
    if (field_for_enemy[next_i][next_j] == EMPTY)
      field_for_enemy[next_i][next_j] = direction;
    else if (field_for_enemy[next_i][next_j] == FIREGOINGUP ||
             field_for_enemy[next_i][next_j] == FIREGOINGDOWN ||
             field_for_enemy[next_i][next_j] == FIREGOINGLEFT ||
             field_for_enemy[next_i][next_j] == FIREGOINGRIGHT)
      field_for_enemy[next_i][next_j] = EMPTY;
    else
      field_for_enemy[i][j] = reverse_direction;
  } else {
    field_for_enemy[i][j] = reverse_direction;
  }
}

int stepEnimy(int *step, int field_for_enemy[MAX_Y][MAX_X],
              int field[MAX_Y][MAX_X], int max_step) {
  if (*step >= max_step) {
    *step = 0;
    for (int i = 0; i < MAX_Y; i++) {
      for (int j = 0; j < MAX_X; j++) {
        if (field_for_enemy[i][j] == ENIMYGOINGUP) {
          int next_i = i - 1;
          moveEnemy(i, j, next_i, j, field_for_enemy, field, ENIMYGOINGUP,
                    ENIMYGOINGDOWN);
        } else if (field_for_enemy[i][j] == ENIMYGOINGDOWN) {
          int next_i = i + 1;
          moveEnemy(i, j, next_i, j, field_for_enemy, field, ENIMYGOINGDOWN,
                    ENIMYGOINGUP);
          i++;
        } else if (field_for_enemy[i][j] == ENIMYGOINGLEFT) {
          int next_j = j - 1;
          moveEnemy(i, j, i, next_j, field_for_enemy, field, ENIMYGOINGLEFT,
                    ENIMYGOINGRIGHT);
        } else if (field_for_enemy[i][j] == ENIMYGOINGRIGHT) {
          int next_j = j + 1;
          moveEnemy(i, j, i, next_j, field_for_enemy, field, ENIMYGOINGRIGHT,
                    ENIMYGOINGLEFT);
          j++;
        }
      }
    }
  } else {
    (*step)++;
  }

  return 0;
}

void moveFire(int pos1, int pos2, int max1, int max2, int dir1, int dir2,
              int field[MAX_Y][MAX_X], int field_for_enemy[MAX_Y][MAX_X],
              int fire_direction) {
  int next_pos1 = pos1 + dir1;
  int next_pos2 = pos2 + dir2;

  if (next_pos1 >= 0 && next_pos1 < max1 && next_pos2 >= 0 &&
      next_pos2 < max2 &&
      (field[next_pos1][next_pos2] == ' ' ||
       field[next_pos1][next_pos2] == FOOD ||
       field[next_pos1][next_pos2] == WEAKWALL)) {
    field_for_enemy[pos1][pos2] = ' ';
    if (field_for_enemy[next_pos1][next_pos2] == ENIMYGOINGUP ||
        field_for_enemy[next_pos1][next_pos2] == ENIMYGOINGDOWN ||
        field_for_enemy[next_pos1][next_pos2] == ENIMYGOINGLEFT ||
        field_for_enemy[next_pos1][next_pos2] == ENIMYGOINGRIGHT) {
      field_for_enemy[next_pos1][next_pos2] = ' ';
    } else if (field[next_pos1][next_pos2] == WEAKWALL) {
      field[next_pos1][next_pos2] = EMPTY;
    } else {
      field_for_enemy[next_pos1][next_pos2] = fire_direction;
    }
  } else {
    field_for_enemy[pos1][pos2] = ' ';
  }
}

int stepFire(int field[MAX_Y][MAX_X], int field_for_enemy[MAX_Y][MAX_X]) {
  for (int i = 0; i < MAX_Y; i++) {
    for (int j = 0; j < MAX_X; j++) {
      switch (field_for_enemy[i][j]) {
        case FIREGOINGUP:
          moveFire(i, j, MAX_Y, MAX_X, -1, 0, field, field_for_enemy,
                   FIREGOINGUP);
          break;
        case FIREGOINGDOWN:
          moveFire(i, j, MAX_Y, MAX_X, 1, 0, field, field_for_enemy,
                   FIREGOINGDOWN);
          i++;
          break;
        case FIREGOINGLEFT:
          moveFire(i, j, MAX_Y, MAX_X, 0, -1, field, field_for_enemy,
                   FIREGOINGLEFT);
          break;
        case FIREGOINGRIGHT:
          moveFire(i, j, MAX_Y, MAX_X, 0, 1, field, field_for_enemy,
                   FIREGOINGRIGHT);
          j++;
          break;
      }
    }
  }
  return 0;
}

int toFire(Tank *tank, int field_for_enemy[MAX_Y][MAX_X]) {
  Key *key = getStaticKey();
  int fire = false;
  if (*key == Fire) {
    if (tank->dir == UP) {
      field_for_enemy[tank->y][tank->x] = FIREGOINGUP;
      fire = true;
    } else if (tank->dir == DOWN) {
      field_for_enemy[tank->y][tank->x] = FIREGOINGDOWN;
      fire = true;
    } else if (tank->dir == LEFT) {
      field_for_enemy[tank->y][tank->x] = FIREGOINGLEFT;
      fire = true;
    } else if (tank->dir == RIGHT) {
      field_for_enemy[tank->y][tank->x] = FIREGOINGRIGHT;
      fire = true;
    }
  }
  return fire;
}

void moveTank(int limit, int dir1, int dir2, int field[MAX_Y][MAX_X],
              int field_for_enemy[MAX_Y][MAX_X], Tank *tank, int direction,
              int *nexlevel) {
  field[tank->y][tank->x] = ' ';
  int new_coord1 = tank->y + dir1;
  int new_coord2 = tank->x + dir2;

  if (new_coord1 >= 0 && new_coord1 < limit &&
      (field[new_coord1][new_coord2] == EMPTY ||
       field[new_coord1][new_coord2] == FOOD ||
       field[new_coord1][new_coord2] == DOOR ||
       field[new_coord1][new_coord2] == AMMUNITION ||
       field[new_coord1][new_coord2] == LIFE ||
       field[new_coord1][new_coord2] == MONEY ||
       field[new_coord1][new_coord2] == DOORBOSS)) {
    if (field_for_enemy[new_coord1][new_coord2] != EMPTY ||
        field_for_enemy[tank->y][tank->x] != EMPTY) {
      tank->keel = true;
    }
    tank->y = new_coord1;
    tank->x = new_coord2;
  }

  if (field[tank->y][tank->x] == DOOR) *nexlevel = 1;
  if (field[tank->y][tank->x] == DOORBOSS) *nexlevel = 3;
  if (field[tank->y][tank->x] == MONEY) *nexlevel = 2;
  if (field[tank->y][tank->x] == AMMUNITION) tank->ammunitions += 3;
  if (field[tank->y][tank->x] == LIFE) tank->lives++;

  field[tank->y][tank->x] = '@';
  tank->dir = direction;
}

int turn(Tank *tank, int field[MAX_Y][MAX_X],
         int field_for_enemy[MAX_Y][MAX_X]) {
  int nexlevel = false;
  Key *key = getStaticKey();

  if (*key == Up) {
    moveTank(MAX_Y, -1, 0, field, field_for_enemy, tank, UP, &nexlevel);
  } else if (*key == Down) {
    moveTank(MAX_Y, 1, 0, field, field_for_enemy, tank, DOWN, &nexlevel);
  } else if (*key == Left) {
    moveTank(MAX_X, 0, -1, field, field_for_enemy, tank, LEFT, &nexlevel);
  } else if (*key == Right) {
    moveTank(MAX_X, 0, 1, field, field_for_enemy, tank, RIGHT, &nexlevel);
  }

  return nexlevel;
}

bool checkTankCollision(Tank *tank, int field[MAX_Y][MAX_X],
                        int field_for_enemy[MAX_Y][MAX_X], int step,
                        int max_step, int initial_y, int initial_x) {
  if ((field_for_enemy[tank->y][tank->x] == ENIMYGOINGUP ||
       field_for_enemy[tank->y][tank->x] == ENIMYGOINGDOWN ||
       field_for_enemy[tank->y][tank->x] == ENIMYGOINGLEFT ||
       field_for_enemy[tank->y][tank->x] == ENIMYGOINGRIGHT) &&
      step == max_step) {
    tank->keel = true;
  }
  if (tank->keel == true) {
    tank->lives--;
    tank->y = initial_y;
    tank->x = initial_x;
    for (int i = 0; i < MAX_Y; i++) {
      for (int j = 0; j < MAX_X; j++) {
        if (field[i][j] == '@') field[i][j] = EMPTY;
      }
    }
    field[tank->y][tank->x] = '@';
    tank->keel = false;
  }

  return tank->lives <= 0;
}

void clearField(int field[MAX_Y][MAX_X], int field_for_enemy[MAX_Y][MAX_X]) {
  for (int i = 0; i < MAX_Y; i++) {
    for (int j = 0; j < MAX_X; j++) {
      if (field_for_enemy[i][j] == ENIMYGOINGUP ||
          field_for_enemy[i][j] == ENIMYGOINGDOWN ||
          field_for_enemy[i][j] == ENIMYGOINGLEFT ||
          field_for_enemy[i][j] == ENIMYGOINGRIGHT) {
        field_for_enemy[i][j] = ' ';
      }
      if (field[i][j] == '^') {
        field[i][j] = ' ';
      }
    }
  }
}

int checkApples(int field[MAX_Y][MAX_X]) {
  int apples = 0;
  for (int i = 0; i < MAX_Y; i++) {
    for (int j = 0; j < MAX_X; j++) {
      if (field[i][j] == FOOD) apples++;
    }
  }
  return apples;
}

int initTank(int field[MAX_Y][MAX_X], Tank *tank) {
  int error = true;
  for (int i = 0; i < MAX_Y; i++) {
    for (int j = 0; j < MAX_X; j++) {
      if (field[i][j] == '@') {
        tank->x = j;
        tank->y = i;
        error = false;
        break;
      }
    }
  }
  tank->keel = false;
  return error;
}

int read_level(void) {
  int highscore = 0;
  FILE *f = fopen("level.txt", "r");
  if (f != NULL) {
    fscanf(f, "%d", &highscore);
    fclose(f);
  }
  return highscore;
}

void write_level(int score) {
  FILE *file = fopen("level.txt", "w");
  if (file != NULL) {
    fprintf(file, "%d", score);
    fclose(file);
  }
}

int initField(int field[MAX_Y][MAX_X], int level, int *initial_y,
              int *initial_x) {
  const char *level_files[] = {
      "levels/money.txt", "levels/1.txt",  "levels/2.txt",  "levels/3.txt",
      "levels/4.txt",     "levels/5.txt",  "levels/6.txt",  "levels/7.txt",
      "levels/8.txt",     "levels/9.txt",  "levels/10.txt", "levels/11.txt",
      "levels/12.txt",    "levels/13.txt", "levels/14.txt", "levels/15.txt",
      "levels/16.txt",    "levels/17.txt", "levels/18.txt", "levels/19.txt",
      "levels/20.txt"};
  if (level < -1 || level > 20) return 1;
  FILE *file = NULL;
  if (level == -1)
    file = fopen("levels/boss1.txt", "r");
  else
    file = fopen(level_files[level], "r");
  if (file == NULL) {
    file = fopen("levels/win.txt", "r");
    if (file == NULL) return 1;
  }
  char num = 0;
  for (int i = 0; i < MAX_Y; i++) {
    for (int j = 0; j < MAX_X; j++) {
      fscanf(file, "%c", &num);
      field[i][j] = num;
      if (field[i][j] == '@') {
        *initial_y = i;
        *initial_x = j;
      }
      fseek(file, 2, SEEK_CUR);
    }
    fscanf(file, "\n");
  }
  fclose(file);
  return 0;
}

int initFieldForEnemy(int field_for_enemy[MAX_Y][MAX_X],
                      int field[MAX_Y][MAX_X]) {
  for (int i = 0; i < MAX_Y; i++) {
    for (int j = 0; j < MAX_X; j++) {
      if (field[i][j] == ENIMYGOINGUP) {
        field_for_enemy[i][j] = ENIMYGOINGUP;
        field[i][j] = ' ';
      } else if (field[i][j] == ENIMYGOINGDOWN) {
        field_for_enemy[i][j] = ENIMYGOINGDOWN;
        field[i][j] = ' ';
      } else if (field[i][j] == ENIMYGOINGLEFT) {
        field_for_enemy[i][j] = ENIMYGOINGLEFT;
        field[i][j] = ' ';
      } else if (field[i][j] == ENIMYGOINGRIGHT) {
        field_for_enemy[i][j] = ENIMYGOINGRIGHT;
        field[i][j] = ' ';
      } else {
        field_for_enemy[i][j] = ' ';
      }
    }
  }
  return 0;
}

Key *getStaticKey(void) {
  static Key *key = NULL;
  if (key == NULL) {
    key = malloc(sizeof(Key));
    if (key == NULL) {
      return NULL;
    } else {
      *key = Pause;
    }
  }
  return key;
}

void setKey(Key *key) {
  int ch = 0;
  ch = getch();
  switch (ch) {
    case KEY_LEFT:
    case 'a':
      *key = Left;
      break;
    case KEY_RIGHT:
    case 'd':
      *key = Right;
      break;
    case KEY_DOWN:
    case 's':
      *key = Down;
      break;
    case KEY_UP:
    case 'w':
      *key = Up;
      break;
    case 'q':
      *key = Quit;
      break;
    case 'p':
      *key = Pause;
      break;
    case ' ':
    case 'e':
      *key = Fire;
      break;
    case '\n':
      *key = Play;
      break;
    default:
      *key = Pass;
      break;
  }
}
