// Lista Dubla.cpp : Defines the entry point for the console application.
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

struct nodld
{
	obiect inf;
	nodld* prev;
	nodld* next;
};

void inserare (nodld** cap, nodld** coada, obiect o)
{
	nodld* nou = (nodld*)malloc (sizeof (nodld));
	nou->next = NULL;
	nou->prev = NULL;
	nou->inf.cod = o.cod;
	nou->inf.denumire = (char*)malloc ((strlen (o.denumire) + 1) * sizeof (char));
	strcpy (nou->inf.denumire, o.denumire);

	if (*cap == NULL)
	{
		*cap = nou;
		*coada = nou;
	}
	else
	{
		nou->prev = *coada;
		(*coada)->next = nou;
		*coada = nou;
	}
}

void traversare (nodld* cap)
{
	nodld* aux = cap;
	while (aux != NULL)
	{
		printf ("\nCod: %d  Denumire: %s", aux->inf.cod, aux->inf.denumire);
		aux = aux->next;
	}
}

void dezalocare (nodld* cap, nodld* coada)
{
	if (cap != NULL)
	{
		nodld* temp = cap;
		while (temp != NULL)
		{
			if (cap->next == NULL)
			{
				nodld* aux = cap;
				free (aux->inf.denumire);
				free (aux);
				temp = NULL;
			}
			else
			{
				nodld* aux = temp->next;
				free (temp->inf.denumire);
				free (temp);
				temp = aux;
			}
		}
	}
}





void stergere (nodld** cap, nodld** coada, int cod)
{
	if (*cap != NULL)
	{
		nodld* temp = *cap;
		while (temp != NULL)
		{
			if (temp->inf.cod == cod && temp == *cap)
			{
				nodld* aux = temp;
				(*cap) = (*cap)->next;
				(*cap)->prev = NULL;
				free (aux->inf.denumire);
				free (aux);
				temp = *cap;
				break;
			}
			if (temp->inf.cod == cod && temp == *coada)
			{
				nodld* aux = temp;
				(*coada) = (*coada)->prev;
				(*coada)->next = NULL;
				free (aux->inf.denumire);
				free (aux);
				temp = NULL;
				break;
			}
			if (temp->inf.cod == cod)
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free (temp->inf.denumire);
				free (temp);
				break;
			}
			temp = temp->next;

		}
	}
}


void inserareSortata (nodld** cap, nodld** coada, obiect p)
{
	nodld* nou = (nodld*)malloc (sizeof (nodld));

	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc ((strlen (p.denumire) + 1) * sizeof (char));
	strcpy (nou->inf.denumire, p.denumire);

	nou->prev = NULL;
	nou->next = NULL;

	if (*cap == NULL)
	{
		*cap = nou;
		*coada = nou;
	}
	else
		if (nou->inf.cod < (*cap)->inf.cod)
		{
			nou->next = (*cap);
			(*cap)->prev = nou;
			(*cap) = nou;
		}
		else
			if (nou->inf.cod > (*coada)->inf.cod)
			{
				nou->prev = (*coada);
				(*coada)->next = nou;
				(*coada) = nou;
			}
			else
			{
				nodld* temp = *cap;
				while (temp->next == NULL && temp->next->inf.cod < nou->inf.cod)
					temp = temp->next;
				nou->next = temp->next;
				temp->next = nou;
				nou->prev = temp;
				
			}

}


int main()
{
	int n;
	printf ("n: ");
	scanf ("%d", &n);

	obiect o;
	nodld* cap = NULL;
	nodld* coada = NULL;
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

		inserareSortata (&cap, &coada, o);
	}

	stergere (&cap, &coada, 1);
	traversare (cap);
	dezalocare (cap, coada);

	cout << endl << endl;

    return 0;
}

