#ifndef _NOEUD_C_
#define _NOEUD_C_

#include<stdlib.h>
#include<stdio.h>
#include"noeud.h"

arbre creer_feuille(int * tab, int index){
  arbre resultat ;
  resultat = malloc(sizeof(noeud));
  if(!resultat){
    printf("Erreur d'allocation\n");
    return resultat;
  }
  resultat->caractere = (char) index;
  resultat->occurence = tab[index];
  resultat->taillecode =-1;
  resultat->code =-1;
  resultat->fils_droit = NULL;
  resultat->fils_gauche = NULL;
  return resultat;
}

#endif
