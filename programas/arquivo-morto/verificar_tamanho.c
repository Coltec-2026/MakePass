#include <stdio.h>

int verificarDigitacao(const char *mensagem_inicial,const char *mensagem_err);


/* Verifica tamanho válido */
int verificarTamanho(int tamanho_valido, int tam_min, int tam_max){
	char valores[35];
	sprintf(valores, "Digite um valor entre %d e %d", tam_min, tam_max); // nunca usar sprintf puro em produção? substituir por snprintf que limita a escrita ao tamanho do buffer e empede a invasão de memória.  
  while(tamanho_valido < tam_min || tamanho_valido >= tam_max) {

    printf("Tamanho invalido.\n");
    tamanho_valido = verificarDigitacao( valores, "Tamanho invalido, digite novamente: ");
  }
  return tamanho_valido;
  }
