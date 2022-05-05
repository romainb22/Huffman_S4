#ifndef _DECOMPRESSION_C_
#define _DECOMPRESSION_C_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"decompression.h"

void getFileName(char file[2500], FILE * myfile){
  rewind(myfile);
  if(fscanf(myfile,"%[^\n]",file)!=1){
    printf("Erreur de lecture dans le fichier compressé!\n");
  }
  return;
}

void getArbre(FILE * myfile,  arbre alphabet[256]){
  char c,old,code[5000]="";
  c = fgetc(myfile);
  old = c;
  while(c!=EOF){
    while(c!='-'){
      old = c;
      c=fgetc(myfile);
    }
    c=fgetc(myfile);
    if(c=='>'){
      alphabet[(int)old]=malloc(sizeof(noeud));
      alphabet[(int)old]->caractere=old;
      while(c!='-'){
        c=fgetc(myfile);
        if(c=='0' || c=='1'){
          strncat(code,&c,1);
        }
      }
      alphabet[(int)old]->taillecode = strlen(code);
      alphabet[(int)old]->code=atoi(code);
    }
    if(c=='-'){
      c=fgetc(myfile);
      if(c=='|'){
        c=fgetc(myfile);
        if(c=='\n'){
          return;
        }
      }
      else{
        printf("Fichier corrompu, arrêt...\n");
        exit(EXIT_FAILURE);
      }
    }
  }
  return;
}

void getFileContent(FILE * myfile);


#endif
