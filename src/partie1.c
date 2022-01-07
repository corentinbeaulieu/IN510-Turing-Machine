
#include "partie1.h"

bande *Init_Bande(char *mot) {
	bande *b, *prec;
	b = NULL;

	char lu;
	uint16_t i;
	i = 0;
	lu = mot[i];
	while(lu != '\0') {
		prec = b;
		b = malloc(sizeof(bande));
		if(!b) {
			//ERREUR
			exit(1);
		}
		b->contenu = lu;
		b->prec = prec;
		b->suiv = NULL;

		if(prec != NULL) prec->suiv = b;

		i++;
		lu = mot[i];
	}

	while(prec != NULL) {
		b = prec;
		prec = b->prec;
	}

	return b;
}


