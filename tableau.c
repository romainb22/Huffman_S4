#ifndef _TABLEAU_C_
#define _TABLEAU_C_

#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<unistd.h>
#include"tableau.h"
#include"noeud.h"

void rechercherDeuxMin(arbre huffman[256], int taille){
  int i, j, tmp, min, k=0;
  arbre ntmp;
  for(i=0;i<taille-1;i++){
    min = huffman[i]->occurence;
    for(j=i+1;j<taille;j++){
      printf("min : %d\n",min);
      if(huffman[j]->occurence<min){
        min = huffman[j]->occurence;
        k=j;
        printf("Found : %c | %d\n", huffman[j]->caractere, huffman[j]->occurence);
        usleep(1000000);
      }
    }
    if(min<huffman[i]->occurence){
      tmp = huffman[i]->occurence;
      ntmp = huffman[i];
      huffman[i]->occurence = huffman[k]->occurence;
      huffman[i] = huffman[k];
      huffman[k]->occurence=tmp;
      huffman[k]=ntmp;
    }
    printf("Next:\n");
  }
  return;
}


#endif
