#ifndef _DECOMPRESSION_H_
#define _DECOMPRESSION_H_

#include"noeud.h"

/*! \file decompression.h
    \brief Sont définies ici les fonctions permettant de décompresser un fichier

    Nous avons séparés la décompression en trois étapes : la récupération du nom de fichier, la lecture de l'entête et la décompression du contenu.
    Est définie aussi une fonction permettant de convertir un entier en une chaîne de caractère
*/

/*! \fn void itoa(int \a n , char \a s[] )
    \brief Permet de convertir \a n en chaine de caractère stockée dans \a s[]
    \param \a n L'entier à convertir
    \param \a s[] la chaîne de caractère résultat
*/

/*! \fn void getFileName(char * \a file , FILE * \a myfile)
    \brief Permet de récupérer le nom du fichier d'origine dans le fichier compressé
    \param \a file La chaîne de caractère dans laquelle on stocke le nom
    \param \a myfile Un flux de fichier où lire

    \details Il nous suffit juste de lire ce qui est écrit sur la première ligne
    On quitte le programme si on rencontre une entête erronée
*/

/*! \fn void getArbre(FILE * \a myfile , arbre \a alphabet[256] )
    \brief récupère dans \a alphabet l'alphabet contenu dans l'entête de \a myfile
    \param \a myfile Un flux de fichier où lire
    \param \a alphabet L'aplhabet où l'on récupère l'alphabet lu

    \details Notre algorithme :
          -\a c le caractère lu dans \a myfile, \a old un caractère
          -\a code et \a taillecode des chaînes de caractères
          -\a first un entier

    c = lireProchainCaractere( \a myfile )
    tant que \a c != \a EOF faire
          \a first = 1
          switch( \a c ):
                    cas '<':
                            \a c = lireProchainCaractere( \a myfile )
                            si \a c == \c '\n' alors
                                    retourner (on est en fin d'entête)
                            sinon
                                    first = first - 1
                            fin si
                    cas '>':
                          \i = 0
                          vider( \a code )
                          vider( \a taillecode )
                          si \a first != 0 alors
                                    \a c = lireProchainCaractere( \a myfile )
                                    \a old = \a c
                          fin si
                          \a c = lireProchainCaractere( \a myfile )
                          si \a c == ' ' alors
                                    \a c = lireProchainCaractere( \a myfile )
                          fin si
                          tant que \a c != ' '
                                    ajouter( \a code , \a c )
                                    \a c = lireProchainCaractere( \a myfile )
                                    i++
                          fin tant que
                          \a code[ \a i \a] = '\0'
                          \a c = lireProchainCaractere( \a myfile )
                          tant que \a c != \c '\n' faire
                                    ajouter( \a taillecode , \a c )
                                    \a c = lireProchainCaractere( \a myfile )
                                    i++
                          fin tant que
                          initialiser( \a alphabet[ valeurEntiere( \a old ) \a ] , \a code, \a taillecode, \a old)
                          break
                    defaut:
                          \a c = lireProchainCaractere( \a myfile )
                          break
          fin switch
    fin tant que
*/

/*! \fn void getFileContent(FILE * \a myfilesrc , FILE * \a myfiledst , arbre \a alphabet[256] )
    \brief Permet de lire le contenu de \a myfilesrc (compressé) et de l'écrire dans \a myfiledst (décompressé)
    \param \a myfilesrc Le flux fichier où lire
    \param \a myfiledst Le flux fichier où écrire
    \param \a alphabet[256] L'arbre généré par l'algorithme d'Huffman

    Notre algorithme :

    Tant que l'on lit du contenu dans \a myfilesrc :
            On l'écrit sous forme de 0 et de 1 dans un fichier temporaire
    fin tant que
    Tant que l'on lit du contenu (caractère par caractère) dans le fichier temporaire et que longueur( \a code ) <= taillecodemax :
            alphabet[ \a i \a ]
            on ajoute le caractère lu à \a code
            Tant que longueur( \a code ) <= \a taillecodemin
                      on ajoute le caractère lu à \a code
            fin tant que
            pour \a i de 0 à 256
                      si \a alphabet[ \a i \a ] existe et que \a alphabet[ \a i \a ] pointé par longueur est égale longueur( \a code ) alors
                                écrire( \a myfiledst , \a alphabet[ \a i \a ] pointé par caractère)
                                vider(code)
                                Aller à: \a ETIQUETTE \a 1
                      fin si
            fin pour
    fin tant que
*/

void itoa(int n, char s[]);

void getFileName(char * file, FILE * myfile);

void getArbre(FILE * myfile, arbre alphabet[256]);

void getFileContent(FILE * myfilesrc, FILE *myfiledst, arbre alphabet[256]);

#endif
