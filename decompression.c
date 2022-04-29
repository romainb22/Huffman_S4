#ifndef _DECOMPRESSION_C_
#define _DECOMPRESSION_C_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"decompression.h"

char * getFileName(FILE * myfile){
  char *res=NULL;
  rewind(myfile);
  if(fscanf(myfile, "%s\n",res)!=1){
      printf("Erreur de leceture");
      return NULL;
  }
  return res;
}

void getArbre(FILE * myfile,  arbre alphabet[256]){
  char c,old,*code="";
  c = fgetc(myfile);
  old = c;
  while(c!=EOF){
    while(c!='-'){
      old = c;
      c=fgetc(myfile);
    }
    c=fgetc(myfile);
    if(c=='>'){
      alphabet[(int)old]=creerArbreVide();
      alphabet[(int)old]->caractere=old;
      if(fscanf(myfile, "%c-|",code)!=1){
        printf("Erreur de lecture\n");
        return;
      }
      else{
        alphabet[(int)old]->taillecode = strlen(code);
        alphabet[(int)old]->code=atoi(code);
      }
    }
    else if(c=='-'){
      c=fgetc(myfile);
    }
    else{
      printf("Fichier corrompu, arrêt...");
      exit(EXIT_FAILURE);
    }
  }
  return;
}

void getFileContent(FILE * myfile);


#endif
