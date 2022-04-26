#ifndef _NOEUD_C_
#define _NOEUD_C_

#include<stdlib.h>
#include<stdio.h>
#include"noeud.h"
#include"tableau.h"

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

void creer_noeud(arbre tab[], int taille){
  int i=0,j=0;
  while(i<(taille*2)-1){
    tab[taille+j]=malloc(sizeof(noeud));
    if(!tab[taille+j]){
      printf("Erreur d'allocation\n");
      return;
    }
    tab[taille+j]->occurence=tab[i]->occurence+tab[i+1]->occurence;
    tab[taille+j]->fils_gauche=tab[i];
    tab[taille+j]->fils_droit=tab[i+1];
    i+=2;
    j++;
    trierTableauArbre(tab,taille+j);
  }
  return;
}

int est_feuille(arbre a){
  if(a->fils_droit || a->fils_gauche){
    return 0;
  }
  else{
    return 1;
  }
}

int concat(int x, int y){
  int tmp=y;
  while(y){
    x*=10;
    y/=10;
  }
  return x+tmp;
}

void affichage_code(int nbr_bits, int codage){
  printf("nbr_bits = %d\n",nbr_bits);
  int tmp = codage, taille=1;
  while(tmp>9){
    tmp/=10;
    taille++;
  }
  for(tmp=0;tmp<nbr_bits-taille;tmp++){
    printf("0");
  }
  printf("%d", codage);
  return;
}

void creer_code(arbre element, int code, int profondeur){
  if(est_feuille(element)){
    element->taillecode=profondeur;
    element->code=code;
    affichage_code(element->taillecode, element->code);
  }
  else{
    creer_code(element->fils_gauche,concat(code,0),profondeur+1);
    creer_code(element->fils_droit,concat(code,1),profondeur+1);
  }
  return;
}

#endif
