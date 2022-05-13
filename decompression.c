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

void getFileName(char file[2500], FILE * myfile){
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
  char c,old=0,code[5000]="";
  int i, first;
  /*if(fread(&c,sizeof(char),1,myfile)!=1){
    printf("Erreur de lecture l74!\n");
    return;
  }*/
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
      case '>':
        /*On est potentiellement au début d'une nouvelle ligne*/
        i=0;
        strcpy(code,"");
        if(first){
          c=fgetc(myfile);
          old = c;
        }
        c=fgetc(myfile);
        while(c!='\n'){
          if(c=='0' || c=='1'){
            strncat(code,&c,1);
          }
          c=fgetc(myfile);
          i++;
        }
        code[i]='\0';
        alphabet[(int)old]=malloc(sizeof(noeud));
        if(!alphabet[(int)old]){
          printf("Erreur d'allocation\n");
        }
        alphabet[(int)old]->code= atoi(code);
        alphabet[(int)old]->taillecode = strlen(code);
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
  char c, code[500],codage[500],codage2[500];
  int towrite=0, sizetowrite=0,i=0,j=0,k,found,taillecodemax=0,taillecodemin=500;
  c = fgetc(myfilesrc);
  fseek(myfilesrc, 0, SEEK_SET);

  FILE * dump = fopen("dump.txt","w+");
  FILE * dump2 = fopen("dump2.txt","w+");
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
  printf("%c",c);
  /* On traite le contenu */
  ICI:
  while(c!=EOF){
    strcpy(code,""); /* On initialise le code que l'on va récupérer*/
    strncat(code,&c,1); /* On ajoute le caractère */
    while((int)strlen(code)<taillecodemin){ /* On récupère les caractères suivant, jusqu'à arriver à la taille minimum */
      c = fgetc(myfilesrc);
      strncat(code,&c,1);
      printf("%c",c);
    }
    LA:
    for(i=0;i<256;i++){ /* On parcours l'alphabet pour comparer les codes (lourd) */
      PLUSHAUT:
      if(!estVide(alphabet[i])){
        if(alphabet[i]->taillecode!=(int)strlen(code)){
          i++;
          goto PLUSHAUT;
        }
        strcpy(codage2,""); /* On initialise le code de l'alphabet */
        strcpy(codage,"");
        itoa(alphabet[i]->code,codage);
        for(k=0;k<alphabet[i]->taillecode-(int)strlen(codage);k++){ /* on rajoute les 0 à guache */
          strncat(codage2,"0",1);
        }
        strcat(codage2,codage); /* on concatène les deux chaines (donc on a dans codage2 le code de la lettre de l'alphabet) */
        if(!strcmp(codage2,code)){ /* Si les deux codes coïncident */
          fputc(alphabet[i]->caractere,myfiledst); /* On écrit dans le fichier destination le caractère lu */
          found++;
        }
        else{
          found=0;
        }
        if(found){ /* Si on a trouvé une coïncidence, on lit le prochain caractère et on recommence */
          c=fgetc(myfilesrc);
          printf("%c",c);
          goto ICI;
        }
      }
    }
    if(strlen(code)<taillecodemax+1){ /* Si la taille du code est acceptable, on lit le prochain caractère */
      c=fgetc(myfilesrc);
      printf("%c",c);
      strncat(code,&c,1);
    }
    goto LA;
    /*towrite=towrite<<PAQUET;
    towrite=towrite|c;
    sizetowrite=sizetowrite+PAQUET;
    strcpy(code,binaryToStr(towrite));
    for(k=0;k<PAQUET;){
      for(i=0;i<256;i++){
        if(!estVide(alphabet[i])){
          itoa(alphabet[i]->code,codage);
          for(j=0;j<alphabet[i]->taillecode;j++){
            if(codage[j]==code[k]){
              k++;
            }
          }
          if(k==j){
            fputc(i,myfiledst);
          }
        }
      }
    }*/
  }
  return;
}

char* binaryToStr(int number){
  static char res[PAQUET+1];
  int i;
  for(i=0;i<PAQUET;i++){
    res[i] = number & 0x8000 ? '1' : '0';
    number<<=1;
  }
  res[PAQUET]='\0';
  return res;
}

#endif
