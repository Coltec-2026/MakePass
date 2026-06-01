#include <stdio.h>

#define TAM_MAX 100
 /* Verifica tamanho válido */
  int verificarTamanho(int tamanho_valido){
  while(tamanho_valido < 8 || tamanho_valido >= TAM_MAX) {

    printf("Tamanho invalido.\n");
    printf("Digite um valor entre 8 e 99: ");
    scanf("%d", &tamanho_valido);
  }
  return tamanho_valido;
  }
