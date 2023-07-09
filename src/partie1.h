/* Copyright (c) 2022 Corentin Beaulieu, Victor Schweisthal 

 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions: 

 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software. 

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE. */


#ifndef PARTIE1_H_INCLUDED
#define PARTIE1_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

// Enumeration des erreurs couvertes pour valeurs de retour
enum ERREUR {
	ERR_USAGE=1,
	ERR_OUV_FICHIER,
	ERR_ALLOC,
	ERR_TRANS_IMP,
	ERR_HORS_BANDE
};

// Structure d'une bande sous forme d'une liste doublement chainée
typedef struct Bande {
	char contenu;
	struct Bande *prec;
	struct Bande *suiv;
} bande;

// Structure d'une delta transition sous forme d'un quintuplet
typedef struct Delta {
	char etatDepart[8];
	char lettreLue;
	char etatArrivee[8];
	char lettreEc;
	enum Deplacement {
		droite,
		gauche,
		place
	} dep;
} delta;

// Structure d'une machine de Turing 
typedef struct MachineTuring {
	char etatCourant[8];
	bande* tete;
	uint16_t nbDeltas;
	delta *transitions;
	char etatFinal[8];
} MT;


MT Init_MT (const char *,const char *);

void Exec_Total(MT *, bool);

void Affiche_Bande (bande *);

void Ecriture_MT(MT *, const char *);

void Desalloc_MT(MT *);

#endif
