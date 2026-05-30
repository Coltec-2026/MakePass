 
#ifndef VERIFICATAMANH_H
#define VERIFICATAMANHO_H


#include <stdio.h>

#define TAM_MAX 100
 /* Verifica tamanho válido */
  void verificarTamanho(int *tamanho){
  while(*tamanho < 8 || *tamanho >= TAM_MAX) {

    printf("Tamanho invalido.\n");
    printf("Digite um valor entre 8 e 99: ");
    scanf("%d",tamanho);
  }}
  #endif
