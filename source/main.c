#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#pragma warning (disable:4996)
#pragma warning (disable:6031)
#pragma warning (disable:6001)
#pragma warning (disable:4703)
int anzahlnachbarn(char feldori[10][10], int z, int s, int maxz, int maxs) {
	int zahl = 0;

	for (int i = z - 1; i < z + 2; i++)
	{
		for (int j = s - 1; j < s + 2; j++)
		{
			if ((i == z) && (j == s) || (i < 0 || j < 0) || (i >= maxz || j >= maxs))
			{
				continue;
			}

			else
			{

				if (feldori[i][j] == '*')
				{
					zahl++;
				}

			}

		}
	}
	return zahl;
}

void ausgabe(char array[10][10], int maxz, int maxs)
{

	for (int i = 0; i < maxz; i++)
	{
		for (int j = 0; j < maxs; j++)
		{
			printf("%c", array[i][j]);

		}
		printf("\n");
	}
	printf("\n_________________________________________________________\n");
}

char array(char feldori[10][10], int maxz, int maxs)
{
	char feldgen[100][100] = { '*' };
	int nachbarn = 0;

	printf("Original:\n");
	ausgabe(feldori, maxz, maxs);

	for (int z = 0; z < maxz; z++)
		for (int s = 0; s < maxs; s++)
		{
			nachbarn = anzahlnachbarn(feldori, z, s, maxz, maxs);

			if (feldori[z][s] == '*')
			{
				if (nachbarn == 2 || nachbarn == 3)
				{
					feldgen[z][s] = '*';
				}
				else
				{
					feldgen[z][s] = ' ';
				}
			}
			else
			{
				if (feldori[z][s] == ' ' && nachbarn == 3)
				{
					feldgen[z][s] = '*';
				}
				else
				{
					feldgen[z][s] = ' ';
				}
			}

		}

	for (int i = 0; i < maxz; i++)
		for (int j = 0; j < maxs; j++)
		{
			feldori[i][j] = feldgen[i][j];
		}
	printf("Neachste:\n");
	ausgabe(feldori, maxz, maxs);

	return feldori;

}

char zufall(char feldori[10][10], int maxz, int maxs)
{
	int zufallart, count = 0,max;
	printf("Zufaelliger Startzustand:\n(0)komplett Zufall\n(1)Zufall mit Angabe lebendiger Zellen\n");
	scanf("%d", &zufallart);
	time_t t;
	srand((unsigned)time(&t));

	switch(zufallart)
	{
	case 0:
		for (int i = 0; i < maxz; i++)
		{
			for (int j = 0; j < maxs; j++)
			{
				int z = rand() % 2;

				if (z == 1)
				{
					feldori[i][j] = '*';
				}
				else
				{
					feldori[i][j] = ' ';
				}

			}

		}
		break;
	case 1:
		for (int i = 0; i < maxz; i++)
		{
			for (int j = 0; j < maxs; j++)
			{
				feldori[i][j] = ' ';

			}
		}
		printf("Wieviele Lebendige Zellen?\n");
		scanf("%d",&max);
		
		int randz,rands;
		
		while (count < max)
		{
			randz = (rand() % maxz), rands = (rand() % maxs);
			if (feldori[randz][rands] == '*')
			{
				continue;
			}
			else
			{
				feldori[randz][rands] = '*';
				count++;
			}
		}
		
		
		
		
		break;
	default: printf("Eingabe nicht erlaubt. Bitte (0) oder (1). %d ist falsch", zufallart);
		exit(1);
		break;
	}
	
}

char dateistart(char feldori[10][10], int maxz, int maxs)
{
	printf("Startzustand aus Datei:\n(0)eigene Datei\n(1)Startzustand 1\n(2)Startzustand 2\n(3)Startzustand 3\n");
	FILE *fp;
	char name[50];
	int fall;
	scanf("%d", &fall);

	switch (fall)
	{
	case 0:
		printf("Dateiname eingeben bitte:\n");
		scanf("%s", &name);
		fp = fopen(name,"rt");
		break;
	case 1:fp = fopen("startzustand1.txt", "r"); printf("Start1:\n"); break;
	case 2:fp = fopen("startzustand2.txt", "r"); printf("Start2:\n"); break;
	case 3:fp = fopen("startzustand3.txt", "r"); printf("Start3:\n"); break;
	default: printf("Die Eingabe: '%d' ist inkorrekt. Bitte (0), (1), (2) oder (3) eingeben.", fall); exit(1); break;
	}

	int temp;
	
	if (fp == NULL)
	{
		printf("Datei konnte nicht geoeffnet werden.\n");
		exit(2);
	}
	else 
	{
		int z;
		for (int i = 0; i < 10; i++) 
		{
			for (int j = 0; j < 10; j++)
			{
				z = fgetc(fp);
				if (z == EOF)
				{
					i = 10;
					break;
				}      
				feldori[i][j] = z;
			}
		}
		fclose(fp);
	}
	
	return feldori;
}

int main() {
	char feldori[10][10],c;
	int maxz = 10, maxs = 10;
	int eingabe2,t=3,ausgabeart;

	printf("Zufallsstart oder aus einer Datei?\n(0) fuer Zufall \n(1) fuer Datei\nIhre Eingabe: ");
	
	if (scanf("%d", &eingabe2) == 1)
	{



		if ((eingabe2 == 0) || (eingabe2 == 1))
		{
			if (eingabe2 == 0)
			{
				zufall(feldori, maxz, maxs);
			}
			else
			{
				dateistart(feldori, maxz, maxs);
			}
		}
		else
		{
			printf("Eingabe '%d' ist nicht gueltig. Entweder '0' oder '1'", eingabe2);
			return 1;
		}
	}
	else
	{
		printf("Eingabe '%d' ist nicht gueltig. Entweder '0' oder '1'", eingabe2);
		return 1;
	}



	printf("(0) Schrittweise Entwicklung der Population\n(1) flieszende Animation der Entwicklung\n");

	if (scanf("%d", &ausgabeart) == 1)
	{
		if ((ausgabeart == 0) || (ausgabeart == 1))
		{
			if (ausgabeart == 0)
			{
				while (t == 3)
				{
					printf("(Enter-Taste) fuer weiter\n(s) zum stoppen\n");
					scanf("%c", &c);
					if ((c == '\n') || (c == 's'))
					{
						if (c == '\n')
						{
							array(feldori, maxz, maxs);
						}
						else
						{
							break;
						}
					}
					else
					{
						printf("(%c) ist als Eingabe nicht zugelassen", c);
						continue;
					}
				}
			}
			else
			{
				while (t == 3)
				{
					array(feldori, maxz, maxs);
					Sleep(300);
				}
			}
		}
		else
		{
			printf("Falsche eingabe: '%d'", ausgabeart);
			return 2;
		}
	}
	else
	{
		printf("Falsche eingabe: '%d'", ausgabeart);
		return 2;
	}


	return 0;
}