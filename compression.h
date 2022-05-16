#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

#include "noeud.h"

/*! \file compression.h
    \brief Sont définies ici les fonctions permettant de compresser un fichier

    Nous avons séparés la compression en deux étapes : l'écriture de l'entête et l'écriture du contenu.
    Est définie aussi une fonction permettant d'écrire dans un fichier le caractère correspondant à une code binaire passé en paramètre
*/

/*! \fn void ecrireEntete(FILE * \a fich, char * \a nomfich, arbre \a alphabet[256])
    \brief Permet d'écrire dans \a fich le nom du fichier stocké dans \a nomfich, ainsi qu'une représentation de l'arbre \a alphabet[256]
    \param \a fich Le flux fichier où écrire
    \param \a nomfich Le nom du fichier
    \param \a alphabet[256] L'arbre généré par l'algorithme d'Huffman

    \details Pour nous une entête est composée d'au plus 258 lignes:
    Sur la première ligne, nous avons le nom du fichier
    Sur les n lignes suivantes (au max 256), nous avons les représentation des feuilles comme suit:
          >c [code] \c [taillecode]'\n'
          où c est le caractère, [code] son code, et [taillecode] la taille du code
    L'entète est terminée par une ligne :
          \c<\n
*/

/*! \fn void ecrireFichier(FILE * \a fichdest, FILE * \a fichsrc, arbre \a alphabet[256])
    \brief Permet d'écrire dans \a fich le contenu du fichier \a fichsrc, de façon compressée
    \param \a fichdest Le flux fichier où écrire
    \param \a fichsrc Le flux fichier où lire
    \param \a alphabet[256] L'arbre généré par l'algorithme d'Huffman

    \details Notre algorithme :
      -\a c le caractère lu dans \a fichsrc
      -\a code , \a codage et \a codagetmp des chaînes de caractères

      c = lireProchainCaractere( \a fichsrc )
      Tant que \a c != \a EOF faire:
                vider(\a code )
                vider(\a codage )
                vider(\a codagetmp )
                \a ETIQUETTE \a 1:
                Tant que \a c != \a EOF et longueur(code)<=8 faire:
                          si existe( \a alphabet[ valeurEntiere(\a c ) \a ] ) alors:
                                    \a codagetmp = valeurbinaire( \a alphabet[ valeurEntiere(\a c ) \a ] )
                                    pour \i de 0 à ( \a alphabet[ valeurEntiere(\a c ) \a ] - longueur( \a codagetmp ) ) - 1 faire:
                                                ajouter( \a codage , '0')
                                    fin pour
                                    \a ETIQUETTE \a 2:
                                    concatener( \a codage , \a codagetmp )
                                    si ( longueur( \a codage ) == 8 et longueur( \a code ) == 0 ) alors
                                                ecrireEnBinaire( \a fichdest , \a codage )
                                    fin si
                                    sinon si ( longueur( \a codage ) + longueur( \a code ) < 8 ) alors
                                                concatener( \a code , \a codage )
                                                vider( \a codage )
                                                vider( \a codagetmp )
                                                c = lireProchainCaractere( \a fichsrc )
                                                aller a: \a ETIQUETTE \a 1
                                    fin sinon si
                                    sinon
                                                \a taillecode = longueur( \a code )
                                                pour \a i de \a taillecode à tailleMémoireDe( \a code )
                                                            \a code[ \a i \a ] = \a codage[ \a i - \a taillecode \a ]
                                                fin pour
                                                \a code[ \a i \a] = '\0'
                                                ecrireEnBinaire( \a fichdest , \a code )
                                                vider( \a codagetmp )
                                                pour j de ( tailleMémoireDe( \a code ) - \a taillecode ) à i
                                                            ajouter( \a codagetmp , \a codage[ \a j \a ] )
                                                fin pour
                                                vider( \a code )
                                                vider( \a codage )
                                                Aller a: \a ETIQUETTE \a 2
                                    fin sinon
                          fin si
                          si \a c == \a EOF alors
                                    Aller a: \a ETIQUETTE \a 1
                          fin si
                fin tant que
      fin tant que
      si longueur( \a code ) != 0 alors
                tant que (longueur( \a code ) < tailleMémoireDe( \a code ) ) faire
                          ajouter( \a code, '0' )
                fin tant que
                ecrireEnBinaire( \a fichdest , \a code )
      fin si
*/

/*! \fn void writeStringAsBinary(FILE * \a fichdest , char * \a code )
    \brief écrit dans \a fichdest la chaine de caractère \a code en binaire, i.e écrit le code ASCII correspondant à la chaîne de caractère \a code
    \param \a fichdest Un flux de fichier où écrire
    \param \a code Une chaîne de 8 caractère (sous format binaire)
*/


void ecrireEntete(FILE * fich, char *nomfich, arbre alphabet[256]);

void ecrireFichier(FILE *fichdest, FILE *fichsrc, arbre alphabet[256]);

void writeStringAsBinary(FILE *fichdest,char *code);

#endif
