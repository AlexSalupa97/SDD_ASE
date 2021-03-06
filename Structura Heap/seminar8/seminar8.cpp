﻿// seminar8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#pragma warning (disable:4996)
using namespace std;

struct obiect
{
	int cod;
	char* denumire;
};

struct heap
{
	obiect* vect;
	int nrElem;
};

void filtrare (heap h, int index)
{
	int indexMax = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt<h.nrElem&&h.vect[indexSt].cod>h.vect[indexMax].cod)
		indexMax = indexSt;
	if (indexDr<h.nrElem&&h.vect[indexDr].cod>h.vect[indexMax].cod)
		indexMax = indexDr;
	if (index != indexMax)
	{
		obiect o = h.vect[index];
		h.vect[index] = h.vect[indexMax];
		h.vect[indexMax] = o;

		filtrare (h, indexMax);
	}

}

void inserare (heap* h, obiect o)
{
	obiect* vect = (obiect*)malloc (((*h).nrElem + 1) * sizeof (obiect));

	for (int i = 0; i < (*h).nrElem; i++)
		vect[i] = (*h).vect[i];

	(*h).nrElem++;
	free ((*h).vect);
	(*h).vect = vect;
	(*h).vect[(*h).nrElem - 1] = o;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--)
		filtrare (*h, i);
}

void afisare (heap h)
{
	printf ("\n\nElemente heap: \n");
	for (int i = 0; i < h.nrElem; i++)
		printf ("\nCod: %d  Denumire: %s", h.vect[i].cod, h.vect[i].denumire);

}

void extragere (heap* h, obiect* o)
{
	obiect* vect = (obiect*)malloc (((*h).nrElem - 1) * sizeof (obiect));
	obiect temp = (*h).vect[0];
	(*h).vect[0] = (*h).vect[(*h).nrElem - 1];
	(*h).vect[(*h).nrElem - 1] = temp;

	*o = (*h).vect[(*h).nrElem - 1];
	for (int i = 0; i < (*h).nrElem-1; i++)
		vect[i] = (*h).vect[i];

	free ((*h).vect);
	(*h).nrElem--;
	(*h).vect = vect;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i -- )
		filtrare (*h, i);
}


int main()
{
	heap h;
	printf ("n: ");
	scanf ("%d", &h.nrElem);
	char buffer[20];

	h.vect = (obiect*)malloc (h.nrElem * sizeof (obiect));

	for (int i = 0; i < h.nrElem; i++)
	{
		printf ("Cod: ");
		scanf ("%d", &h.vect[i].cod);
		cin.ignore ();
		printf ("Denumire:  ");
		cin.getline (buffer, 21);
		h.vect[i].denumire = (char*)malloc ((strlen (buffer) + 1) * sizeof (char));
		strcpy (h.vect[i].denumire, buffer);

	}

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare (h, i);

	
	afisare (h);

	obiect o;
	o.cod = 5;
	o.denumire = (char*)malloc (2 * sizeof (char));
	strcpy (o.denumire, "5");
	
	inserare (&h, o);
	afisare (h);

	obiect o1;
	extragere (&h, &o1);
	cout << endl << "Elem sters: " << o1.cod;
	afisare (h);

	obiect* vectSortat = (obiect*)malloc (h.nrElem * sizeof (obiect));

	int n = h.nrElem;
	for (int i = 0; i < n; i++)
	{
		extragere (&h, &o1);
		vectSortat[i] = o1;

	}

	cout << endl << endl << "Arbore parcurs: ";
	for (int i = 0; i < n; i++)
		cout << vectSortat[i].cod<<" ";

	free (vectSortat);

	cout << endl << endl;
	return 0;


}
