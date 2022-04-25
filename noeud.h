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

#endif
