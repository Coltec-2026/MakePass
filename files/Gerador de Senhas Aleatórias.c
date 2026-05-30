/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/******************************************************************************
  Projeto Final - Laboratório de Programação
  Tema: Gerador de Senhas Aleatórias

  Objetivo:
  Gerar senhas aleatórias utilizando strings e funções.

  Funcionalidades:
  - Escolher tamanho da senha
  - Escolher tipos de caracteres
  - Gerar senha aleatória
  - Verificar força da senha
  - Salvar senha em arquivo texto

  Autor: Ana Thereza Naback
******************************************************************************/

/* Bibliotecas utilizadas */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TAM_MAX 100

/* void MontaCaracteres(char caracteres[], int mai, int min, int num, int simb)

  Entradas:
    caracteres: Vetor que armazenará os caracteres permitidos
    mai: Define uso de letras maiúsculas
    min: Define uso de letras minúsculas
    num: Define uso de números
    simb: Define uso de símbolos

  Saída:
    Vetor caracteres preenchido
*/
void MontaCaracteres(char caracteres[], int mai, int min, int num, int simb) {

  strcpy(caracteres, "");

  if(mai == 1) {
    strcat(caracteres, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  }

  if(min == 1) {
    strcat(caracteres, "abcdefghijklmnopqrstuvwxyz");
  }

  if(num == 1) {
    strcat(caracteres, "0123456789");
  }

  if(simb == 1) {
    strcat(caracteres, "!@#$%&*?");
  }
}

/* void GeraSenha(char senha[], int tamanho, char caracteres[])

  Entradas:
    senha: Vetor que armazenará a senha
    tamanho: Quantidade de caracteres da senha
    caracteres: Vetor contendo os caracteres permitidos

  Saída:
    Senha aleatória gerada
*/
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

/* int VerificaSenhaForte(char senha[])

  Entrada:
    senha: Senha gerada

  Saídas:
    0: Senha fraca
    1: Senha forte
*/
int VerificaSenhaForte(char senha[]) {

  int i;

  int maiuscula = 0;
  int minuscula = 0;
  int numero = 0;
  int simbolo = 0;

  if(strlen(senha) < 8) {
    return 0;
  }

  for(i = 0; senha[i] != '\0'; i++) {

    if(isupper(senha[i])) {
      maiuscula = 1;
    }

    else if(islower(senha[i])) {
      minuscula = 1;
    }

    else if(isdigit(senha[i])) {
      numero = 1;
    }

    else {
      simbolo = 1;
    }
  }

  if(maiuscula && minuscula && numero && simbolo) {
    return 1;
  }

  return 0;
}

/* void SalvaArquivo(char senha[])

  Entrada:
    senha: Senha gerada

  Saída:
    Arquivo texto contendo a senha
*/
void SalvaArquivo(char senha[]) {

  FILE *arquivo;

  arquivo = fopen("senhas.txt", "a");

  if(arquivo == NULL) {

    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  fprintf(arquivo, "Senha Gerada: %s\n", senha);

  fclose(arquivo);

  printf("Senha salva no arquivo com sucesso.\n");
}

/* Função Principal */
int main() {

  int tamanho;

  int usarMai;
  int usarMin;
  int usarNum;
  int usarSimb;

  int salvar;

  char caracteres[TAM_MAX];
  char senha[TAM_MAX];

  /* Inicialização da função rand */
  srand(time(NULL));

  printf("====================================\n");
  printf("   GERADOR DE SENHAS ALEATORIAS\n");
  printf("====================================\n");

  /* Tamanho da senha */
  printf("Digite quantos caracteres a senha deve ter: ");
  scanf("%d", &tamanho);

  /* Verifica tamanho válido */
  while(tamanho < 8 || tamanho >= TAM_MAX) {

    printf("Tamanho invalido.\n");
    printf("Digite um valor entre 8 e 99: ");
    scanf("%d", &tamanho);
  }

  printf("\nDigite 1 para SIM ou 0 para NAO.\n");

  /* Escolha dos caracteres */
  printf("Usar letras maiusculas? ");
  scanf("%d", &usarMai);

  printf("Usar letras minusculas? ");
  scanf("%d", &usarMin);

  printf("Usar numeros? ");
  scanf("%d", &usarNum);

  printf("Usar simbolos? ");
  scanf("%d", &usarSimb);

  /* Verifica se pelo menos uma opcao foi escolhida */
  while(usarMai == 0 && usarMin == 0 &&
        usarNum == 0 && usarSimb == 0) {

    printf("\nEscolha pelo menos um tipo de caractere.\n");

    printf("Usar letras maiusculas? ");
    scanf("%d", &usarMai);

    printf("Usar letras minusculas? ");
    scanf("%d", &usarMin);

    printf("Usar numeros? ");
    scanf("%d", &usarNum);

    printf("Usar simbolos? ");
    scanf("%d", &usarSimb);
  }

  /* Monta vetor de caracteres */
  MontaCaracteres(caracteres, usarMai,
                  usarMin, usarNum, usarSimb);

  /* Gera senha */
  GeraSenha(senha, tamanho, caracteres);

  /* Exibe senha */
  printf("\nSenha gerada automaticamente: %s\n", senha);

  /* Verifica força */
  if(VerificaSenhaForte(senha) == 1) {

    printf("Senha FORTE.\n");

  } else {

    printf("Senha FRACA.\n");
  }

  /* Salvar arquivo */
  printf("\nDeseja salvar a senha em arquivo?\n");
  printf("1 - SIM\n");
  printf("0 - NAO\n");
  scanf("%d", &salvar);

  if(salvar == 1) {

    SalvaArquivo(senha);

  } else {

    printf("Senha nao salva.\n");
  }

  printf("\nPrograma Finalizado.\n");

  return 0;
}