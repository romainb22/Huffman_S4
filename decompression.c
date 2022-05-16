#ifndef _DECOMPRESSION_C_
#define _DECOMPRESSION_C_
#define PAQUET 8

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

void getFileName(char * file, FILE * myfile){
  char c='0';
  int i=0;
  fseek(myfile, 0, SEEK_SET);
  if(fread(&c,sizeof(char),1,myfile)!=1){
    printf("Erreur de lecture!\n");
    return;
  }
  do{
    file[i]=c;
    i++;
    if(c==EOF){
      printf("Arrivés à la fin du fichier, entête corrompue\n");
      return;
    }
    if(fread(&c,sizeof(char),1,myfile)!=1){
      printf("Erreur de lecture!\n");
      return;
    }
  }
  while((c!='\n'));
  if(c==EOF){
    printf("Arrivés à la fin du fichier, entête corrompue\n");
    return;
  }
  file[i]='\0';
  return;
}

void getArbre(FILE * myfile,  arbre alphabet[256]){
  char c,old=0,*code,*taillecode,vide[]="";
  int i, first;

  code = malloc(sizeof(char)*50000);
  taillecode = malloc(sizeof(char)*50000);
  if(!code || !taillecode){
    printf("Erreur d'allocation.\n");
    exit(EXIT_FAILURE);
  }
  c=fgetc(myfile);
  while(c!=EOF){
    first=1;
    switch(c){
      case '<':
        /*On est potentiellement à la fin de l'entête*/
        c=fgetc(myfile);
        if(c=='\n'){
          /*On est à la fin de l'entête*/
          return;
        }
        else{
          first--;
        }
        __attribute__ ((fallthrough)); /* Pour éviter un warning de fallthrough intentionnel*/
      case '>':
        /*On est potentiellement au début d'une nouvelle ligne*/
        i=0;
        code = strdup(vide);
        taillecode = strdup(vide);
        if(first){
          c=fgetc(myfile);
          old = c;
        }
        c=fgetc(myfile);
        if(c==' '){
          c=fgetc(myfile);
        }
        while(c!=' '){
          strncat(code,&c,1);
          c=fgetc(myfile);
          i++;
        }
        code[i]='\0';
        alphabet[(int)old]=malloc(sizeof(noeud));
        if(!alphabet[(int)old]){
          printf("Erreur d'allocation\n");
        }
        c=fgetc(myfile);
        while(c!='\n'){
          strncat(taillecode,&c,1);
          c=fgetc(myfile);
          i++;
        }
        alphabet[(int)old]->code= atoi(code);
        alphabet[(int)old]->taillecode = atoi(taillecode);
        alphabet[(int)old]->caractere = old;
        break;
      default:
        c=fgetc(myfile);
        break;
    }
  }
  return;
}

void getFileContent(FILE * myfilesrc, FILE * myfiledst, arbre alphabet[256]){
  char c, zero='0',*code,*codage,*codage2,vide[]="";
  int i=0,k,found,taillecodemax=0,taillecodemin=500;
  c = fgetc(myfilesrc);
  fseek(myfilesrc, 0, SEEK_SET);

  FILE * tmp = fopen("tmp","wb+");
  /* On récupèrere la taille max et minimum des codes */
  for(i=0;i<256;i++){
    if(!estVide(alphabet[i])){
      if(alphabet[i]->taillecode>taillecodemax){
        taillecodemax=alphabet[i]->taillecode;
      }
      if(alphabet[i]->taillecode<taillecodemin){
        taillecodemin=alphabet[i]->taillecode;
      }
    }
  }
  while(c!='<'){
    c = fgetc(myfilesrc);
  }
  c = fgetc(myfilesrc);
  if(c!='\n'){
    while(c!='<'){
      c = fgetc(myfilesrc);
    }
  }
  /* Ici on est au début du contenu du fichier */
  found=0;
  c = fgetc(myfilesrc);
  while(c!=EOF){
    for (i=7;i>=0;--i){
      if(c & (1<<i)){
        fputc('1',tmp);
      }
      else{
        fputc('0',tmp);
      }
    }
    c = fgetc(myfilesrc);
  }
  printf("\n\n");
  fclose(tmp);
  /* On traite le contenu */
  tmp=fopen("tmp","rb+");
  c=fgetc(tmp);
  ICI:
  while(c!=EOF){
    /* On initialise le code que l'on va récupérer*/
    code=strdup(vide);
    strncat(code,&c,1); /* On ajoute le caractère */
    while((int)strlen(code)<taillecodemin){ /* On récupère les caractères suivant, jusqu'à arriver à la taille minimum */
      c = fgetc(tmp);
      strncat(code,&c,1);
    }
    LA:
    if(c==EOF){
      goto ICI;
    }
    for(i=0;i<256;i++){ /* On parcours l'alphabet pour comparer les codes (lourd) */
      PLUSHAUT:
      if(!estVide(alphabet[i])){
        if(alphabet[i]->taillecode!=(int)strlen(code)){
          i++;
          goto PLUSHAUT;
        }
        codage2=strdup(vide);
        codage=strdup(vide);
        codeToBiStr(alphabet[i]->code,codage2);
        for(k=0;k<alphabet[i]->taillecode-(int)strlen(codage2);k++){
          strncat(codage,&zero,1);
        }
        strcat(codage,codage2);
        if(!strcmp(codage,code)){ /* Si les deux codes coïncident */
          fputc(alphabet[i]->caractere,myfiledst); /* On écrit dans le fichier destination le caractère lu */
          found++;
        }
        else{
          found=0;
        }
        if(found){ /* Si on a trouvé une coïncidence, on lit le prochain caractère et on recommence */
          c=fgetc(tmp);
          goto ICI;
        }
      }
    }
    if((int)strlen(code)<taillecodemax+1){ /* Si la taille du code est acceptable, on lit le prochain caractère */
      c=fgetc(tmp);
      strncat(code,&c,1);
    }
    goto LA;
  }
  fclose(tmp);
  remove("tmp");
  return;
}

#endif
