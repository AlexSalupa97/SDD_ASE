// seminar8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#pragma warning(disable:4996)
using namespace std;

// structura heap - coada de prioritati
// maxheap - radacina are val. maxima
// minheap - analog
// fiu stanga - 2i+1
// fiu dreapta - 2i+2

struct heap
{
	int* vect;
	int nrElem;
};

struct student 
{
	int cod;
	char* nume;
	float medie;
};


void filtrare (heap h, int index)    // mapare pe student
{
	int indexMax = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt<h.nrElem&&h.vect[indexSt]>h.vect[indexMax])
		indexMax = indexSt;

	if (indexDr<h.nrElem&&h.vect[indexDr]>h.vect[indexMax])
		indexMax = indexDr;

	if (index != indexMax)
	{
		int temp = h.vect[index];
		h.vect[index] = h.vect[indexMax];
		h.vect[indexMax] = temp;

		filtrare (h, indexMax);
	}
}

void inserare (heap* h, int elem)
{
	int* vect = (int*)malloc (((*h).nrElem+1) * sizeof (int));
	for (int i = 0; i < (*h).nrElem; i++)
		vect[i] = h->vect[i];

	(*h).nrElem++;

	free ((*h).vect);

	(*h).vect = vect;

	(*h).vect[(*h).nrElem - 1] = elem;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--)
		filtrare (*h, i);
}


void extragere (heap *h, int * elem)
{
	int* vect = (int*)malloc (((*h).nrElem - 1) * sizeof (int));

	int temp = (*h).vect[0];
	(*h).vect[0] = (*h).vect[(*h).nrElem - 1];
	(*h).vect[(*h).nrElem - 1] = temp;

	*elem = (*h).vect[(*h).nrElem - 1];
	for (int i = 0; i < (*h).nrElem - 1; i++)
		vect[i] = (*h).vect[i];

	(*h).nrElem--;

	free ((*h).vect);
	(*h).vect = vect;
	
	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--)
		filtrare (*h, i);
}

void afisare (heap h)
{
	printf ("\n\nElemente heap: \n");
	for (int i = 0; i < h.nrElem; i++)	
		printf ("%d ", h.vect[i]);
}


int main()
{
	heap h;
	printf ("n: ");
	scanf ("%d", &h.nrElem);

	h.vect = (int*)malloc (h.nrElem * sizeof (int));

	for (int i = 0; i < h.nrElem; i++)
	{
		printf ("Element: ");
		scanf ("%d", &h.vect[i]);
	}

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare (h, i);

	afisare (h);
	inserare (&h, 50);
	afisare (h);

	int elem;
	extragere (&h, &elem);
	cout << endl << "Elem sters: " << elem;
	afisare (h);

	int* vectSortat = (int*)malloc (h.nrElem * sizeof (int));

	int n = h.nrElem;
	for (int i = 0; i < n; i++)
	{
		extragere (&h, &elem);
		vectSortat[i] = elem;
		
	}

	cout << endl << endl << "Vector sortat" << endl;
	for (int i = 0; i < n; i++)
		cout << vectSortat[i] << " "; // pentru sortare crescatoare, modificare in filtrare -> minheap

	free (vectSortat);

	cout << endl << endl;
    return 0;
}