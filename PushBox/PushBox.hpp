#ifndef PUSHBOX_HPP
#define PUSHBOX_HPP

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <Locale.h>
#include <windows.h>
extern int level;
extern int map[3][10][10];
void gamedraw(HDC hdc);
void keyEvent();
bool jude();

#endif // PUSHBOX_HPP