#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void GeraSenha(char senha[], int tamanho, char caracteres[]) {

  int i;
  int tamCaracteres;

  char mai[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char min[] = "abcdefghijklmnopqrstuvwxyz";
  char num[] = "0123456789";
  char simb[] = "!@#$%&*?";

  tamCaracteres = strlen(caracteres);

  /* Garantia de senha forte */
  senha[0] = mai[rand() % strlen(mai)];
  senha[1] = min[rand() % strlen(min)];
  senha[2] = num[rand() % strlen(num)];
  senha[3] = simb[rand() % strlen(simb)];

  /* Completa o restante da senha */
  for(i = 4; i < tamanho; i++) {

    int posicao;

    posicao = rand() % tamCaracteres;

    senha[i] = caracteres[posicao];
  }

  senha[tamanho] = '\0';
}


