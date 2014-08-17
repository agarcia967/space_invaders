/* CS150 FALL 2013 12092013
 * Anthony Garcia
 * Garcia_SpaceInvaders_CS150.cpp
 * Description: This program displays a moving ship using windows.h and SetConsoleCursorPosition().
 */

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;

namespace Colors
{
	const int BLUE_TEXT     = 0x09;
	const int GREEN_TEXT    = 0x0A;
	const int RED_TEXT      = 0x0C;
	const int DEFAULT_COLOR = 0x0F;
}
using namespace Colors;
void BlueText(int Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE_TEXT);
}
void GreenText(int Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_TEXT);
}
void RedText(int Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED_TEXT);
}
void ResetColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_COLOR);     
}

void placeCursor(int col, int row)
{
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = col;
	position.Y = row;
	SetConsoleCursorPosition(screen, position);
}

void splash()
{
	ResetColor();
	int PositionX = 15;
	int PositionY = 7;
	placeCursor(PositionX,PositionY);
	cout << "Welcome to Space Invaders!";
	
	placeCursor(PositionX,++PositionY);
	cout << "*******************************************";
	
	placeCursor(PositionX,++PositionY);
	cout << "Use the arrow keys <- and -> to move";

	placeCursor(PositionX,++PositionY);
	cout << "the space ship ";
	GreenText(1);
	cout << ">/^\\<";
	ResetColor();
	cout << " Left and Right";

	placeCursor(PositionX,++PositionY);
	cout << "Use the space bar to Shoot ";
	BlueText(1);
	cout << "|";
	ResetColor();
	
	placeCursor(PositionX,++PositionY);
	cout << "the Space Invader ";
	RedText(1);
	cout << "<<O>>";
	ResetColor();
	cout << " as many times as you can.";
	
	PositionY+=2;
	placeCursor(PositionX,PositionY);
	cout << "Press ESC to quit at any time.";

	PositionY+=2;
	placeCursor(PositionX,PositionY);
	cout << "Press ENTER to START.";
	cin.ignore();

	for(int i = PositionY;i>=7;i--)
	{
		placeCursor(15,i);
		cout << string(50,' ');
	}
}

void writeBG()
{
	ResetColor();
	placeCursor(22,0);
	cout << "Space Invaders (by Anthony Garcia 2013)";
	placeCursor(1,1);
	cout << string(77,'*');
	int x = 0;
	for(int y = 0; y < 21; y++)
	{
		x++;
		placeCursor(1,y+2);
		cout << '*';
		placeCursor(77,y+2);
		cout << '*';
	}
	placeCursor(1,22);
	cout << string(77,'*');
	placeCursor(1,23);
	cout << "Shots Fired: 000";
	placeCursor(25,23);
	cout << "Times Hit: 000";
	placeCursor(50,23);
	cout << "Accuracy: 000%";
}

void gameOver(double _score);

bool quit(double _score)
{
	char resp;
	bool cancel = false;
	placeCursor(20,10);
	cout << "Are you sure you want to quit (Y/N)? ";
	do
	{
		placeCursor(57,10);
		cin >> resp;
		cin.clear();
		switch(toupper(resp))
		{
			case 'Y':
				placeCursor(30,12);
				cout << "Your score: " << _score;
				cin.clear();
				cin.ignore();
				return true;
				break;
			case 'N':
				return false;
				break;
			default:
				break;
		}
	}
	while(resp!='Y');
}

void gameOver(double _score)
{
	int score=0;
	placeCursor(35,11);
	cout << "GAME OVER";
	placeCursor(30,12);
	
	cout << "Your score: " << _score;
	cin.clear();
	cin.ignore();
}

class Invader
{
private:
	int oldPositionX;
	int oldPositionY;
public:
	void remove()
	{
		placeCursor(oldPositionX, oldPositionY);
		cout << "     ";
	}
	void place(int _positionX, int _positionY,bool _stasis_state)
	{
		placeCursor(_positionX, _positionY);
		oldPositionX = _positionX;
		oldPositionY = _positionY;
		if(_stasis_state) BlueText(1);
		else RedText(1);
		cout << "<<O>>";
		ResetColor();
	}
	int getOPX()
	{
		return oldPositionX;
	}
	int getOPY()
	{
		return oldPositionY;
	}
};

class Missile
{
	private:
	int oldPositionX;
	int oldPositionY;
	public:
	void remove()
	{
		placeCursor(oldPositionX, oldPositionY);
		cout << ' ';
	}
	void remove(int _positionX, int _positionY)
	{
		placeCursor(_positionX, _positionY);
		cout << ' ';
	}
	void place(int _positionX, int _positionY)
	{
		placeCursor(_positionX, _positionY);
		oldPositionX = _positionX;
		oldPositionY = _positionY;
		BlueText(1);
		cout << '|';
		ResetColor();
	}
};

class SpaceShip
{
	private:
	int oldPositionX;
	int oldPositionY;
	public:
	void remove()
	{
		placeCursor(oldPositionX, oldPositionY);
		cout << "     ";
	}
	void place(int _positionX, int _positionY)
	{
		placeCursor(_positionX, _positionY);
		oldPositionX = _positionX;
		oldPositionY = _positionY;
		GreenText(1);
		cout << ">/^\\<";
		ResetColor();
	}
	int fireCoord()
	{
		return oldPositionX+2;
	}
	bool moveR(int _XMAX)
	{
		if(oldPositionX>=_XMAX) return false;
		else return true;
	}
	bool moveL(int _XMIN)
	{
		if(oldPositionX<=_XMIN) return false;
		else return true;
	}
	int getOPX()
	{
		return oldPositionX;
	}
	int getOPY()
	{
		return oldPositionY;
	}
};

int main()
{
	SetConsoleTitle("Space Invaders by Anthony Garcia (2013)");
	const int SCREEN_XMIN = 2;
	const int SCREEN_XMAX = 72;
	const int SCREEN_YMIN = 2;
	const int SCREEN_YMAX = 21;
	const int FPS = 50;//default == 50
	
	double score = 0;
	double accuracy = 0;
	int hits = 0;
	
	writeBG();
	splash();
	
	Invader enemyShip;
	int enemyXPos = SCREEN_XMIN;
	int enemyYPos = SCREEN_YMIN;
	bool forward = true;
	int counter = 0;
	bool enemySpeed = true;
	bool stasisState= false;

	SpaceShip ship;
	int shipXPos = 37;
	const int shipYPos = SCREEN_YMAX;
	
	Missile shot;
	int Missiles = 0;
	int missileXPos = 0;
	int missileYPos = 20;
	bool fired = false;
	COORD object;
	vector<COORD> missiles;
	
	int timer = 0;
	int seconds = 0;
	const int countdownTimer = 20;
	int countdown = countdownTimer;

	while(enemyYPos<=SCREEN_YMAX)
	{
		score = (accuracy*100)+(Missiles*10);
	//////Invader Ship///////////////
		placeCursor(enemyXPos,enemyYPos);
		if(enemyXPos<=SCREEN_XMIN) forward = true;
		else if(enemyXPos>=SCREEN_XMAX) forward = false;
		if(countdown<=1) stasisState = true;
		else stasisState = false;
		enemyShip.place(enemyXPos,enemyYPos,stasisState);
		if(enemySpeed)
		{
			if(70==counter)
			{
				enemyYPos++;
				counter=0;
			}
			counter++;
			if(forward==true) enemyXPos++;
			else enemyXPos--;
			enemySpeed=false;
		}
		else enemySpeed=true;
		if(enemyShip.getOPY()==ship.getOPY() && (enemyShip.getOPX()>=ship.getOPX() && enemyShip.getOPX()<=ship.getOPX()+5))
		{
			gameOver(score);
			return(0);
		}
		//every 20 iterations is 1 sec
	//////Space Ship/////////////////
		if(GetAsyncKeyState(VK_RIGHT))
		{
			if(ship.moveR(SCREEN_XMAX)) shipXPos++;
		}
		if(GetAsyncKeyState(VK_LEFT))
		{
			if(ship.moveL(SCREEN_XMIN)) shipXPos--;
		}
		ship.place(shipXPos,shipYPos);
		
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			bool quitR = quit(score);
			cin.ignore();
			if(quitR==true)
			{
				return(0);
			}
			placeCursor(20,10);
			cout << string(50,' ');
		}
	//////Missiles///////////////////
		cin.clear();
		if(GetAsyncKeyState(VK_SPACE) && fired==false)
		{
			++Missiles;
			object.X = ship.fireCoord();
			object.Y = 20;
			missiles.push_back(object);
			fired = true; //Comment this line to allow rapid-fire
		}
		placeCursor(14,23);
		cout <<setw(3) << Missiles;
		if(timer<600)
		{
			for(int i = 0; i<missiles.size(); i++)
			{
				if(missiles[i].Y>=SCREEN_YMIN)
				{
					shot.place(missiles[i].X,missiles[i].Y--);
				}
				if(missiles[i].X>=enemyShip.getOPX() && missiles[i].X<=enemyShip.getOPX()+5 && missiles[i].Y==enemyShip.getOPY())
				{
					hits++;
				}
			}
		}
	//////-//////////////////////////
		placeCursor(36,23);
		cout <<setw(3) << hits;
		
		if(Missiles>0)
		{
			accuracy = hits * 100 / Missiles;
		}
		placeCursor(60,23);
		cout <<setw(3) << accuracy << "%";
		
	//////Sleep//////////////////////
		Sleep(FPS);
	//////-//////////////////////////

		if(timer==20)
		{
			countdown--;
			timer = 0;
		}
		if(countdown<=0)
		{
			missiles.clear();
			placeCursor(22,3);
			cout << string(45,' ');
			countdown = countdownTimer;
		}
		if(countdown<4)
		{
			placeCursor(22,3);
			RedText(1);
			cout << "WARNING!!! Enemy's Missile Stasis field in " << countdown;
			ResetColor();
		}
		timer++;
		
		for(int i = 0; i<missiles.size(); i++)
		{
			shot.remove(missiles[i].X,missiles[i].Y+1);
		}
		ship.remove();
		enemyShip.remove();
		if(GetAsyncKeyState(VK_SPACE)==false)
		{
			fired = false;
		}
	}
}//Anthony Garcia
