#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<windows.h>
#include<time.h>

using namespace std;
#define green 0
#define red 1
#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
enum DIRECTION { UP, DOWN, LEFT, RIGHT };

struct position
{
	int ri, ci;
};
struct Snake
{
	position* ps;
	int size;
	int score;
	char sym;
	string Pnames;
	int nop;
	DIRECTION dir;
	int LEFTKEY, RIGHTKEY, UPKEY, DOWNKEY;
};


struct food
{
	position pf;
	bool isJaan;
	int score;
	char sym;
};
bool islegalcoordinate(position p, Snake S)
{
	for (int i = 0; i < S.size; i++)
	{
		if (S.ps[i].ri == p.ri - 1 && S.ps[i].ci == p.ci)
		{
			return false;
		}
	}
	return true;
}
struct food;
void generateFood(food& f, int height, int width, Snake& S)
{
	srand(time(0));
	do {
		f.pf.ri = rand() % height;
		f.pf.ci = rand() % width;
	} while (!islegalcoordinate(f.pf, S));
	f.isJaan = true;
	f.score = 1;
}
void boundary(int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
			{
				SetClr(2);
				gotoRowCol(i, j);
				cout << char(-37);
			}
		}
	}
}
bool stage(int height, int width)
{
	bool isborder = false;
	for (int i = height / 3; i < 2*height/3; i++)
	{
		for (int j = width / 3; j < 2 * width / 3; j++)
		{
			if (i == height/3 || i == 2 * height / 3 - 1 )
			{
				SetClr(1);
				gotoRowCol(i, j);
				cout << char(-37);
				isborder = true;
			
			}
		}
	}
	return isborder;
}
void init(Snake*& S, food& f, int height, int width)
{
	int n;
	cout << "Enter no of players that want to play" << endl;
	cin >> n;
	S = new Snake[n];
	S[0].nop = n;
	int np = S[0].nop;

	if (np == 1)
	{
		S[0].ps = new position[3];
		S[0].ps[0].ri = height / 2;
		S[0].ps[0].ci = width / 2;

		S[0].ps[1].ri = height / 2;
		S[0].ps[1].ci = width / 2 - 1;

		S[0].ps[2].ri = height / 2;
		S[0].ps[2].ci = width / 2 - 2;



		S[0].sym = -37;
		S[0].Pnames = "MR.";

		S[0].size = 3;
		S[0].score = 0;

		S[0].RIGHTKEY = 77, S[0].LEFTKEY = 75, S[0].UPKEY = 72, S[0].DOWNKEY = 80;

		S[0].dir = RIGHT;
	}
	else if (np == 2)
	{
		S[0].ps = new position[3];
		S[0].ps[0].ri = height / 2;
		S[0].ps[0].ci = width / 2;

		S[0].ps[1].ri = height / 2;
		S[0].ps[1].ci = width / 2 - 1;

		S[0].ps[2].ri = height / 2;
		S[0].ps[2].ci = width / 2 - 2;

		S[1].ps = new position[3];
		S[1].ps[0].ri = height / 2 - 3;
		S[1].ps[0].ci = width / 2 - 3;

		S[1].ps[1].ri = height / 2 - 4;
		S[1].ps[1].ci = width / 2 - 4;

		S[1].ps[2].ri = height / 2 - 4;
		S[1].ps[2].ci = width / 2 - 4;


		S[0].size = 3;
		S[0].score = 0;


		S[0].sym = -37;
		S[0].Pnames = "MR.";

		S[0].RIGHTKEY = 77, S[0].LEFTKEY = 75, S[0].UPKEY = 72, S[0].DOWNKEY = 80;

		S[1].size = 3;
		S[1].score = 0;

		S[1].sym = -37;
		S[1].Pnames = "MR.lk";

		S[1].RIGHTKEY = 100, S[1].LEFTKEY = 97, S[1].UPKEY = 119, S[1].DOWNKEY = 115;

		S[0].dir = RIGHT;

		S[1].dir = LEFT;

	}
	else if (np == 3)
	{
		S[0].ps = new position[3];
		S[0].ps[0].ri = height / 2;
		S[0].ps[0].ci = width / 2;

		S[0].ps[1].ri = height / 2;
		S[0].ps[1].ci = width / 2 + 1;

		S[0].ps[2].ri = height / 2;
		S[0].ps[2].ci = width / 2 + 2;

		S[1].ps = new position[3];
		S[1].ps[0].ri = height / 2 + 3;
		S[1].ps[0].ci = width / 2 + 3;

		S[1].ps[1].ri = height / 2 + 4;
		S[1].ps[1].ci = width / 2 + 4;

		S[1].ps[2].ri = height / 2 + 4;
		S[1].ps[2].ci = width / 2 + 4;

		S[2].ps = new position[3];
		S[2].ps[0].ri = height / 2 - 6;
		S[2].ps[0].ci = width / 2 - 6;

		S[2].ps[1].ri = height / 2 - 7;
		S[2].ps[1].ci = width / 2 - 7;

		S[2].ps[2].ri = height / 2 - 7;
		S[2].ps[2].ci = width / 2 - 7;

		S[0].size = 3;
		S[0].score = 0;


		S[0].sym = -37;
		S[0].Pnames = "MR.";

		S[0].RIGHTKEY = 77, S[0].LEFTKEY = 75, S[0].UPKEY = 72, S[0].DOWNKEY = 80;

		S[1].size = 3;
		S[1].score = 0;

		S[1].sym = -37;
		S[1].Pnames = "MR.lk";

		S[1].RIGHTKEY = 100, S[1].LEFTKEY = 97, S[1].UPKEY = 119, S[1].DOWNKEY = 115;

		S[0].dir = RIGHT;

		S[1].dir = LEFT;
		S[2].dir = UP;

		S[2].size = 3;
		S[2].score = 0;

		S[2].sym = -37;
		S[2].Pnames = "MR.lk";

		S[2].RIGHTKEY = 108, S[2].LEFTKEY = 106, S[2].UPKEY = 105, S[2].DOWNKEY = 107;

	}
	else if (np == 4)
	{
		S[0].ps = new position[3];
		S[0].ps[0].ri = height / 2;
		S[0].ps[0].ci = width / 2;

		S[0].ps[1].ri = height / 2;
		S[0].ps[1].ci = width / 2 - 1;

		S[0].ps[2].ri = height / 2;
		S[0].ps[2].ci = width / 2 - 2;

		S[1].ps = new position[3];
		S[1].ps[0].ri = height / 2 - 3;
		S[1].ps[0].ci = width / 2 - 3;

		S[1].ps[1].ri = height / 2 - 4;
		S[1].ps[1].ci = width / 2 - 4;

		S[1].ps[2].ri = height / 2 - 4;
		S[1].ps[2].ci = width / 2 - 4;

		S[2].ps = new position[3];
		S[2].ps[0].ri = height / 2 - 6;
		S[2].ps[0].ci = width / 2 - 6;

		S[2].ps[1].ri = height / 2 - 7;
		S[2].ps[1].ci = width / 2 - 7;

		S[2].ps[2].ri = height / 2 - 7;
		S[2].ps[2].ci = width / 2 - 7;

		S[3].ps = new position[3];
		S[3].ps[0].ri = height / 2 + 5;
		S[3].ps[0].ci = width / 2 + 5;

		S[3].ps[1].ri = height / 2 + 6;
		S[3].ps[1].ci = width / 2 + 6;

		S[3].ps[2].ri = height / 2 + 6;
		S[3].ps[2].ci = width / 2 + 6;

		S[0].size = 3;
		S[0].score = 0;


		S[0].sym = -37;
		S[0].Pnames = "MR.";

		S[0].RIGHTKEY = 77, S[0].LEFTKEY = 75, S[0].UPKEY = 72, S[0].DOWNKEY = 80;

		S[1].size = 3;
		S[1].score = 0;

		S[1].sym = -37;
		S[1].Pnames = "MR.lk";

		S[1].RIGHTKEY = 100, S[1].LEFTKEY = 97, S[1].UPKEY = 119, S[1].DOWNKEY = 115;

		S[0].dir = RIGHT;

		S[1].dir = LEFT;
		S[2].dir = UP;
		S[3].dir = DOWN;
		S[2].size = 3;
		S[2].score = 0;

		S[2].sym = -37;
		S[2].Pnames = "MR.lk";

		S[2].RIGHTKEY = 108, S[2].LEFTKEY = 106, S[2].UPKEY = 105, S[2].DOWNKEY = 107;

		S[3].size = 3;
		S[3].score = 0;


		S[3].sym = -37;
		S[3].Pnames = "MR.";

		S[3].RIGHTKEY = 54, S[3].LEFTKEY = 52, S[3].UPKEY = 56, S[3].DOWNKEY = 53;

	}
	stage(height, width);
	boundary(height, width);
	generateFood(f, height, width, S[0]);
	//generateFood(f, height, width, S[1]);
	f.sym = -37;

}
void displayfood(food f)
{
	gotoRowCol(f.pf.ri, f.pf.ci);
	SetClr(4);
	cout << '*';
}
void displaySanp(const Snake* S)
{

	int nop = S[0].nop;
	for (int j = 0; j < nop; j++)
	{

		for (int i = 0; i < S[j].size; i++)
		{
			if (j == 0)
			{
				SetClr(6);
				gotoRowCol(S[j].ps[i].ri, S[j].ps[i].ci);
				cout << 'O';
			}
			else if (j == 1)
			{
				SetClr(7);
				gotoRowCol(S[j].ps[i].ri, S[j].ps[i].ci);
				cout << 'O';
			}
			else if (j == 2)
			{
				SetClr(8);
				gotoRowCol(S[j].ps[i].ri, S[j].ps[i].ci);
				cout << 'O';
			}
			else if (j == 3)
			{
				SetClr(9);
				gotoRowCol(S[j].ps[i].ri, S[j].ps[i].ci);
				cout << 'O';
			}
		}
	}
}

bool ripSanp(const Snake* S)
{
	for (int j = 0; j < S[0].nop; j++)
	{
		for (int i = 1; i < S[j].size; i++)
		{
			if (S[j].ps[0].ri == S[j].ps[i].ri && S[j].ps[0].ci == S[j].ps[i].ci)
			{
				return true;
			}
		}
	}
	return false;
}
bool ripSanpkissanp(Snake* S)
{
	//forP1
	for (int j = 0; j < S[0].nop; j++)
	{
		for (int i = 1; i < S[0].nop; i++)
		{
			for (int k = 1; k < S[j].size; k++)
			{
				if (S[i].ps[0].ri == S[j].ps[k].ri && S[i].ps[0].ci == S[j].ps[k].ci)
				{
					return true;
				}
			}
		}
		
	}
	return false;
}

void eraseSanp(const Snake* S)
{
	int nop = S[0].nop;
	for (int j = 0; j < nop; j++)
	{
		for (int i = 0; i < S[j].size; i++)
		{
			gotoRowCol(S[j].ps[i].ri, S[j].ps[i].ci);
			cout << ' ';
		}
	}
}
void moveSanp(Snake* S, int height, int width)
{
	int nop = S[0].nop;
	for (int j = 0; j < nop; j++)
	{
		for (int i = S[j].size - 1; i - 1 >= 0; i--)
		{
			S[j].ps[i] = S[j].ps[i - 1];
		}
	}
	for (int j = 0; j < nop; j++)
	{
		if (stage(height, width));
		{
			break;
		}
		if (!stage(height, width));
		{
			switch (S[j].dir)
			{
			case UP:
				S[j].ps[0].ri--;
				if (S[j].ps[0].ri == 0)
				{
					S[j].ps[0].ri = height - 2;
				}
				break;

			case DOWN:
				S[j].ps[0].ri++;
				if (S[j].ps[0].ri == height - 1)
				{
					S[j].ps[0].ri = 1;
				}
				break;

			case LEFT:
				S[j].ps[0].ci--;
				if (S[j].ps[0].ci == 0)
				{
					S[j].ps[0].ci = width - 2;
				}

				break;

			case RIGHT:
				S[j].ps[0].ci++;
				if (S[j].ps[0].ci == width - 1)
				{
					S[j].ps[0].ci = 1;
				}

				break;

			}
		}


	}
}
void changeDir(Snake& S, char k)
{
	if (k == S.LEFTKEY)
		if (S.dir != RIGHT)
		{
			S.dir = LEFT;
		}
	if (k == S.RIGHTKEY)
		if (S.dir != LEFT)
		{
			S.dir = RIGHT;
		}
	if (k == S.UPKEY)
		if (S.dir != DOWN)
		{
			S.dir = UP;
		}
	if (k == S.DOWNKEY)
		if (S.dir != UP)
		{
			S.dir = DOWN;
		}
}
bool foodeaten(Snake& S, food f)
{
	/*for (int i = 0; i < 2; i++)
	{*/
	return S.ps[0].ri == f.pf.ri && S.ps[0].ci == f.pf.ci;
	/*}*/
}
void expandSnake(Snake& S)
{
	/*for (int j = 0; j < 2; j++)
	{*/
	position* EP = new position[S.size + 1];
	for (int i = 0; i < S.size; i++)
	{
		EP[i] = S.ps[i];
	}
	EP[S.size] = S.ps[S.size - 1];
	S.size++;
	delete[] S.ps;
	S.ps = EP;
	/*}*/
}
void displayNames(Snake* S)
{
	for (int i = 0; i < S[0].nop; i++)
	{
		gotoRowCol(10 + (1 + i), 120);
		cout << S[i].Pnames << " score :" << S[i].score;
	}
}
int main()
{
	char ch;
	int height = 80, width = 100;
	Snake* S;
	food f;
	//boundary(height, width);
	init(S, f, height, width);
	generateFood(f, height, width, S[0]);
	displayfood(f);
	while (true)
	{
		displayNames(S);
		if (_kbhit())
		{
			ch = _getch();

			if (ch == -32)
			{
				/*	cout << "PRESSED KEY "<<ch<<" HAS ASCII " << int(ch) << endl;*/

				ch = _getch();
				changeDir(S[0], ch);
			}
			else if (ch == 100 || ch == 97 || ch == 119 || ch == 115)
			{
				/*ch = _getch();*/
				changeDir(S[1], ch);
			}
			else if (ch == 105 || ch == 106 || ch == 107 || ch == 108)
			{
				/*ch = _getch();*/
				changeDir(S[2], ch);
			}
			else if (ch == 56 || ch == 52 || ch == 53 || ch == 54)
			{
				/*ch = _getch();*/
				changeDir(S[3], ch);
			}
		}
		displaySanp(S);
		Sleep(10);
		eraseSanp(S);
		moveSanp(S, height, width);
		
		if (ripSanp(S))
		{
			break;
		}
		
		/*if (ripSanpkissanp(S))
		{
			break;
		}*/
		
		for (int i = 0; i < S[0].nop; i++)
		{
			if (foodeaten(S[i], f))
			{
				S[i].score += f.score;
				/*	if (S.score == 3)
					{
						cout << "U WIN BLOODY";
						system("cls");
					}*/
				generateFood(f, height, width, S[i]);

				displayfood(f);
				expandSnake(S[i]);

			}
		}

	}
	gotoRowCol(height / 2, width / 2);
	cout << " TY TY FISH";
	_getch();
}