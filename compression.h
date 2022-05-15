#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

#include "noeud.h"

void ecrireEntete(FILE * fich, char *nomfich, arbre alphabet[256]);

void ecrireFichier(FILE *fichdest, FILE *fichsrc, arbre alphabet[256]);

void writeStringAsBinary(FILE *fichdest,char *code);

#endif
