
#ifndef PARTIE1_H_INCLUDED
#define PARTIE1_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct Bande {
	char contenu;
	struct Bande *prec;
	struct Bande *suiv;
} bande;

typedef struct Delta {
	char etatDepart;
	char lettreLue;
	char etatArrivee;
	char lettreEc;
	enum Deplacement {
		droite,
		gauche,
		place
	} dep;
} delta;

typedef struct MachineTuring {
	char etatCourant;
	bande* tete;
	uint16_t nbDeltas;
	delta *transitions;
	char etatFinal;
} MT;


MT Init_MT (const char *,const char *);

void Exec_Pas (MT *);

void Exec_Total(MT *);

void Affiche_Bande (bande *);

void Ecriture_MT(MT *, char *);

void Desalloc_MT(MT *);

#endif
