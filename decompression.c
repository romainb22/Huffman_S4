#ifndef _DECOMPRESSION_C_
#define _DECOMPRESSION_C_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"decompression.h"

void itoa(int n, char s[]){
  int i,j, sign;
  char c;
  if((sign=n)<0){
    n=-n;
  }
  i=0;
  do{
    s[i++]=n%10+'0';
  }
  while((n/=10)>0);
  if(sign<0){
    s[i++]='-';
  }
  s[i]='\0';
  for(i=0,j=strlen(s)-1;i<j;i++, j--){
    c=s[i];
    s[i]=s[j];
    s[j]=c;
  }
  return;
}

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

void getFileContent(FILE * myfilesrc, FILE * myfiledst, arbre alphabet[256]){
  char c,code[500];
  int i,j,found, foundinter;
  c = fgetc(myfilesrc);
  printf("yo c=%c\n!",c);
  while(c != EOF){
    i=0;
    found=0;
    while(!found){
      printf("yo2 c=%c\n!",c);
      if(c!='0' && c!='1'){
        /*On est potentiellement sur la première ou la deuxième ligne, reste à voir ce que ça donne sur les données */
        printf("yo3 c=%c\n!",c);
        while(c!='\n'){
          printf("yo4 c=%c\n!",c);
          c=fgetc(myfilesrc);
          if(c==EOF){
            printf("yo5 c=%c\n!",c);
            return;
          }
        }
        /* Dans le pire des cas, on est à la fin de la première ligne */
        printf("yo6 c=%c\n!",c);
        c=fgetc(myfilesrc);
        if(c==EOF){
          printf("yo7 c=%c\n!",c);
          return;
        }
        /* Donc ici on est au début de la prochaine ligne */
      }
      else{
        printf("yo8 c=%c\n!",c);
        foundinter=0;
        for(j=0;!foundinter;j++){
          printf("yo9 c=%c\n!",c);
          if(!estVide(alphabet[j])){
            itoa(alphabet[j]->code,code); /*alphabet[j]->code -> segfault */
            if(j==255 || code[i] == c){
              foundinter++;
              printf("yo10 c=%c\n!",c);
            }
          }
        }
        printf("yo11 c=%c\n!",c);
        i++;
        if(i==alphabet[j]->taillecode){
          found++;
          printf("yo12 c=%c\n!",c);
        }
      }
    }
    printf("yo13 c=%c\n!",c);
    fputc(alphabet[j]->caractere, myfiledst);
  }
  return;
}


#endif
