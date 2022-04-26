#ifndef _TABLEAU_C_
#define _TABLEAU_C_

#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<unistd.h>
#include"tableau.h"
#include"noeud.h"

void rechercherDeuxMin(arbre huffman[256], int taille){
  int i, j;
  arbre ntmp;
  for(i=0;!huffman[i]->occurence;i++){
    ;
  }
  for(;i<taille-1;i++){
    if(huffman[i]->occurence){
      for(j=i+1;j<taille;j++){
        if(huffman[i]->occurence>huffman[j]->occurence && huffman[j]->occurence){
          ntmp = huffman[i];
          huffman[i]=huffman[j];
          huffman[j]=ntmp;
        }
      }
    }
  }
  return;
}


#endif
