#ifndef _DECOMPRESSION_H_
#define _DECOMPRESSION_H_

#include"noeud.h"

char * getFileName(FILE * myfile);

void getArbre(FILE * myfile, arbre alphabet[256]);

void getFileContent(FILE * myfile);

#endif
