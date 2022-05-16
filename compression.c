#ifndef _COMPRESSION_C_
#define _COMPRESSION_C_
#define PAQUET 8

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"compression.h"
#include"decompression.h"

void ecrireEntete(FILE * fich, char *nomfich, arbre alphabet[256]){
  int i;
  char *code,taillecode[500],vide[]="";
  code = malloc(sizeof(char)*50000);
  if(!code){
    printf("Erreur d'allocation.\n");
    exit(EXIT_FAILURE);
  }
  fputs(nomfich,fich);
  fputc('\n',fich);
  for(i=0;i<256;i++){
    if(!estVide(alphabet[i])){
      code=strdup(vide);
      fputc('>',fich);
      fputc(alphabet[i]->caractere,fich);
      fputc(' ',fich);
      itoa(alphabet[i]->code,code);
      fputs(code,fich);
      fputc(' ',fich);
      itoa(alphabet[i]->taillecode,taillecode);
      fputs(taillecode,fich);
      fputc('\n',fich);
    }
  }
  fputs("<\n",fich);
  return;
}

void ecrireFichier(FILE *fichdest, FILE *fichsrc, arbre alphabet[256]){
  char c, *code, *codage,*codagetmp, zero='0',vide[]="";
  int towrite=0,i, j, taillecode;
  code = malloc(sizeof(char)*50000);
  codage = malloc(sizeof(char)*50000);
  codagetmp = malloc(sizeof(char)*50000);
  if(!code || !codage || !codagetmp){
    printf("Erreur d'allocation.\n");
    exit(EXIT_FAILURE);
  }
  rewind(fichsrc);
  c = fgetc(fichsrc);
  while(c!=EOF){
    code=strdup(vide);
    codage=strdup(vide);
    codagetmp=strdup(vide);
    THERE:
    while(c!=EOF && strlen(code)<=8){
      if(alphabet[(int)c]){
        codeToBiStr(alphabet[(int)c]->code,codagetmp);
        for(towrite=0;towrite<alphabet[(int)c]->taillecode-(int)strlen(codagetmp);towrite++){
          strncat(codage,&zero,1);
        }
        HERE:
        strcat(codage,codagetmp);
        /* On a le code entier dans codage */
        if((int)strlen(codage)==8 && strlen(code)==0){
          /* On écrit le caractere correspondant à la chaine codage */
          writeStringAsBinary(fichdest,codage);
        }
        else if((int)strlen(codage)+(int)strlen(code)<8){
          strcat(code,codage);
          codage=strdup(vide);
          codagetmp=strdup(vide);
          c = fgetc(fichsrc);
          goto THERE;
        }
        else{
          taillecode = strlen(code);
          for(i=strlen(code);i<(int)sizeof(code);i++){
            code[i]=codage[i-taillecode];
          }
          code[i]='\0';
          /* On écrit le caractere correspondant à la chaine codage */
          writeStringAsBinary(fichdest,code);
          /* Aller à un autre endroit spécial et traiter le reste de la chaine */
          codagetmp=strdup(vide);
          for(j=(int)sizeof(code)-taillecode;j<=i;j++){
            strncat(codagetmp,&codage[j],1);
          }
          code=strdup(vide);
          codage=strdup(vide);
          goto HERE;
        }
      }
      if(c==EOF){
        goto THERE;
      }
    }
  }
  if(strlen(code)){
    while(strlen(code)<sizeof(code)-1){
      strncat(code,&zero,1);
    }
    writeStringAsBinary(fichdest,code);
  }
  return;
}

void writeStringAsBinary(FILE *fichdest,char *code){
  char c = strtol(code,0,2);
  fputc(c,fichdest);
  return;
}

#endif
