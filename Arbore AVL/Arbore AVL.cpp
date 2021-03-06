// Arbore AVL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#pragma warning(disable:4996)
using namespace std;

struct obiect
{
	int cod;
	char* denumire;
};

struct nodArb
{
	obiect inf;
	nodArb* left;
	nodArb* right;
	int GE;
};

nodArb* creare (obiect o, nodArb* left, nodArb* right)
{
	nodArb* nou = (nodArb*)malloc (sizeof (nodArb));
	nou->left = NULL;
	nou->right = NULL;
	nou->inf.cod = o.cod;
	nou->inf.denumire = (char*)malloc ((strlen (o.denumire) + 1) * sizeof (char));
	strcpy (nou->inf.denumire, o.denumire);
	return nou;
}

nodArb* inserare (nodArb* rad, obiect o)
{
	nodArb* aux = rad;
	if (rad == NULL)
	{
		aux = creare (o, NULL, NULL);
		return aux;
	}
	else
		while(true)
		if (o.cod < aux->inf.cod)
			if (aux->left == NULL)
			{
				aux->left = creare (o, NULL, NULL);
				return rad;
			}
			else
				aux = aux->left;
		else
			if (o.cod > aux->inf.cod)
				if (aux->right == NULL)
				{
					aux->right = creare (o, NULL, NULL);
					return rad;
				}
				else
					aux = aux->right;
			else
				return rad;
}

void traversare_preordine (nodArb* rad)
{
	if (rad != NULL)
	{
		printf ("\nCod: %d  Denumire: %s", rad->inf.cod, rad->inf.denumire);
		traversare_preordine (rad->left);
		traversare_preordine (rad->right);
		
	}
}


void traversare_inordine (nodArb* rad)
{
	if (rad != NULL)
	{
		traversare_inordine (rad->left);
		printf ("\nCod: %d  Denumire: %s", rad->inf.cod, rad->inf.denumire);
		traversare_inordine (rad->right);
	}
}

void traversare_postordine (nodArb* rad)
{
	if (rad != NULL)
	{
		traversare_postordine (rad->left);
		traversare_postordine (rad->right);
		printf ("\nCod: %d  Denumire: %s", rad->inf.cod, rad->inf.denumire);
	}
}


void dezalocare (nodArb* rad)
{
	if (rad != NULL)
	{
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		free (rad->inf.denumire);
		free (rad);
		dezalocare (st);
		dezalocare (dr);
	}
}

nodArb* cautare (nodArb* rad, int cod)
{
	if (rad != NULL)
		if (rad->inf.cod == cod)
			return rad;
		else
			if (cod < rad->inf.cod)
				return cautare (rad->left, cod);
			else
				return cautare (rad->right, cod);
	else
		return NULL;
}


int max (int a, int b)
{
	if (a > b)
		return a;
	return b;
}


int nrNiv (nodArb* rad)
{
	if (rad != NULL)
		return 1 + max (nrNiv (rad->left), nrNiv (rad->right));
	else
		return 0;
}

void calculGE (nodArb* rad)
{
	if (rad != NULL)
	{
		rad->GE = nrNiv (rad->right) - nrNiv (rad->left);
		calculGE (rad->left);
		calculGE (rad->right);
	}
}

nodArb* rotatie_dreapta (nodArb* rad)
{
	cout << endl << "Rotatie dreapta";
	nodArb* nod1 = rad->left;
	rad->left = nod1->right;
	nod1->right = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga (nodArb* rad)
{
	cout << endl << "Rotatie stanga";
	nodArb* nod1 = rad->right;
	rad->right = nod1->left;
	nod1->left = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga_dreapta (nodArb* rad)
{
	cout << endl << "Rotatie stanga dreapta";
	nodArb* nod1 = rad->left;
	nodArb* nod2 = nod1->right;
	nod1->right = nod2->left;
	nod2->left = nod1;
	rad->left = nod2->right;
	nod2->right = rad;
	rad = nod2;
	return rad;
}


nodArb* rotatie_dreapta_stanga (nodArb* rad)
{
	cout << endl << "Rotatie dreapta stanga";
	nodArb* nod1 = rad->right;
	nodArb* nod2 = nod1->left;
	nod1->left = nod2->right;
	nod2->right = nod1;
	rad->right = nod2->left;
	nod2->left = rad;
	rad = nod2;
	return rad;
}

int main()
{
	nodArb* rad = NULL;
	char buffer[20];
	obiect s;

	while (!feof (stdin))
	{
		cout << endl << endl;

		printf ("Cod: ");
		scanf ("%d", &s.cod);

		if (!feof (stdin))
		{
			printf ("Nume: ");
			cin.ignore ();
			cin.getline (buffer, 21);
			s.denumire = (char*)malloc ((strlen (buffer) + 1) * sizeof (char));
			strcpy (s.denumire, buffer);

		}

		rad = inserare (rad,s);

		calculGE (rad);
		if (rad->GE == -2 && rad->left->GE == -1)
		{
			rad = rotatie_dreapta (rad);
			calculGE (rad);
		}
		else
			if (rad->GE == 2 && rad->right->GE == 1)
			{
				rad = rotatie_stanga (rad);
				calculGE (rad);
			}
			else
				if (rad->GE == -2 && rad->right->GE == 1)
				{
					rad = rotatie_stanga_dreapta (rad);
					calculGE (rad);
				}
				else
					if (rad->GE == 2 && rad->right->GE == -1)
					{
						rad = rotatie_dreapta_stanga (rad);
						 calculGE (rad);
					}
	}

	printf ("\nCod: %d  Denumire: %s", rad->inf.cod, rad->inf.denumire);
	printf ("\n\nSubarbore stang:");
	traversare_inordine (rad->left);
	printf ("\n\nSubarbore drept:");
	traversare_inordine (rad->right);

	
	dezalocare (rad);

	cout << endl << endl;
	return 0;

}

