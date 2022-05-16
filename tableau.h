#ifndef _TABLEAU_H_
#define _TABLEAU_H_

#include"noeud.h"
/*! \file tableau.h
    \brief Est définie ici la la fonction de tri de tableau
*/

/*! \fn void trierTableauArbre(arbre \a huffman[256], int \a taille)
    \brief Permet de trier l'arbre passé en paramètre
    \param \a huffman[256] Le tableau de noeud de taille 256
    \param \a taille Le nombre d'éléments dans le tableau (pas toujours 256)
*/

void trierTableauArbre(arbre huffman[256], int taille);

#endif
