#include "../tank_T-39.h"

void inclusionOfColors(void) {
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(10, COLOR_CYAN, COLOR_BLACK);
  init_pair(6, COLOR_WHITE, COLOR_BLACK);
  init_pair(7, COLOR_GREEN, COLOR_BLACK);
  init_pair(8, COLOR_BLACK, COLOR_GREEN);
  init_pair(9, COLOR_BLACK, COLOR_RED);
  init_pair(11, COLOR_RED, COLOR_CYAN);
  init_pair(12, COLOR_RED, COLOR_BLACK);
}

void drawPhone(int color) {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  int startY = (screenHeight - MAX_Y) / 2;
  int startX = (screenWidth - MAX_X * 3) / 2;

  attron(COLOR_PAIR(color));
  for (int i = 0; i < MAX_Y; i++) {
    for (int j = 0; j < MAX_X * 3; j++)
      mvaddch(startY + i, startX + j, ' ' | A_REVERSE);
  }
}

void drawButtonTank(int color) {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  int startY = (screenHeight - 10) / 2;
  int startX = (screenWidth - 15) / 2;

  attron(COLOR_PAIR(color));
  mvaddch(startY, startX, ' ');
  printw("               ");
  mvaddch(startY + 1, startX, ' ');
  printw("   Tank T-39   ");
  mvaddch(startY + 2, startX, ' ');
  printw("               ");
}

void drawButtonEmpty(int color) {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  int startY = (screenHeight) / 2;
  int startX = (screenWidth - 15) / 2;

  attron(COLOR_PAIR(color));
  mvaddch(startY, startX, ' ');
  printw("               ");
  mvaddch(startY + 1, startX, ' ');
  printw("   Reset       ");
  mvaddch(startY + 2, startX, ' ');
  printw("               ");
}

void drawButtonExit(int color) {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  int startY = (screenHeight + 10) / 2;
  int startX = (screenWidth - 15) / 2;

  attron(COLOR_PAIR(color));
  mvaddch(startY, startX, ' ');
  printw("               ");
  mvaddch(startY + 1, startX, ' ');
  printw("   Exit        ");
  mvaddch(startY + 2, startX, ' ');
  printw("               ");
}

void drawGame(int field[MAX_Y][MAX_X], int field_for_enemy[MAX_Y][MAX_X]) {
  Key *key = getStaticKey();
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  int startY = (screenHeight - MAX_Y) / 2;
  int startX = (screenWidth - MAX_X * 3) / 2;

  attron(COLOR_PAIR(4));
  for (int i = 0; i < MAX_Y; i++) {
    for (int j = 0; j < MAX_X; j++) {
      int y = startY + i;
      int x = startX + j * 3;

      if (field_for_enemy[i][j] == ENIMYGOINGUP ||
          field_for_enemy[i][j] == ENIMYGOINGDOWN ||
          field_for_enemy[i][j] == ENIMYGOINGLEFT ||
          field_for_enemy[i][j] == ENIMYGOINGRIGHT) {
        attron(COLOR_PAIR(2));
        mvaddch(y, x, '(');
        mvaddch(y, x + 1, '-');
        mvaddch(y, x + 2, ')');
      } else if (field_for_enemy[i][j] == FIREGOINGUP ||
                 field_for_enemy[i][j] == FIREGOINGDOWN ||
                 field_for_enemy[i][j] == FIREGOINGLEFT ||
                 field_for_enemy[i][j] == FIREGOINGRIGHT) {
        attron(COLOR_PAIR(1));
        mvaddch(y, x, ' ');
        mvaddch(y, x + 1, '*');
        mvaddch(y, x + 2, ' ');
      } else if (field[i][j] == '@') {
        attron(COLOR_PAIR(1));
        mvaddch(y, x, '|');
        mvaddch(y, x + 1, '0');
        mvaddch(y, x + 2, '|');
        if (*key == Up) {
          mvaddch(y, x, '/');
          mvaddch(y, x + 2, '\\');
        } else if (*key == Down) {
          mvaddch(y, x, '\\');
          mvaddch(y, x + 2, '/');
        } else if (*key == Right) {
          mvaddch(y, x + 2, '>');
        } else if (*key == Left) {
          mvaddch(y, x, '<');
        }
      } else if (field[i][j] == '1') {
        attron(COLOR_PAIR(6));
        mvaddch(y, x, '(');
        mvaddch(y, x + 1, '`');
        mvaddch(y, x + 2, ')');
      } else if (field[i][j] == '^') {
        attron(COLOR_PAIR(2));
        mvaddch(y, x, '-');
        mvaddch(y, x + 1, '^');
        mvaddch(y, x + 2, '-');
      } else if (field[i][j] == AMMUNITION) {
        attron(COLOR_PAIR(5));
        mvaddch(y, x, '[');
        mvaddch(y, x + 1, '$');
        mvaddch(y, x + 2, ']');
      } else if (field[i][j] == WEAKWALL) {
        attron(COLOR_PAIR(3));
        mvaddch(y, x, '[');
        mvaddch(y, x + 1, '=');
        mvaddch(y, x + 2, ']');
      } else if (field[i][j] == LIFE) {
        attron(COLOR_PAIR(1));
        mvaddch(y, x, '(');
        mvaddch(y, x + 1, '+');
        mvaddch(y, x + 2, ')');
      } else if (field[i][j] == DOORBOSS || field[i][j] == MONEY) {
        attron(COLOR_PAIR(1));
        mvaddch(y, x, (field[i][j] == MONEY) ? '$' : '!');
        mvaddch(y, x + 1, (field[i][j] == MONEY) ? '$' : '!');
        mvaddch(y, x + 2, (field[i][j] == MONEY) ? '$' : '!');
      } else {
        attron(COLOR_PAIR(4));
        if (field[i][j] == DOOR) attron(COLOR_PAIR(1));
        mvaddch(y, x, field[i][j]);
        mvaddch(y, x + 1, field[i][j]);
        mvaddch(y, x + 2, field[i][j]);
      }
    }
  }
}

void drawAmminitions(int ammunitions) {
  attron(COLOR_PAIR(6));
  mvaddch(1, 1, 'A');
  printw("                     ");
  mvaddch(1, 1, 'A');
  printw("mmunitions: %d", ammunitions);
}

void drawApples(int apples) {
  attron(COLOR_PAIR(6));
  mvaddch(1, 20, 'A');
  printw("                     ");
  mvaddch(1, 20, 'A');
  printw("pples: %d%%", apples);
}

void drawLives(int lives) {
  attron(COLOR_PAIR(6));
  mvaddch(1, 35, 'L');
  printw("ives: %d", lives);
}

void drawLevel(int level) {
  attron(COLOR_PAIR(6));
  mvaddch(1, 50, 'L');
  printw("evel: %d", level);
}
