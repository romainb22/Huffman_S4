#ifndef _COMPRESSION_C_
#define _COMPRESSION_C_
#define PAQUET 8

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"compression.h"
#include"decompression.h"

void ecrireEntete(FILE * fich, char *nomfich, arbre alphabet[256]){
  int i,j;
  char code[500];
  fputs(nomfich,fich);
  fputc('\n',fich);
  for(i=0;i<256;i++){
    if(!estVide(alphabet[i])){
      strcpy(code,"");
      fputc('>',fich);
      fputc(alphabet[i]->caractere,fich);
      fputc(' ',fich);
      itoa(alphabet[i]->code,code);
      printf("Code=alphabet[%d]->%d, taillecode=%d\n",i,alphabet[i]->code,alphabet[i]->taillecode);
      for(j=0;j<alphabet[i]->taillecode-(int)strlen(code);j++){
        fputc('0',fich);
        printf("0");
      }
      for(j=0;j<(int)strlen(code);j++){
        fputc(code[j],fich);
      }
      printf("%s",code);
      fputc('\n',fich);
      printf("\n");
    }
  }
  fputs("<\n",fich);
  return;
}

void ecrireFichier(FILE *fichdest, FILE *fichsrc, arbre alphabet[256]){
  char c, code, codage[500];
  int towrite=0, sizetowrite=0,taille;
  c = fgetc(fichsrc);
  while(c!=EOF){
    if(alphabet[(int)c]){
      //towrite = towrite << alphabet[(int)c]->taillecode; /* On décale de taillecode */
      //printf("towrite: %d\n",towrite);
      //sleep(1);
      //towrite = towrite | alphabet[(int)c]->code;
      //printf("towrite | alphabet[%d]->code: %d\n",(towrite | alphabet[(int)c]->code), (int) c);
      //sleep(1);
      /*sizetowrite+=alphabet[(int)c]->taillecode;
      while(sizetowrite>=PAQUET){
        sizetowrite-=PAQUET;
        code=towrite<<sizetowrite;
        fputc(code,fichdest);
      }*/
      taille=1;
      sizetowrite = alphabet[(int)c]->code;
      while(sizetowrite>9){
        sizetowrite/=10;
        taille++;
      }
      for(towrite=0;towrite<alphabet[(int)c]->taillecode-taille;towrite++){
        fputc('0',fichdest);
      }
      itoa(alphabet[(int)c]->code,codage);
      fputs(codage,fichdest);
    }
    c = fgetc(fichsrc);
  }
  /*if(sizetowrite){
    towrite=towrite<<(PAQUET-sizetowrite);*/ /* On rajoute les zeros */
    /*fputc(towrite,fichdest);
  }*/
  return;
}

#endif
