// Grafuri.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#pragma warning(disable:4996)
using namespace std;

struct nodls;

struct nodlp
{
	int nod;
	nodlp* next;
	nodls* vecini;
};

struct nodls
{
	int nod;
	nodls* next;
};

struct nodSt
{
	nodSt* next;
	int nod;
};

struct nodCd
{
	nodCd* next;
	int nod;
};

void push (nodSt** varf, int nod)
{
	nodSt* nou = (nodSt*)malloc (sizeof (nodSt));
	nou->next = NULL;
	nou->nod = nod;

	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

void pop (nodSt** varf, int* cod)
{
	if (*varf == NULL)
		return;
	else
	{
		nodSt* aux = *varf;
		*cod = (*varf)->nod;
		(*varf) = (*varf)->next;
		free (aux);

	}
}


void put (nodCd** prim, nodCd** ultim, int nod)
{
	nodCd* nou = (nodCd*)malloc (sizeof (nodCd));
	nou->next = NULL;
	nou->nod = nod;

	if (*prim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

void get (nodCd** prim, nodCd** ultim, int* nod)
{
	if (*prim == NULL)
		*ultim = NULL;
	else
	{
		nodCd* aux = *prim;
		*nod = aux->nod;
		*prim = (*prim)->next;
		free (aux);
	}
}


void inserareLS (nodls** ls, int nod)
{
	nodls* nou = (nodls*)malloc (sizeof (nodls));
	nou->next = NULL;
	nou->nod = nod;

	if (*ls == NULL)
		*ls = nou;
	else
	{
		nodls* temp = *ls;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
}


void inserareLP (nodlp** lp, nodls* vecini,int nod)
{
	nodlp* nou = (nodlp*)malloc (sizeof (nodlp));
	nou->next = NULL;
	nou->nod = nod;
	nou->vecini = vecini;

	if (*lp == NULL)
		*lp = nou;
	else
	{
		nodlp* temp = *lp;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
}


nodlp* cautaNodLP (nodlp* lp, int nod)
{
	nodlp* temp = lp;
	while (temp != NULL)
	{
		if (temp->nod == nod)
			return temp;
		temp = temp->next;
	}
	return NULL;
}



int main()
{
	int n;
	printf ("Nr noduri: ");
	scanf ("%d", &n);

	nodlp* lp = NULL;
	nodls* ls = NULL;

	for (int i = 1; i <= n; i++)
	{
		inserareLP (&lp, ls, i);
	}

	int ii, jj;
	while (!feof (stdin))
	{
		printf ("\n\nSursa: ");
		scanf ("%d", &ii);

		if (!feof (stdin))
		{
			printf ("Destinatia: ");
			scanf ("%d", &jj);
			if (ii <= n && jj <= n)
			{
				nodlp* cautat = cautaNodLP (lp, ii);
				nodls* vecini = cautat->vecini;
				inserareLS (&vecini, jj);
				cautat->vecini = vecini;
			}
		}


	}

	int* viz = (int*)malloc (n * sizeof (int));
	for (int i = 0; i < n; i++)
		viz[i] = 0;

	int nodPornire;

	printf ("\n\nParcurgere in adancime de la nodul (DF): ");
	scanf ("%d", &nodPornire);

	nodSt* varf = NULL;
	push (&varf, nodPornire);
	viz[nodPornire-1] = 1;

	while (varf != NULL)
	{
		pop (&varf, &nodPornire);
		printf ("%d", nodPornire);
		nodlp* cautat = cautaNodLP (lp, nodPornire);
		nodls* cautaLS = cautat->vecini;
		while (cautaLS != NULL)
		{
			if (viz[cautaLS->nod - 1] == 0)
			{
				push (&varf, cautaLS->nod);
				viz[cautaLS->nod - 1] = 1;
			}
			cautaLS = cautaLS->next;
		}

	}


	for (int i = 0; i < n; i++)
		viz[i] = 0;


	printf ("\n\nParcurgere in latime de la nodul (BF): ");
	scanf ("%d", &nodPornire);

	nodCd* prim = NULL;
	nodCd* ultim = NULL;
	put (&prim,&ultim, nodPornire);
	viz[nodPornire - 1] = 1;

	while (prim != NULL)
	{
		get (&prim,&ultim, &nodPornire);
		printf ("%d", nodPornire);
		nodlp* cautat = cautaNodLP (lp, nodPornire);
		nodls* cautaLS = cautat->vecini;
		while (cautaLS != NULL)
		{
			if (viz[cautaLS->nod - 1] == 0)
			{
				put (&prim, &ultim, cautaLS->nod);
				viz[cautaLS->nod - 1] = 1;
			}
			cautaLS = cautaLS->next;
		}

	}


	cout << endl << endl;
    return 0;
}

