#include <stdio.h>

int verificarDigitacao(const char *mensagem_inicial,const char *mensagem_err);

#define TAM_MAX 100

/* Verifica tamanho válido */
int verificarTamanho(int tamanho_valido){
  while(tamanho_valido < 8 || tamanho_valido >= TAM_MAX) {

    printf("Tamanho invalido.\n");
    tamanho_valido = verificarDigitacao("Digite um valor entre 8 e 99: ", "Tamanho invalido, digite novamente:\n");
  }
  return tamanho_valido;
  }
