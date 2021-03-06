// eu_stv.cpp : Defines the entry point for the console application.
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

struct nodst
{
	nodst* next;
	obiect inf;
};

void push (nodst** varf, obiect p)
{
	nodst* nou = (nodst*)malloc (sizeof (nodst));

	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc ((strlen (p.denumire) + 1) * sizeof (char));
	strcpy (nou->inf.denumire, p.denumire);

	nou->next = NULL;

	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

void traversare (nodst* varf)
{
	nodst* aux = varf;
	while (aux != NULL)
	{
		printf ("\nCod: %d  Denumire: %s", aux->inf.cod, aux->inf.denumire);
		aux = aux->next;
	}

}

void pop (nodst** varf, obiect* p)
{
	if (*varf != NULL)
	{
		(*p).cod = (*varf)->inf.cod;
		(*p).denumire = (char*)malloc ((strlen ((*varf)->inf.denumire) + 1) * sizeof (char));
		strcpy ((*p).denumire, (*varf)->inf.denumire);

		nodst* aux = *varf;
		*varf = (*varf)->next;

		free (aux->inf.denumire);
		free (aux);
	}
}


int main ()
{
	int n;
	printf ("n: ");
	scanf ("%d", &n);

	obiect o;
	nodst* varf = NULL;
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

		push (&varf, o);
	}

	traversare (varf);

	cout << endl << endl;
	for (int i = 0; i < n; i++)
	{
		pop (&varf, &o);
		cout << o.cod;
	}

	cout << endl << endl;
	return 0;
}
