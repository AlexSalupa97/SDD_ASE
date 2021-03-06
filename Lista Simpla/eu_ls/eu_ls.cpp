// eu_ls.cpp : Defines the entry point for the console application.
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

struct nodls
{
	nodls* next;
	obiect inf;
};

void inserare (nodls** cap, obiect p)
{
	nodls* nou = (nodls*)malloc (sizeof (nodls));

	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc ((strlen (p.denumire) + 1) * sizeof (char));
	strcpy (nou->inf.denumire, p.denumire);

	nou->next = NULL;

	if (*cap == NULL)
		*cap = nou;
	else
	{
		nodls* aux = *cap;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nou;
	}
}

void traversare (nodls* cap)
{
	nodls* aux = cap;
	while (aux != NULL)
	{
		printf ("\nCod: %d  Denumire: %s", aux->inf.cod, aux->inf.denumire);
		aux = aux->next;
	}
}

void dezalocare (nodls* cap)
{
	if (cap != NULL)
	{
		nodls* temp = cap;
		while (temp != NULL)
		{
			nodls* aux = temp->next;
			free (temp->inf.denumire);
			free (temp);
			temp = aux;
		}
	}
}

void inserareSortata (nodls** cap, obiect p)
{
	nodls* nou = (nodls*)malloc (sizeof (nodls));

	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc ((strlen (p.denumire) + 1) * sizeof (char));
	strcpy (nou->inf.denumire, p.denumire);

	nou->next = NULL;

	if (*cap == NULL)
		*cap = nou;
	else
		if (nou->inf.cod < (*cap)->inf.cod)
		{
			nou->next = (*cap);
			*cap = nou;
		}
		else
		{
			nodls* temp = *cap;
			if (temp->next != NULL && temp->next->inf.cod < nou->inf.cod)
				temp = temp->next;
			nou->next = temp->next;
			temp->next = nou;
		}
}

void stergere (nodls**cap, int cod)
{
	if (*cap != NULL)
	{
		nodls* temp = *cap;
		while (temp != NULL)
		{
			if (temp->inf.cod == cod)
				if (temp == *cap)
				{
					nodls* aux = temp;
					*cap = aux->next;
					temp = temp->next;
					free (aux->inf.denumire);
					free (aux);
				}
				else
				{
					nodls* aux = *cap;
					while (aux->next != temp)
						aux = aux->next;
					aux->next = temp->next;
					free (temp->inf.denumire);
					free (temp);
				}
			temp = temp->next;
		}
	}
}

int main ()
{
	FILE* f;
	f = fopen ("fisier.txt", "r");

	char* token, sir[100], sep[] = ",";

	obiect o;
	nodls* cap = NULL;
	char buffer[20];

	while (fgets (sir, 101, f))
	{
		token = strtok (sir, sep);
		o.cod = atoi (token);

		token = strtok (0, sep);
		o.denumire = (char*)malloc ((strlen (token) + 1) * sizeof (char));
		strcpy (o.denumire, token);
		

		inserareSortata (&cap, o);
	}

	stergere (&cap, 1);
	traversare (cap);
	dezalocare (cap);

	cout << endl << endl;
	return 0;
}



