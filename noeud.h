#ifndef _NOEUD_H_
#define _NOEUD_H_

/*! \file noeud.h
    \brief Sont définies ici la structure noeud ainsi que les fonctions correspondantes

    La structure noeud est définie ici, ainsi que le type arbre, qui est un pointeur
    sur un noeud. Sont définies les fonctions permettant de gérer ces noeuds/arbres
    plus une fonction permettant de convertir un entier sous sa forme binaire pour
    le stocker dans une chaîne de caractères.
*/

/*! \struct noeud noeud.h "noeud.h"
    \brief La structure noeud est conçue pour représenter un noeud d'un arbre binaire

    \details Elle contient six membres:
    - \a caractere : le caractère
    - \a occurence : l'occurence du caractère
    - \a code : le code du caractère issu de l'algorithme de Huffman
    - \a taillecode : le nombre de bits du code
    - \a fils_gauche : Un pointeur sur noeud, le fils gauche
    - \a fils_droit : Un pointeur sur noeud, sur le fils droit
*/

/*! \var typedef noeud * arbre
    \brief le type arbre est un pointeur sur noeud, ce qui rend plus pratique leur utilisation.
*/

/*! \fn int estVide(arbre \a a)
    \brief Retourne 1 si l'arbre \a a est vide, 0 sinon
    \param \a a L'arbre à tester
*/

/*! \fn arbre creerArbreVide()
    \brief Retourne un pointeur sur un arbre vide (\a NULL )
*/

/*! \fn arbre creer_feuille(int * \a tab, int \a index)
    \brief crée et retourne une feuille initialisée avec les paramètres passés
    \param \a tab Un tableau d'occurence
    \param \a index Un index qui représentera le caractère
*/

/*! \fn void creer_noeud(arbre \a tab[], int \a taille)
    \brief recherche les plus petites occurences dans \a tab[] et crée des noeuds à partir de ces occurences
    \param \a tab[] Un tableau de noeud, qui définira l'arbre
    \param \a taille Un entier
*/

/*! \fn int est_feuille(arbre \a a)
    \brief Retourne 1 si \a a pointe sur une feuille (i.e pas de fils), 0 sinon
    \param \a a L'arbre à tester
*/

/*! \fn void affichage_code(int \a codage)
    \brief Permet d'afficher un code sous sa forme binaire
    \param \a codage L'entier à afficher
*/

/*! \fn void codeToBiStr(int \a code, char * \a str)
    \brief Permet de convertir un code (entier) sous sa forme binaire dans une chaîne de caractères
    \param \a code L'entier à convertir
    \param \a str La chaîne de caractère où écrire le code
*/

/*! \fn void creer_code(arbre \a element, int \a code, int \a profondeur)
    \brief La fonction va parcourir l'arbre \a element et affecter un code à chacun des éléments en fonction du parcours et de la profondeur
    \param \a element L'arbre dont on veut créer les codes
    \param \a code L'entier qui servira pour le code (appel avec 0)
    \param \a profondeur L'entier qui servira pour la profondeur (taillecode) (appel avec 0)
*/

typedef struct noeud{
  char caractere;
  int occurence;
  int code;
  int taillecode;
  struct noeud * fils_gauche;
  struct noeud * fils_droit;
}noeud;

typedef noeud * arbre;

int estVide(arbre a);

arbre creerArbreVide();

arbre creer_feuille(int * tab, int index);

void creer_noeud(arbre tab[], int taille);

int est_feuille(arbre a);

void affichage_code(int codage);

void codeToBiStr(int code, char * str);

void creer_code(arbre element, int code, int profondeur);

#endif
