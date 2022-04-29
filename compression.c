#ifndef _COMPRESSION_C_
#define _COMPRESSION_C_

#include<stdlib.h>
#include<stdio.h>
#include"compression.h"

void ecrireEntete(FILE * fich, char *nomfich, arbre alphabet[256]){
  int i, tmp, taille;
  fprintf(fich,"%s\n",nomfich);
  for(i=0;i<256;i++){
    if(!estVide(alphabet[i])){
      taille=1;
      tmp=alphabet[i]->code;
      fprintf(fich,"%c->",alphabet[i]->caractere);
      while(tmp>9){
        tmp/=10;
        taille++;
      }
      for(tmp=0;tmp<alphabet[i]->taillecode-taille-1;tmp++){
        fprintf(fich,"0");
      }
      fprintf(fich,"%d-|",alphabet[i]->code);
    }
  }
  fprintf(fich,"\n");
  return;
}

void ecrireFichier(FILE *fichdest, FILE *fichsrc, arbre alphabet[256]){
  char c;
  int tmp, taille;
  c = fgetc(fichsrc);
  while(c!=EOF){
    if(alphabet[(int)c]){
      taille=1;
      tmp=alphabet[(int)c]->code;
      while(tmp>9){
        tmp/=10;
        taille++;
      }
      for(tmp=0;tmp<alphabet[(int)c]->taillecode-taille-1;tmp++){
        fprintf(fichdest,"0");
      }
      fprintf(fichdest,"%d",alphabet[(int)c]->code);
    }
    c = fgetc(fichsrc);
  }
  fprintf(fichdest, "\n");
  return;
}

#endif
