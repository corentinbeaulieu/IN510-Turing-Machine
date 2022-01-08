
#ifndef PARTIE1_H_INCLUDED
#define PARTIE1_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

enum ERREUR {
	ERR_USAGE=1,
	ERR_OUV_FICHIER,
	ERR_ALLOC,
	ERR_TRANS_IMP,
	ERR_HORS_BANDE
};


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

void Exec_Total(MT *, bool);

void Affiche_Bande (bande *);

void Ecriture_MT(MT *, const char *);

void Desalloc_MT(MT *);

#endif
