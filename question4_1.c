#ifndef _QUESTION4_1_C_
#define _QUESTION4_1_C_

#include<stdio.h>
#include<stdlib.h>


void usage(char * str){
  printf("Usage : %s [fichier] [entier]\n", str);
  printf("fichier : chemin vers un fichier texte\n");
  printf("entier : le nombre de caractère à lire dans ledit fichier\n\n");
  return;
}

void readNCharFromFile(FILE *myfile, int n){
  int count;
  char todisplay[n];
  if(myfile){
    count = fread(&todisplay, sizeof(char), n, myfile);
    if(count<n){
      printf("Seulement %d caractères on pu être lus sur %d (Fichier trop court):\n",count, n);
    }
    else{
      printf("%d caractères on pu être lus :\n", n);
    }
  }
  else{
    printf("Erreur fichier non valide.\n");
  }
  printf("\n%s\n",todisplay);
  return;
}

void readEntireFile(FILE *myfile){
  char c;
  if(!myfile){
    printf("Erreur fichier non valide.\n");
    return;
  }
  c = fgetc(myfile);
  while(c!=EOF){
    printf("%c",c);
    c = fgetc(myfile);
  }
  return;
}

int main(int argc, char ** argv){
  FILE * myfile;
  if(argc != 3){
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }
  else{
    myfile = fopen(argv[1],"r");
    readNCharFromFile(myfile,atoi(argv[2]));
    fclose(myfile);
    printf("\n\n");
    myfile = fopen(argv[1],"r");
    readEntireFile(myfile);
    fclose(myfile);
  }
  return 0;
}

#endif
