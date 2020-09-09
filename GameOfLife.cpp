#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

#define SizeX 25
#define SizeY 55

int A[SizeX][SizeY] = { 0 };
bool B[SizeX][SizeY] = { 0 };

void gotoXY(int x, int y) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD m = { x, y };
	SetConsoleCursorPosition(h, m);
}

void setColor(int x) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, x);
}
void Nocursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void count() {
	for (int i = 0; i < SizeX; i++) {
		for (int j = 0; j < SizeY; j++) {
			int c = 0;
			if (i > 0 && j > 0) c += B[i - 1][j - 1];
			if (i > 0) c += B[i - 1][j];
			if (i > 0 && j < SizeY - 1) c += B[i - 1][j + 1];
			if (j > 0) c += B[i][j - 1];
			if (j < SizeY - 1) c += B[i][j + 1];
			if (i < SizeX - 1 && j > 0) c += B[i + 1][j - 1];
			if (i < SizeX - 1) c += B[i + 1][j];
			if (i < SizeX - 1 && j < SizeY - 1) c += B[i + 1][j + 1];
			A[i][j] = c;
		}
	}
}

void turn() {
	for (int i = 0; i < SizeX; i++) {
		for (int j = 0; j < SizeY; j++) {
			if (A[i][j] < 2 || A[i][j] > 3) B[i][j] = 0;
			else if (A[i][j] == 3 && B[i][j] == 0) B[i][j] = 1;
		}
	}
}

void draw() {
	for (int i = 0; i < SizeX; i++) {
		for (int j = 0; j < SizeY; j++) {
			if (B[i][j]) printf("%c ", 254);
			else printf("  ");
		}
		putchar('\n');
	}
}

void init() {
	int i = 0, j = 0;
	while (1) {
		gotoXY(2 * j, i);
		char c = _getch();
		if (c == ' ') {
			if (B[i][j] == 1) {
				B[i][j] = 0;
				gotoXY(2 * j, i); printf(" ");
			}
			else {
				B[i][j] = 1;
				gotoXY(2 * j, i); printf("%c", 254);
			}
		}
		else if (c == 13) break;
		else {
			if (c == 224) c = _getch();
			if (c == 72 || c == 'W' || c == 'w') {
				if (i > 0) i--;
			}
			else if (c == 80 || c == 'S' || c == 's') {
				if (i < SizeX - 1) i++;
			}
			else if (c == 77 || c == 'D' || c == 'd') {
				if (j < SizeY - 1) j += 1;
			}
			else if (c == 75 || c == 'A' || c == 'a') {
				if (j > 0) j -= 1;
			}
		}
	}
}

void drawBorder() {
	for (int i = 0; i <= SizeX; i++) {
		for (int j = 0; j <= SizeY; j++) {
			if (i == SizeX && j == SizeY) printf("%c", 188);
			else if (i == SizeX) printf("%c%c", 205, 205);
			else if (j == SizeY) printf("%c", 186);
			else printf("  ");
		}
		putchar('\n');
	}

	for (int i = 0; i < SizeX; i++) {
		setColor(rand() % 15);
		gotoXY(2 * SizeY + 1, i);
		for (int j = 0; j < 9; j++)
			putchar(254);
	}

	string s = "GAME OF LIFE\n";
	string t = "Nguyen Thanh Luan - (CatRom)";
	setColor(12);
	gotoXY(0, SizeX + 2);
	for (int i = 0; i < s.size(); i++) {
		cout << s[i];
		Sleep(30);
	}
	setColor(10);
	for (int i = 0; i < t.size(); i++) {
		cout << t[i];
		Sleep(30);
	}
	
	setColor(11);
	s = "Step 1: Using direction key and SPACE to initalize the map";
	t = "Step 2: ENTER and enjoy the result";
	gotoXY(60, SizeX + 3); 
	for (int i = 0; i < s.size(); i++) {
		cout << s[i];
		Sleep(20);
	}
	gotoXY(60, SizeX + 4); 
	for (int i = 0; i < t.size(); i++) {
		cout << t[i];
		Sleep(20);
	}
}

int main() {
	system("mode 120, 30");
	srand(time(0));
	drawBorder();
	init();

	Nocursortype();

	while (!_kbhit()) {
		setColor(8 + rand() % 7);
		gotoXY(0, 0);
		draw();
		count();
		turn();
		Sleep(100);
	}

	_getch();
	return 0;
}