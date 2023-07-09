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


#include "partie2.h"

// Fonction réduisant le code d'une machine sur ruban bi infini vers une machine sur ruban infini à droite
MT Question6 (const char *fichier) {
    MT mt;
    mt = Init_MT(fichier, "_");

    uint16_t i, j;
    uint16_t nbEtats; nbEtats = 0;
    char etats[32][8];
    bool contenu; contenu = false;
    char final[8];

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
    strcpy(final, mt.etatFinal);
    strcpy(mt.etatFinal, "nvFinal");

    i = mt.nbDeltas;
    //Pour chaque état non final on ajoute 10 transitions. On aujoute 19 transitions de plus.
    mt.nbDeltas += 10*(nbEtats + 2)-1;
    mt.transitions = realloc(mt.transitions, mt.nbDeltas*sizeof(delta));
    

    for(j=0; j < nbEtats; j++) {
        //Pour chaque états on rajoute des transitions permettant un décalage d'une case sur la droite de tout le mot
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

    // Le premier état décale tout le mot d'entrée d'une case sur la droite et écrit * dans la première case
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

    // L'avant dernier état supprime la première lettre * et décale tout le mot d'une case sur la gauche
    strcpy(mt.transitions[i].etatDepart, final);
    mt.transitions[i].lettreLue = '0';
    strcpy(mt.transitions[i].etatArrivee, final);
    mt.transitions[i].lettreEc = '0';
    mt.transitions[i].dep = gauche;
    i++;
    strcpy(mt.transitions[i].etatDepart, final);
    mt.transitions[i].lettreLue = '1';
    strcpy(mt.transitions[i].etatArrivee, final);
    mt.transitions[i].lettreEc = '1';
    mt.transitions[i].dep = gauche;
    i++;
    strcpy(mt.transitions[i].etatDepart, final);
    mt.transitions[i].lettreLue = '*';
    strcpy(mt.transitions[i].etatArrivee, final);
    strcat(mt.transitions[i].etatArrivee, "1");
    mt.transitions[i].lettreEc = '*';
    mt.transitions[i].dep = droite;
    i++;
    strcpy(mt.transitions[i].etatDepart, final);
    strcat(mt.transitions[i].etatDepart, "1");
    mt.transitions[i].lettreLue = '*';
    strcpy(mt.transitions[i].etatArrivee, final);
    strcat(mt.transitions[i].etatArrivee, "1");
    mt.transitions[i].lettreEc = '*';
    mt.transitions[i].dep = droite;
    i++;
    strcpy(mt.transitions[i].etatDepart, final);
    strcat(mt.transitions[i].etatDepart, "1");
    mt.transitions[i].lettreLue = '0';
    strcpy(mt.transitions[i].etatArrivee, final);
    strcat(mt.transitions[i].etatArrivee, "2");
    mt.transitions[i].lettreEc = '*';
    mt.transitions[i].dep = gauche;
    i++;
    strcpy(mt.transitions[i].etatDepart, final);
    strcat(mt.transitions[i].etatDepart, "1");
    mt.transitions[i].lettreLue = '1';
    strcpy(mt.transitions[i].etatArrivee, final);
    strcat(mt.transitions[i].etatArrivee, "3");
    mt.transitions[i].lettreEc = '*';
    mt.transitions[i].dep = gauche;
    i++;
    strcpy(mt.transitions[i].etatDepart, final);
    strcat(mt.transitions[i].etatDepart, "1");
    mt.transitions[i].lettreLue = '_';
    strcpy(mt.transitions[i].etatArrivee, final);
    strcat(mt.transitions[i].etatArrivee, "4");
    mt.transitions[i].lettreEc = '_';
    mt.transitions[i].dep = gauche;
    i++;
    strcpy(mt.transitions[i].etatDepart, final);
    strcat(mt.transitions[i].etatDepart, "2");
    mt.transitions[i].lettreLue = '*';
    strcpy(mt.transitions[i].etatArrivee, final);
    strcat(mt.transitions[i].etatArrivee, "1");
    mt.transitions[i].lettreEc = '0';
    mt.transitions[i].dep = droite;
    i++;
    strcpy(mt.transitions[i].etatDepart, final);
    strcat(mt.transitions[i].etatDepart, "3");
    mt.transitions[i].lettreLue = '*';
    strcpy(mt.transitions[i].etatArrivee, final);
    strcat(mt.transitions[i].etatArrivee, "1");
    mt.transitions[i].lettreEc = '1';
    mt.transitions[i].dep = droite;
    i++;
    strcpy(mt.transitions[i].etatDepart, final);
    strcat(mt.transitions[i].etatDepart, "4");
    mt.transitions[i].lettreLue = '*';
    strcpy(mt.transitions[i].etatArrivee, mt.etatFinal);
    mt.transitions[i].lettreEc = '_';
    mt.transitions[i].dep = gauche;
    i++;
    

    return mt;
}

// Fonction réduisant le code d'une machine sur l'alphabet {a,b,c,d} vers une machine sur l'alphabet {0,1}
MT Question7 (const char *fichier) {
    MT mt;
    mt = Init_MT(fichier, "_");

    int m = 14;
    int nbDelta = m*mt.nbDeltas;
    //Et on y ajoute toutes les transitions de la machine à simuler
    delta *trans = malloc(sizeof(delta) * nbDelta);

    for (int i = 0; i < mt.nbDeltas; i++) {

        //A -> A0 ou A1
        strcpy(trans[m*i].etatDepart,mt.transitions[i].etatDepart);
        strcpy(trans[m*i].etatArrivee,mt.transitions[i].etatDepart);
        //A0
        if((mt.transitions[i].lettreLue == 'a') || (mt.transitions[i].lettreLue == 'b')) {
            trans[m*i].lettreLue = '0';
            strcat(trans[m*i].etatArrivee,"0"); 
            trans[m*i].lettreEc = '0';
        } 
        //A1
        else if((mt.transitions[i].lettreLue == 'c') || (mt.transitions[i].lettreLue == 'd')){
            trans[m*i].lettreLue = '1';
            strcat(trans[m*i].etatArrivee,"1");
            trans[m*i].lettreEc = '1';
        } 
        else {
            trans[m*i].lettreLue = '_';
            strcat(trans[m*i].etatArrivee,"_");
            trans[m*i].lettreEc = '_';
        }
        trans[m*i].dep = droite;



        //A0 ou A1 -> A00 ou A01 ou A10 ou A11
        strcpy(trans[m*i+1].etatDepart,trans[m*i].etatArrivee);

        strcpy(trans[m*i+1].etatArrivee,trans[m*i+1].etatDepart); 
        //A00 ou A10
        if((mt.transitions[i].lettreLue == 'a') || (mt.transitions[i].lettreLue == 'c')) {
            trans[m*i+1].lettreLue = '0';
            strcat(trans[m*i+1].etatArrivee,"0");
            trans[m*i+1].lettreEc = '0';
        } 
        //A01 ou A11
        else if((mt.transitions[i].lettreLue == 'b') || (mt.transitions[i].lettreLue == 'd')) {
            trans[m*i+1].lettreLue = '1';
            strcat(trans[m*i+1].etatArrivee,"1");
            trans[m*i+1].lettreEc = '1';
        } else {
            trans[m*i+1].lettreLue = '_';
            strcat(trans[m*i+1].etatArrivee,"_");
            trans[m*i+1].lettreEc = '_';
        }
        trans[m*i+1].dep = place;



        //On traduit la transition de base par nos nouvelles transitions
        //la première contient les instructions suivantes dans son nom i.e. "0>>A" puis ">>A" ">A" A
        strcpy(trans[m*i+2].etatDepart, trans[m*i+1].etatArrivee);
        trans[m*i+2].lettreLue = '0';
        if((mt.transitions[i].lettreEc == 'a') || (mt.transitions[i].lettreEc == 'c')) {
            trans[m*i+2].lettreEc = '0';
        } 
        else if((mt.transitions[i].lettreEc == 'b') || (mt.transitions[i].lettreEc == 'd')) {
            trans[m*i+2].lettreEc = '1';
        } 
        else {
            trans[m*i+2].lettreEc = '_';
        }
        trans[m*i+2].dep = gauche;

        if((mt.transitions[i].lettreEc == 'a') || (mt.transitions[i].lettreEc == 'b')) {
            strcpy(trans[m*i+2].etatArrivee, "0");
        } else if((mt.transitions[i].lettreEc == 'c') || (mt.transitions[i].lettreEc == 'd')) {
            strcpy(trans[m*i+2].etatArrivee, "1");
        }
        else {
            strcpy(trans[m*i+2].etatArrivee, "_");
        }
        switch(mt.transitions[i].dep) {
            case droite:
                strcat(trans[m*i+2].etatArrivee, ">>");
                break;
            case gauche:
                strcat(trans[m*i+2].etatArrivee, "<<");
                break;
            case place:
                strcat(trans[m*i+2].etatArrivee, "--");
                break;
        }
        strcat(trans[m*i+2].etatArrivee, mt.transitions[i].etatArrivee);



        strcpy(trans[m*i+3].etatDepart, trans[m*i+2].etatArrivee);
        trans[m*i+3].lettreLue = '0';
        trans[m*i+3].lettreEc = trans[m*i+3].etatDepart[0];
        strcpy(trans[m*i+3].etatArrivee, trans[m*i+3].etatDepart);
        trans[m*i+3].dep = place;
        memmove(trans[m*i+3].etatArrivee, trans[m*i+3].etatArrivee+1, 8);

        strcpy(trans[m*i+4].etatDepart, trans[m*i+3].etatArrivee);
        trans[m*i+4].lettreLue = '0';
        trans[m*i+4].lettreEc = '0';
        strcpy(trans[m*i+4].etatArrivee, trans[m*i+4].etatDepart);
        switch(trans[m*i+4].etatDepart[0]) {
            case '>':
                trans[m*i+4].dep = droite;
                break;
            case '<':
                trans[m*i+4].dep = place;
                break;
            case '-':
                trans[m*i+4].dep = place;
                break;
        }
        memmove(trans[m*i+4].etatArrivee, trans[m*i+4].etatArrivee+1, 8);


        strcpy(trans[m*i+5].etatDepart, trans[m*i+4].etatArrivee);
        trans[m*i+5].lettreLue = '0';
        trans[m*i+5].lettreEc = '0';
        strcpy(trans[m*i+5].etatArrivee, trans[m*i+5].etatDepart);
        switch(trans[m*i+5].etatDepart[0]) {
            case '>':
                trans[m*i+5].dep = droite;
                break;
            case '<':
                trans[m*i+5].dep = gauche;
                break;
            case '-':
                trans[m*i+5].dep = place;
                break;
        }
        memmove(trans[m*i+5].etatArrivee, trans[m*i+5].etatArrivee+1, 8);

        for (int j = 0; j < 4; j++) {
            strcpy(trans[m*i+6+j].etatDepart,trans[m*i+2+j].etatDepart);
            trans[m*i+6+j].lettreLue = '1';
            strcpy(trans[m*i+6+j].etatArrivee,trans[m*i+2+j].etatArrivee);
            if (j < 2)
                trans[m*i+6+j].lettreEc = trans[m*i+2+j].lettreEc;
            else
                trans[m*i+6+j].lettreEc = '1';
            trans[m*i+6+j].dep = trans[m*i+2+j].dep;

            strcpy(trans[m*i+10+j].etatDepart,trans[m*i+2+j].etatDepart);
            trans[m*i+10+j].lettreLue = '_';
            strcpy(trans[m*i+10+j].etatArrivee,trans[m*i+2+j].etatArrivee);
            if (j < 2)
                trans[m*i+10+j].lettreEc = trans[m*i+2+j].lettreEc;
            else
                trans[m*i+10+j].lettreEc = '_';
            trans[m*i+10+j].dep = trans[m*i+2+j].dep;
        }
    }


    mt.nbDeltas = nbDelta;
    mt.transitions = trans;
    return mt;
}
