/******************************************************************************
  Tema: Gerador de Senhas Aleatórias
  Funcionalidades:
  - Escolher tamanho da senha
  - Escolher tipos de caracteres
  - Gerar senha aleatória
  - Verificar força da senha
  - Salvar senha em arquivo texto

/* Bibliotecas utilizadas */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <secp256k1.h>
#include <string.h>

#define TAM_MAX 100

// importadas
int verificarTamanho(int tamanho_valido);
int verificarDigitacao(const char *mensagem_inicial,const char *mensagem_err);	
int VerificaSenhaForte(char senha[]);
// locais
void MontaCaracteres(char caracteres[], int mai, int min, int num, int simb);
void GeraSenha(char senha[], int tamanho, char caracteres[]);
void SalvaArquivo(char senha[]);

int main() {
  
  // variaveis prenchidas pelo usuario que não são inicializadas podem gerar erro de comportamento.	
  int tamanho = 0;
  int usarMai, usarMin, usarNum, usarSimb, salvar;
  char caracteres[TAM_MAX];
  char senha[TAM_MAX];

  /* Inicialização da função rand */
  srand(time(NULL));

  printf("====================================\n   GERADOR DE SENHAS ALEATORIAS\n ====================================\n");

  /* Tamanho da senha */
 tamanho =  verificarDigitacao( "Digite quantos caracteres a senha deve ter: ",  "Erro: Voce não digitou um número válido! \n Digite novamente: ");

/* Verifica tamanho válido */ 
tamanho = verificarTamanho(tamanho);

  printf("\nDigite 1 para SIM ou 0 para NAO.\n");

  /* Escolha dos caracteres */
do{
usarMai = verificarDigitacao("Usar letras maiusculas? ", "Erro, digite novamente: " );  

usarMin = verificarDigitacao("Usar letras minusculas? ", "Erro, digite novamente: ");

usarNum = verificarDigitacao("Usar numeros? ", "Erro, digite novamente: ");

usarSimb = verificarDigitacao("Usar simbolos? ", "Erro, digite novamente: ");

if(usarMai == 0 && usarMin == 0 && usarNum == 0 && usarSimb == 0){
 printf("Preencha pelo menos um valor válido! \n ");}
}while(usarMai == 0 && usarMin == 0 && usarNum == 0 && usarSimb == 0); 

      /* Monta vetor de caracteres */
  MontaCaracteres(caracteres, usarMai,usarMin, usarNum, usarSimb);

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
  salvar = verificarDigitacao("\nDeseja salvar a senha em arquivo?\n 1 - SIM\n 0 - NAO\n", "Erro, Digite um valor válido: ");
  if(salvar == 1) {

SalvaArquivo(senha);
} else {

    printf("Senha nao salva.\n");
  }

  printf("\nPrograma Finalizado.\n");

  return 0;

}

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
