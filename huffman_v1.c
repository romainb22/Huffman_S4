#ifndef _HUFFMAN_V1_C_
#define _HUFFMAN_V1_C_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"noeud.h"
#include"tableau.h"
#include"compression.h"
#include"decompression.h"

void usage(char * str){
  printf("Usage : %s [option] [fichier]\n", str);
  printf("option : -c compression -d decompression (exclusif)\n");
  printf("fichier : chemin vers le fichier texte à compresser\n\n");
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

void occurence(FILE *myfile, int tab[256]){
  char c;
  int i;
  if(!myfile){
    printf("Erreur fichier non valide.\n");
    return;
  }
  c = fgetc(myfile);
  while(c!=EOF){
    tab[(int)c]++;
    c = fgetc(myfile);
  }
  for(i=0;i<256;i++){
    if(tab[i]){
      printf("tab[%c] = %d\n",(char) i,tab[i]);
    }
  }
  return;
}

int main(int argc, char ** argv){

  FILE * myfile, * filesrc;
  int i,tab[256],j;
  arbre huffman[256], alphabet[256];
  char * filename, *prevfilename, *extension, *fichorigin, *str;

  for(i=0;i<256;i++){
    tab[i]=0;
    huffman[i]=creerArbreVide();
    alphabet[i]=creerArbreVide();
  }


  filename = malloc(sizeof(char)*50000);
  prevfilename = malloc(sizeof(char)*50000);
  extension = malloc(sizeof(char)*50000);
  fichorigin = malloc(sizeof(char)*50000);
  str=malloc(sizeof(char)*50000);
  if(!filename || !prevfilename || !extension || !fichorigin || !str){
    printf("Erreur d'allocation.\n");
    exit(EXIT_FAILURE);
  }

  if(argc != 3){
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }
  else{
    switch(argv[1][1]){
      case 'c':
        /* compression */
        fichorigin=strdup(argv[2]);
        myfile = fopen(argv[2], "r");
        occurence(myfile, tab);
        for(i=0,j=0;i<256;i++){
          if(tab[i]){
            huffman[j] = creer_feuille(tab, i);
            j++;
          }
        }
        i=j;
        trierTableauArbre(huffman,j);
        printf("\n\n");
        creer_noeud(huffman,j);
        i=j+j-2;
        creer_code(huffman[i],0,0);
        for(j=0;j<=i;j++){
          if(huffman[j]->caractere){
            alphabet[(int)huffman[j]->caractere]=huffman[j];
          }
        }
        for(j=0;j<256;j++){
          if(alphabet[j]){
            strcpy(str,"");
            codeToBiStr(alphabet[j]->code,str);
            printf("%c -> %s (%d)\n",j,str,alphabet[j]->taillecode);
          }
        }
        filename = argv[2];
        prevfilename = argv[2];
        extension = "";
        filename=strtok(filename,"/");
        while(filename!=NULL){
          strcpy(prevfilename,filename);
          filename=strtok(NULL,"/");
        }
        extension = strdup(prevfilename);
        prevfilename = strtok(prevfilename,".");
        filename = strcat(prevfilename,".bc");
        myfile = fopen(filename,"wb+");

        ecrireEntete(myfile,extension,alphabet);
        filesrc = fopen(fichorigin, "rb");
        ecrireFichier(myfile,filesrc,alphabet);
        fclose(myfile);
        fclose(filesrc);
        break;
      case 'd':
        /* decompression */
        filesrc=fopen(argv[2],"rb");
        char file[2500];
        getFileName(file,filesrc);
        getArbre(filesrc,alphabet);
        myfile = fopen(file, "w+"); /*On écrase le fichier s'il existe dans le répertoire*/
        printf("Ouverture de :%s\n",file);
        getFileContent(filesrc, myfile, alphabet);
        fclose(myfile);
        fclose(filesrc);
        printf("\n");
        break;
      default:
        usage(argv[1]);
        break;
    }
  }
}

#endif
