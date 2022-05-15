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
  char *code,taillecode[500],vide[]="";
  fputs(nomfich,fich);
  fputc('\n',fich);
  for(i=0;i<256;i++){
    if(!estVide(alphabet[i])){
      //strcpy(code,"");
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
  char c, *code/*[8]*/, *codage/*[500]*/,*codagetmp/*[500]*/, zero='0',vide[]="";
  int towrite=0,taille,taillecontenu=0,quotient, reste, i, j, taillecode;
  c = fgetc(fichsrc);
  taillecontenu++;
  /*code=malloc(sizeof(char)*500);
  codage=malloc(sizeof(char)*500);
  codagetmp=malloc(sizeof(char)*500);
  if(!code || !codage || !codagetmp){
    printf("Erreur d'allocation mémoire\n");
    return;
  }*/
  while(c!=EOF){
    c = fgetc(fichsrc);
    taillecontenu++;
  }
  quotient = taillecontenu/8;
  reste = taillecontenu%8;
  if(reste){
    quotient++;
  }
  rewind(fichsrc);
  c = fgetc(fichsrc);
  taillecontenu=0;
  while(c!=EOF){
    //strcpy(code,"");
    code=strdup(vide);
    //strcpy(codage,"");
    codage=strdup(vide);
    //strcpy(codagetmp,"");
    codagetmp=strdup(vide);
    //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
    //sleep(5);
    THERE:
    while(c!=EOF && strlen(code)<=8){
      /*printf("%c ->",c);
      usleep(10000);*/
      if(alphabet[(int)c]){
        codeToBiStr(alphabet[(int)c]->code,codagetmp);
        //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
        //sleep(5);
        /*printf("taillecode = %d strlen(codagetmp)= %d\n",alphabet[(int)c]->taillecode,(int)strlen(codagetmp));
        printf("%c > ",c);*/
        for(towrite=0;towrite<alphabet[(int)c]->taillecode-(int)strlen(codagetmp);towrite++){
          strncat(codage,&zero,1);
          //printf("0");
        }
        //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
        //sleep(5);
        //printf("%s\n",codagetmp);
        HERE:
        strcat(codage,codagetmp);
        //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
        //sleep(5);
        /*printf("codagetmp=%s\n",codagetmp);
        sleep(5);
        printf("codage=%s\n",codage);
        sleep(5);*/
        /* On a le code entier dans codage */
        if((int)strlen(codage)==8 && strlen(code)==0){
          /* On écrit le caractere correspondant à la chaine codage */
          //printf("Yo, je vais écrire %s\n\n",codage);
          writeStringAsBinary(fichdest,codage);
        }
        else if((int)strlen(codage)+(int)strlen(code)<8){
          strcat(code,codage);
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
          //strcpy(codage,"");
          codage=strdup(vide);
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
          //strcpy(codagetmp,"");
          codagetmp=strdup(vide);
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
          c = fgetc(fichsrc);
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
          goto THERE;
        }
        else{
          taillecode = strlen(code);
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //printf("taillecode = %d",taillecode);
          //sleep(5);
          for(i=strlen(code);i<(int)sizeof(code);i++){
            code[i]=codage[i-taillecode];
          }
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
          code[i]='\0'; /* Crée un warning, mais sans ça ne marche pas*/
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
          /* On écrit le caractere correspondant à la chaine codage */
          //printf("yo je vais écrire dans le fichier: %s\n",code);
          writeStringAsBinary(fichdest,code);
          /* Aller à un autre endroit spécial et traiter le reste de la chaine */
          //strcpy(codagetmp,"");
          codagetmp=strdup(vide);
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
          for(j=(int)sizeof(code)-taillecode;j<=i;j++){
            strncat(codagetmp,&codage[j],1);
          }
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
          //strcpy(code,"");
          code=strdup(vide);
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
          //strcpy(codage,"");
          codage=strdup(vide);
          //printf("c=%c code de c=%d taillecode de c=(%d)\ncode=%s strlen(%d)\ncodage=%s strlen(%d)\ncodagetmp=%s strlen(%d)\n\n\n",alphabet[(int)c]->caractere,alphabet[(int)c]->code,alphabet[(int)c]->taillecode,code,strlen(code),codage,strlen(codage),codagetmp,strlen(codagetmp));
          //sleep(5);
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
    /*if(strlen(code)<8){
      code[7]='0';
    }*/
    writeStringAsBinary(fichdest,code);
  }
  //printf("oi, %s(%d)\n",codage, strlen(codage));
  return;
}

void writeStringAsBinary(FILE *fichdest,char *code){
  char c = strtol(code,0,2);
  /*printf("[------------------>%s, %c\n",code,c);
  sleep(5);*/
  fputc(c,fichdest);
  return;
}

#endif
