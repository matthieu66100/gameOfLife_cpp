#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

const int TAILLEX = 20;
const int TAILLEY = 60;
string tab_1[TAILLEX][TAILLEY];
string tab_2[TAILLEX][TAILLEY];
int tab_check[TAILLEX][TAILLEY];

void initTables()
{
	for (int i = 0; i < TAILLEX; i++)
	{
		for (int j = 0; j < TAILLEY; j++)
		{
			tab_1[i][j] = " ";
			tab_2[i][j] = " ";
		}
	}

	for (int i = 0; i < TAILLEX; i++)
	{
		for (int j = 0; j < TAILLEY; j++)
		{
			tab_check[i][j] = 0;
		}
	}
}

/**
affichage dans un terminal du tableau tab_1
*/
void printTable()
{
	for (int i = 0; i < TAILLEX; i++)
	{
		for (int j = 0; j < TAILLEY; j++)
		{
			cout << tab_1[i][j];
		}
		cout << endl;
	}
}

/**
verifie les cases autour d'une cellule et renvoie la valeur de cases en vie
*/
int arroundCheck(int x, int y)
{
	int value = 0;

	if (x > 0 && y > 0 && tab_1[x - 1][y - 1] == "O")
		value = value + 1;
	if (y > 0 && tab_1[x][y - 1] == "O")
		value = value + 1;
	if (x < TAILLEX - 1 && y > 0 && tab_1[x + 1][y - 1] == "O")
		value = value + 1;

	if (x > 0 && tab_1[x - 1][y] == "O")
		value = value + 1;
	if (x < TAILLEX - 1 && tab_1[x + 1][y] == "O")
		value = value + 1;

	if (x > 0 && y < TAILLEY - 1 && tab_1[x - 1][y + 1] == "O")
		value = value + 1;
	if (y < TAILLEY - 1 && tab_1[x][y + 1] == "O")
		value = value + 1;
	if (x < TAILLEX - 1 && y < TAILLEY - 1 && tab_1[x + 1][y + 1] == "O")
		value = value + 1;

	return value;
}

/**
règles du jeux de la vie et application sur tab_2
*/
void newGeneration()
{
	for (int i = 0; i < TAILLEX; i++)
	{
		for (int j = 0; j < TAILLEY; j++)
		{
			tab_check[i][j] = arroundCheck(i, j);

			// si 3 voisine = vivante
			if (tab_check[i][j] == 3)
			{
				tab_2[i][j] = "O";
			}
			// si <2 voisines = morte
			else if (tab_check[i][j] < 2)
			{
				tab_2[i][j] = " ";
			}
			// si >3 voisines = morte
			else if (tab_check[i][j] > 3)
			{
				tab_2[i][j] = " ";
			}
			// si 2 voisines = bouge pas
			else
			{
				tab_2[i][j] = tab_1[i][j];
			}
		}
	}
}

/*
ajoute manuellement une cellule pleine en position X/Y du tab_1
*/
void addCell(int posx, int posy)
{
	tab_1[posx][posy] = "O";
}

/*
permet de tranferer tab_2 sur tab_1
*/
void tampTab()
{
	for (int i = 0; i < TAILLEX; i++)
	{
		for (int j = 0; j < TAILLEY; j++)
		{
			tab_1[i][j] = tab_2[i][j];
		}
	}
}

/*
dessin d'un séparateur pour des infos hud
*/
void hud(int nbGen)
{
	cout << "generation : " << nbGen + 1 << endl;
	for (int i = 0; i < TAILLEX; i++)
	{
		cout << "_";
	}
	cout << endl;
}

/*
boucle de jeux
*/
int main()
{
	initTables();

	addCell(10, 11);
	addCell(10, 12);
	addCell(10, 13);
	addCell(9, 12);
	addCell(11, 12);
	addCell(9, 11);

	// boucle de générations
	for (int i = 0; i < 10; i++)
	{
		cout << "\033[2J";
		hud(i);
		printTable();
		newGeneration();
		tampTab();
		usleep(1000000);
	}
	cout << "fin" << endl;
}
