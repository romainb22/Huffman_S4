#ifndef _QUESTION4_1_C_
#define _QUESTION4_1_C_

#include<stdio.h>
#include<stdlib.h>
#include <MLV/MLV_all.h>
#include"noeud.h"
#include"tableau.h"
#include"compression.h"

void usage(char * str){
  printf("Usage : %s [fichier] [entier]\n", str);
  printf("fichier : chemin vers le fichier texte à compresser\n");
  /*printf("entier : le nombre de caractère à lire dans ledit fichier\n\n");*/
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
    if(c!='\n'){
      tab[(int)c]++;
    }
    c = fgetc(myfile);
  }
  for(i=0;i<256;i++){
    if(tab[i]){
      printf("tab[%c] = %d\n",(char) i,tab[i]);
    }
  }
  return;
}
/*
void afficher_arbre_mlv(arbre a,int x,int y,int prof){
    int ecart=0;
    sleep(1);
    if(!estVide(a)){
      MLV_draw_text(x,y,"%c",MLV_COLOR_WHITE,a->caractere);
      MLV_draw_text(x+10,y,"%d",MLV_COLOR_RED,a->occurence);
      if(est_feuille(a)){
        MLV_draw_text(x+30,y,"%d",MLV_COLOR_BLUE,a->code);
      }
      MLV_actualise_window();
      afficher_arbre_mlv(a->fils_gauche,x-100/prof,y+40,prof+1);
      afficher_arbre_mlv(a->fils_droit,x+100/prof,y+40,prof+1);
      ecart-=20;
    }
}*/


int main(int argc, char ** argv){
  FILE * myfile;
  int i,tab[256],j;
  arbre huffman[256], alphabet[256];
  char * filename;
  /*char c;*/

  /*MLV_create_window("Menu","Menu", 800, 800);*/
  for(i=0;i<256;i++){
    tab[i]=0;
    huffman[i]=creerArbreVide();
    alphabet[i]=creerArbreVide();
  }
  if(argc != 2){
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }
  /*else{
    myfile = fopen(argv[1],"r");
    readNCharFromFile(myfile,atoi(argv[2]));
    fclose(myfile);
    printf("\n\n");
    myfile = fopen(argv[1],"r");
    readEntireFile(myfile);
    fclose(myfile);
  }*/
  myfile = fopen(argv[1], "r");
  occurence(myfile, tab);
  fclose(myfile);
  for(i=0,j=0;i<256;i++){
    if(tab[i]){
      huffman[j] = creer_feuille(tab, i);
      /*if(!(huffman[j] = malloc(sizeof(noeud)))){
        printf("Erreur d'allocation !\n");
      }
      else{
        huffman[j]->caractere = (char) i;
        huffman[j]->occurence = tab[i];
      }*/
      j++;
    }
  }
  /*for(i=0;i<j;i++){
    printf("caractère %c, occurence %d\n",huffman[i]->caractere,huffman[i]->occurence);
  }
  printf("\n\n");*/
  trierTableauArbre(huffman,j);
  for(i=0;i<j;i++){
    printf("caractère %c, occurence %d\n",huffman[i]->caractere,huffman[i]->occurence);
  }
  printf("\n\n");
  /*for(i=0;i<2;i++){
    printf("L'occurence la plus petite n°%d : %d (%c)\n",i+1,huffman[i]->occurence,huffman[i]->caractere);
  }*/
  /*n->occurence = huffman[0]->occurence + huffman[1]->occurence;
  n->caractere = '\0';
  printf("Occurence du nouveau noeud : %d\n", n->occurence);*/
  creer_noeud(huffman,j);
  /*printf("\n\n");
  for(i=0;i<j+j-1;i++){
    printf("caractère %c, occurence %d\n",huffman[i]->caractere,huffman[i]->occurence);
  }*/
  i--;
  creer_code(huffman[i],0,0);
  /*afficher_arbre_mlv(huffman[i],400,10,1);
  MLV_actualise_window();
  sleep(300);*/


  for(j=0;j<=i;j++){
    if(huffman[j]->caractere){
      alphabet[(int)huffman[j]->caractere]=huffman[j];
    }
  }

  for(i=0;i<256;i++){
    if(alphabet[i]){
      printf("%c au noeud %d\n",alphabet[i]->caractere,alphabet[i]);
    }
  }


  filename = strtok(argv[1],"/");
  filename = strtok(NULL,"/");
  filename = strtok(NULL,"/");
  filename = strtok(NULL,"/");
  filename = strtok(NULL,"/");
  filename = strtok(filename,".");
  printf("%s\n",filename);

  myfile = fopen("banane.comp","w");

  ecrireEntete(myfile,"banane.comp",alphabet);
  fclose(myfile);
  return 0;
}

#endif
