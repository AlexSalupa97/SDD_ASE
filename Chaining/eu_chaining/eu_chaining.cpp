// eu_chaining.cpp : Defines the entry point for the console application.
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

struct hashT
{
	nodls** vect;
	int size;
};

int functieHash (hashT tabela, int cheie)
{
	return cheie % tabela.size;
}

void inserare (hashT tabela, obiect p)
{
	int pozitie;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash (tabela, p.cod);

		nodls* nou = (nodls*)malloc (sizeof (nodls));

		nou->inf.cod = p.cod;
		nou->inf.denumire = (char*)malloc ((strlen (p.denumire) + 1) * sizeof (char));
		strcpy (nou->inf.denumire, p.denumire);

		nou->next = NULL;

		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else
		{
			nodls* temp = tabela.vect[pozitie];
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = nou;
		}

	}

}

void traversare (hashT tabela)
{
	if(tabela.vect!=NULL)
		for(int i=0;i<tabela.size;i++)
			if (tabela.vect[i] != NULL)
			{
				cout << endl << "Pozitia " << i;
				nodls* aux = tabela.vect[i];
				while (aux != NULL)
				{
					printf ("\nCod: %d  Denumire: %s", aux->inf.cod, aux->inf.denumire);
					aux = aux->next;

				}
			}
}

void dezalocare (hashT tabela)
{
	if (tabela.vect != NULL)
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vect[i] != NULL)
			{
				nodls* temp = tabela.vect[i];
				while (temp != NULL)
				{
					nodls* aux = temp->next;
					free (temp->inf.denumire);
					free (temp);
					temp = aux;
				}
			}
	free (tabela.vect);
}

void stergere (hashT tabela, int cod)
{
	int pozitie;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash (tabela, cod);
		if(tabela.vect[pozitie]!=NULL)
			if (tabela.vect[pozitie]->inf.cod == cod && tabela.vect[pozitie]->next == NULL)
			{
				nodls* temp = tabela.vect[pozitie];
				free (temp->inf.denumire);
				free (temp);
				tabela.vect[pozitie] = NULL;
			}
			else
				if (tabela.vect[pozitie]->inf.cod == cod)
				{
					nodls* temp = tabela.vect[pozitie];
					tabela.vect[pozitie] = tabela.vect[pozitie]->next;
					free (temp->inf.denumire);
					free (temp);
				}
				else
				{
					nodls* temp = tabela.vect[pozitie];
					while (temp->next != NULL && temp->next->inf.cod != cod)
						temp = temp->next;
					nodls* aux = temp->next;
					if (aux->next != NULL)
					{
						temp->next = aux->next;
						free (aux->inf.denumire);
						free (aux);
					}
					else
					{
						temp->next = NULL;
						free (aux->inf.denumire);
						free (aux);
					}

				}
	}
}


int main()
{
	int n;
	printf ("n: ");
	scanf ("%d", &n);

	hashT tabela;
	tabela.size = 101;
	tabela.vect = (nodls**)malloc (tabela.size * sizeof (nodls*));
	for (int i = 0; i < tabela.size; i++)
		tabela.vect[i] = NULL;

	obiect o;
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

		inserare (tabela, o);
	}

	stergere (tabela, 1);
	traversare (tabela);
	dezalocare (tabela);


	cout << endl << endl;
    return 0;
}

