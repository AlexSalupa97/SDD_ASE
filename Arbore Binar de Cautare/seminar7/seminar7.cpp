// seminar7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#pragma warning(disable:4996)
using namespace std;

// preordine (Radacina, Stanga, Dreapta)
// inordine (S,R,D)
// postordine (S,D,R)

struct student
{
	int cod;
	char* nume;
	float medie;
};
struct nodArb
{
	student inf;
	nodArb* left;
	nodArb* right;
};

nodArb* creare (student s, nodArb* left, nodArb* right)
{
	nodArb* nou = (nodArb*)malloc (sizeof (nodArb));
	nou->inf.cod = s.cod;
	nou->inf.medie = s.medie;
	nou->inf.nume = (char*)malloc ((strlen (s.nume) + 1) * sizeof (char));
	strcpy (nou->inf.nume, s.nume);

	nou->left = left;
	nou->right = right;

	return nou;
}

nodArb* inserare (student s, nodArb* rad) //radacina
{
	nodArb* aux = rad;
	if (rad == NULL)
	{
		aux = creare (s, NULL, NULL);
		return aux;
	}
	else
	{
		while (true)
		{
			if (s.cod < aux->inf.cod)
				if (aux->left != NULL)
					aux = aux->left;
				else
				{
					aux->left = creare (s, NULL, NULL);
					return rad;
				}
			else
				if (s.cod > aux->inf.cod)
					if (aux->right != NULL)
						aux = aux->right;
					else
					{
						aux->right = creare (s, NULL, NULL);
						return rad;
					}
				else
					return rad;
		}
	}
}

void traversare_preordine (nodArb* rad)
{
	if (rad != NULL)
	{
		cout << endl << endl;
		printf ("Cod: %d Nume: %s Medie: %f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
		traversare_preordine (rad->left);
		traversare_preordine (rad->right);
	}
}
void traversare_inordine (nodArb* rad)
{
	if (rad != NULL)
	{
		traversare_inordine (rad->left);
		cout << endl << endl;
		printf ("Cod: %d Nume: %s Medie: %f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
		traversare_inordine (rad->right);
	}
}
void traversare_postordine (nodArb* rad)
{
	if (rad != NULL)
	{
		traversare_postordine (rad->left);
		traversare_postordine (rad->right);
		cout << endl << endl;
		printf ("Cod: %d Nume: %s Medie: %f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
		
	}
}

void dezalocare (nodArb* rad)
{
	if (rad != NULL)
	{
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		free (rad->inf.nume);
		free (rad);
		dezalocare (st);
		dezalocare (dr);
	}
}

nodArb* cautare (nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->inf.cod)
			return rad;
		else
			if (cheie < rad->inf.cod)
				return cautare (rad->left, cheie);
			else
				return cautare (rad->right, cheie);
	}
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

void conversieArboreVector (nodArb* rad, student* vect, int *n)
{
	if (rad != NULL)
	{
		vect[*n] = rad->inf;
		(*n)++;
		conversieArboreVector (rad->left, vect, n);
		conversieArboreVector (rad->right, vect, n);
	}
}

int main()
{
	int n;
	printf ("n: ");
	scanf ("%d", &n);

	nodArb* rad = NULL;
	char buffer[20];
	student s;

	for (int i = 0; i < n; i++)
	{
		cout << endl << endl;

		printf ("Cod: ");
		scanf ("%d", &s.cod);

		printf ("Nume: ");
		cin.ignore ();
		cin.getline (buffer, 21);
		s.nume = (char*)malloc ((strlen (buffer) + 1) * sizeof (char));
		strcpy (s.nume, buffer);

		printf ("Medie: ");
		scanf ("%f", &s.medie);

		rad = inserare (s, rad);
	}

	traversare_inordine (rad);

	cout << endl << endl;
	nodArb* cautat = NULL;
	cautat = cautare (rad, 2);
	printf ("Studentul cautat: %s", cautat->inf.nume);

	printf ("%d niveluri", nrNiv (rad));

	student* vect = (student*)malloc (n * sizeof (student));
	int nr = 0;
	conversieArboreVector (rad, vect, &nr);



	free (vect);
	dezalocare (rad);

	cout << endl << endl;
    return 0;
}

