// eu_cd.cpp : Defines the entry point for the console application.
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

struct nodc
{
	nodc* next;
	obiect inf;
};

void put (nodc** prim, nodc** ultim, obiect p)
{
	nodc* nou = (nodc*)malloc (sizeof (nodc));

	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc ((strlen (p.denumire) + 1) * sizeof (char));
	strcpy (nou->inf.denumire, p.denumire);

	nou->next = NULL;

	if (*prim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

void get (nodc** prim, nodc** ultim, obiect *p)
{
	if (*prim != NULL)
	{
		(*p).cod = (*prim)->inf.cod;
		(*p).denumire = (char*)malloc ((strlen ((*prim)->inf.denumire) + 1) * sizeof (char));
		strcpy ((*p).denumire, (*prim)->inf.denumire);

		nodc* aux = *prim;
		*prim = (*prim)->next;

		free (aux->inf.denumire);
		free (aux);
	}

}

void traversare (nodc* cap)
{
	nodc* aux = cap;
	while (aux != NULL)
	{
		printf ("\nCod: %d  Denumire: %s", aux->inf.cod, aux->inf.denumire);
		aux = aux->next;
	}
}



int main ()
{
	int n;
	printf ("n: ");
	scanf ("%d", &n);

	obiect o;
	nodc* prim = NULL;
	nodc* ultim = NULL;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{

		printf ("Cod: ");
		scanf ("%d", &o.cod);
		cin.ignore ();
		printf ("Denumire:  ");
		cin.getline (buffer, 21);
		o.denumire = (char*)malloc ((strlen (buffer) + 1) * sizeof (char));
		strcpy (o.denumire, buffer);

		put (&prim,&ultim, o);
	}

	traversare (prim);

	cout << endl << endl;
	for (int i = 0; i < n; i++)
	{
		get (&prim, &ultim, &o);
		cout << o.cod << " ";
	}
	cout << endl << endl;
	return 0;
}


