#ifndef _DECOMPRESSION_H_
#define _DECOMPRESSION_H_

#include"noeud.h"

void itoa(int n, char s[]);

void getFileName(char file[2500], FILE * myfile);

void getArbre(FILE * myfile, arbre alphabet[256]);

void getFileContent(FILE * myfilesrc, FILE *myfiledst, arbre alphabet[256]);

#endif
