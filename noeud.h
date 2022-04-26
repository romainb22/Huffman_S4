#ifndef _NOEUD_H_
#define _NOEUD_H_

typedef struct noeud{
  char caractere;
  int occurence;
  int code;
  int taillecode;
  struct noeud * fils_gauche;
  struct noeud * fils_droit;
}noeud;

typedef noeud * arbre;

arbre creer_feuille(int * tab, int index);

void creer_noeud(arbre tab[], int taille);

int est_feuille(arbre a);

int concat(int x, int y);

void affichage_code(int nbr_bits, int codage);

void creer_code(arbre element, int code, int profondeur);

#endif
