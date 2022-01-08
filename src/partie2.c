
#include "partie2.h"


MT Question6 (const char *fichier) {
    MT mt;
    mt = Init_MT(fichier, "_");

    uint16_t i, j;
    uint16_t nbEtats; nbEtats = 0;
    char etats[32][8]; bool contenu; contenu = false;
    for(i=0; i < mt.nbDeltas; i++) {
        mt.transitions[i].etatDepart[0]++;
        mt.transitions[i].etatArrivee[0]++;

        for(j=0; j < nbEtats; j++) {
            if(!strcmp(mt.transitions[i].etatDepart, etats[j])) {
                contenu = true;
                break;
            }
        }
        if(!contenu) {
            strcpy(etats[nbEtats], mt.transitions[i].etatDepart);
            nbEtats++;
        }
        contenu = false;
    }

    mt.etatFinal[0]++;
    i = mt.nbDeltas;
    mt.nbDeltas += 10*(nbEtats + 1)-1;
    mt.transitions = realloc(mt.transitions, mt.nbDeltas*sizeof(delta));
    

    for(j=0; j < nbEtats; j++) {
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        mt.transitions[i].lettreLue = '*';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        strcat(mt.transitions[i].etatArrivee, "1");
        mt.transitions[i].lettreEc = '*';
        mt.transitions[i].dep = droite;
        i++;
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        strcat(mt.transitions[i].etatDepart, "1");
        mt.transitions[i].lettreLue = '0';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        strcat(mt.transitions[i].etatArrivee, "1");
        mt.transitions[i].lettreEc = '0';
        mt.transitions[i].dep = droite;
        i++;
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        strcat(mt.transitions[i].etatDepart, "1");
        mt.transitions[i].lettreLue = '1';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        strcat(mt.transitions[i].etatArrivee, "1");
        mt.transitions[i].lettreEc = '1';
        mt.transitions[i].dep = droite;
        i++;
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        strcat(mt.transitions[i].etatDepart, "1");
        mt.transitions[i].lettreLue = '_';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        strcat(mt.transitions[i].etatArrivee, "2");
        mt.transitions[i].lettreEc = '_';
        mt.transitions[i].dep = gauche;
        i++;
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        strcat(mt.transitions[i].etatDepart, "2");
        mt.transitions[i].lettreLue = '0';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        strcat(mt.transitions[i].etatArrivee, "3");
        mt.transitions[i].lettreEc = '_';
        mt.transitions[i].dep = droite;
        i++;
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        strcat(mt.transitions[i].etatDepart, "2");
        mt.transitions[i].lettreLue = '1';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        strcat(mt.transitions[i].etatArrivee, "4");
        mt.transitions[i].lettreEc = '_';
        mt.transitions[i].dep = droite;
        i++;
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        strcat(mt.transitions[i].etatDepart, "2");
        mt.transitions[i].lettreLue = '*';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        mt.transitions[i].lettreEc = '*';
        mt.transitions[i].dep = droite;
        i++;
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        strcat(mt.transitions[i].etatDepart, "3");
        mt.transitions[i].lettreLue = '_';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        strcat(mt.transitions[i].etatArrivee, "5");
        mt.transitions[i].lettreEc = '0';
        mt.transitions[i].dep = gauche;
        i++;
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        strcat(mt.transitions[i].etatDepart, "4");
        mt.transitions[i].lettreLue = '_';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        strcat(mt.transitions[i].etatArrivee, "5");
        mt.transitions[i].lettreEc = '1';
        mt.transitions[i].dep = gauche;
        i++;
        strcpy(mt.transitions[i].etatDepart, etats[j]);
        strcat(mt.transitions[i].etatDepart, "5");
        mt.transitions[i].lettreLue = '_';
        strcpy(mt.transitions[i].etatArrivee, etats[j]);
        strcat(mt.transitions[i].etatArrivee, "2");
        mt.transitions[i].lettreEc = '_';
        mt.transitions[i].dep = gauche;
        i++;
    }

    strcpy(mt.transitions[i].etatDepart, "A");
    mt.transitions[i].lettreLue = '0';
    strcpy(mt.transitions[i].etatArrivee, "A");
    mt.transitions[i].lettreEc = '0';
    mt.transitions[i].dep = droite;
    i++;
    strcpy(mt.transitions[i].etatDepart, "A");
    mt.transitions[i].lettreLue = '1';
    strcpy(mt.transitions[i].etatArrivee, "A");
    mt.transitions[i].lettreEc = '1';
    mt.transitions[i].dep = droite;
    i++;
    strcpy(mt.transitions[i].etatDepart, "A");
    mt.transitions[i].lettreLue = '_';
    strcpy(mt.transitions[i].etatArrivee, "A");
    strcat(mt.transitions[i].etatArrivee, "2");
    mt.transitions[i].lettreEc = '_';
    mt.transitions[i].dep = gauche;
    i++;
    strcpy(mt.transitions[i].etatDepart, "A");
    strcat(mt.transitions[i].etatDepart, "2");
    mt.transitions[i].lettreLue = '0';
    strcpy(mt.transitions[i].etatArrivee, "A");
    strcat(mt.transitions[i].etatArrivee, "3");
    mt.transitions[i].lettreEc = '_';
    mt.transitions[i].dep = droite;
    i++;
    strcpy(mt.transitions[i].etatDepart, "A");
    strcat(mt.transitions[i].etatDepart, "2");
    mt.transitions[i].lettreLue = '1';
    strcpy(mt.transitions[i].etatArrivee, "A");
    strcat(mt.transitions[i].etatArrivee, "4");
    mt.transitions[i].lettreEc = '_';
    mt.transitions[i].dep = droite;
    i++;
    strcpy(mt.transitions[i].etatDepart, "A");
    strcat(mt.transitions[i].etatDepart, "2");
    mt.transitions[i].lettreLue = '_';
    strcpy(mt.transitions[i].etatArrivee, "B");
    mt.transitions[i].lettreEc = '*';
    mt.transitions[i].dep = droite;
    i++;
    strcpy(mt.transitions[i].etatDepart, "A");
    strcat(mt.transitions[i].etatDepart, "3");
    mt.transitions[i].lettreLue = '_';
    strcpy(mt.transitions[i].etatArrivee, "A");
    strcat(mt.transitions[i].etatArrivee, "5");
    mt.transitions[i].lettreEc = '0';
    mt.transitions[i].dep = gauche;
    i++;
    strcpy(mt.transitions[i].etatDepart, "A");
    strcat(mt.transitions[i].etatDepart, "4");
    mt.transitions[i].lettreLue = '_';
    strcpy(mt.transitions[i].etatArrivee, "A");
    strcat(mt.transitions[i].etatArrivee, "5");
    mt.transitions[i].lettreEc = '1';
    mt.transitions[i].dep = gauche;
    i++;
    strcpy(mt.transitions[i].etatDepart, "A");
    strcat(mt.transitions[i].etatDepart, "5");
    mt.transitions[i].lettreLue = '_';
    strcpy(mt.transitions[i].etatArrivee, "A");
    strcat(mt.transitions[i].etatArrivee, "2");
    mt.transitions[i].lettreEc = '_';
    mt.transitions[i].dep = gauche;
    i++;

    return mt;
}

MT Question7 (const char *fichier) {
    printf("Question 7\n");
    abort();
}