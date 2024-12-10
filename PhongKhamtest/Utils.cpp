#include "Utils.h"
#include <iostream>
#ifdef _WIN32
#include <cstdlib> // system()
#else
#include <unistd.h>
#endif
#include <conio.h> // _getch()

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
