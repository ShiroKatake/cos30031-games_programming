#include <iostream>
#include <conio.h>
using namespace std;

int map[9][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 3, 0, 4, 1, 4, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 1, 1, 0, 1, 0, 4, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 2, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

char keyboardInput;

int x = 2;
int y = 7;

bool win = false;
bool lose = false;

void Move(int horizontal, int vertical) {
	int x2 = x + horizontal;
	int y2 = y + vertical;
	if (map[y2][x2] != 1) {
		map[y][x] = 0;
		x += horizontal;
		y += vertical;
	}
	if (map[y2][x2] == 3) {
		win = true;
	}
	if (map[y2][x2] == 4) {
		lose = true;
	}
	map[y][x] = 2;
}

void GetInput() {
	while (!_kbhit()) {
		//Wait for user input before update next frame.
		//This "game" only needs to update if there's a user input anyway...
	}
	keyboardInput = _getch();
}

}

void Render() {
	for (auto& rows : map) // Iterating over rows
	{
		for (int i = 0; i < 8; i++)
		{
			switch (rows[i])
			{
				case 1:
					cout << "#";
					break;
				case 2:
					cout << "P";
					break;
				case 3:
					cout << "G";
					break;
				case 4:
					cout << "D";
					break;
				default:
					cout << " ";
					break;
			}
			if (i + 1 == 8) {
				cout << "\n";
			}
		}
	}
}

int main() {

	while (true)
	{
		ProcessInput();
		Update();
		Render();

		cin.get();
	}
}