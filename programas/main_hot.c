#include <math.h> 
#include <stdint.h> 
#include <stdio.h> 
#include <sys/random.h> 
#include <string.h>
#include <stddef.h>
#include <sys/types.h> 
#include <stdlib.h> // exit faluire
#define SENHA_MAX 128

typedef struct { 
	const char *nome; 
	const char *caracteres; 
	size_t tamanho; 
	int habilitado;
} Conjunto;


void limpeza_segura(void *ptr, size_t tamanho);
void calcular_forca(size_t N ,size_t x );
size_t calcular_universo(Conjunto conjuntos[]);
size_t bits_necessarios(size_t universo);
void  entropia_final();
char obter_caractere(Conjunto conjuntos[],int qtd,size_t indice);
/* Cada campo representa: 
 	nome -> descrição do conjunto;
	caracteres -> string contendo os cadatcetes válidos
	tamanho -> quantidade de caracteres. 
	habilitado -> 0 ou 1.
*/ 

int main() { 
	// ----------- Declarações ---------------
	int conjunto; 
	int tamanho = 0; 
	unsigned char buff[1028]; // representação em bytes por casa, 1028 bytes, 1028 casas com 8. 

	Conjunto conjuntos[] = { 
		{ 	
		.nome= "Numeros",
		.caracteres= "0123456789", 
		.tamanho= 10, 
		.habilitado= 0
		},
		{ 
		.nome= "Minusculas",
		.caracteres= "abcdefghijklmnopqrstuvwxyz", 
		.tamanho= 26, 
		.habilitado= 0
		}, 
		{ 
		.nome= "Maiusculas", 
		.caracteres= "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 
		.tamanho= 26,
		.habilitado= 0
		},
		{ 
		.nome= "Especiais", 
		.caracteres= "!@#$%^&*()-_=+", 
		.tamanho= 15, 
		.habilitado= 0
		} 	
		
	}; 

	// ---------- Enunciado --------------	
	
	printf("Escolha os caracteres que serão usados na sua senha: \n");
        printf("\t1- Apenas números \n\t2- Letras minúsculas \n\t3-Alfanumerico \n\t4- Alfanumerico + simbolos: \t"); 
	
	while(scanf("%d", &conjunto) != 1) { 
		printf("\nDigite um valor válido: "); 		
		while(getchar() != '\n');
	} 	

	// ------- Ligado ou desligado. ------

	switch (conjunto){ 
		case 1: 
			conjuntos[0].habilitado = 1;
			break; 
		case 2:  
			conjuntos[1].habilitado = 1; 
			break;
		case 3: 
			conjuntos[0].habilitado = 1;
			conjuntos[1].habilitado= 1; 
			conjuntos[2].habilitado = 1; 
			break;
		case 4:
		       	conjuntos[0].habilitado = 1;
			conjuntos[1].habilitado = 1; 
			conjuntos[2].habilitado = 1; 
			conjuntos[3].habilitado = 1;
			break;
		default: 
			return 1; 
	} 

	printf("\nDigite o tamanho da senha, deverá ser entre 16 e 128 caracteres: "); 
	while(scanf("%d", &tamanho) != 1 || tamanho < 16 || tamanho > SENHA_MAX){ 
		printf("\nDigite um valor válido: "); 
		while(getchar() != '\n'); 
	}
       // ------------- Tamanho e conjunto capturados. 	
	
	ssize_t bytes = getrandom(buff, sizeof(buff), 0); // tamanho atual permite 1174 testes de amostragem com universo 4. 1028 x 8 / 7.  
	if(bytes == -1){ 
		perror("getrandom"); 
		return 1; 
		// ssize_t permite o bit de sinal, indicando se houve erro, atribuindo valor de bytes capturados com sucesso ou não para encerrar.
	
	}
       
	// ------------ Bytes de entropia capturados somente após aguardar respostas do usuário. 	
	
	printf("Foram gerados %zd bytes \n", bytes);
	
	/* mostrar os dados de entropia são apenas para fins demonstrativos. Não devem permanecer nos processos 
	
	for( int i= 0; i < bytes; i++){ 

		printf("%02X", buff[i]); 
	}
	printf("\n"); 
	*/	
	
	// ------- Variáveis para calculos importantes universo e bits
	size_t universo = calcular_universo(conjuntos); // calcula a soma dos conjuntos para determinar o universo 
	size_t bits_por_amostra = bits_necessarios(universo); // Retorna a quantidade de casas binarias necessarias para percorrer o universo. universo 10, é 4. 
	
	// --------  teste de força
	calcular_forca(universo, tamanho); // tamanho inserido pelo usuário
	entropia_final(universo, tamanho); // a força de entropia estimada H

//----------------- Declarações para amostragem 
	uint64_t mascara = (1ULL << bits_por_amostra) - 1; // mascara recebe as casas de bits que são necessárias para gerar uniformidade 0111 ou 01111
	uint64_t reservatorio_amostras = 0; // será usado para armazenar bits restantes quando remover x bits dos bytes conforme o tamanho do universo
	int bits_disponiveis = 0;  // para informar se tem bits na pool 
	size_t i_buff = 0;  // indice do buufer poderia também chamar i_buff
	char senha[SENHA_MAX + 1]; // resultado final
	size_t i_senha = 0; // indice da senha 

// --------- criação da senha

	while(i_senha < (size_t)tamanho){

		// ------------ Inicio de amostragem 
    		while(bits_disponiveis < (int)bits_por_amostra){ // enquanto meus bits disponíveis forem menores do que os bits pegue mais.
        		if(i_buff >= (size_t)bytes){ // pode causar comportamento inesperado, deveria solicitar nova entropia?				
			limpeza_segura(buff, bytes); 

			fprintf(stderr, 
				"Buffer esgotado!.\n Tente novamente.\n"); 
        		exit(EXIT_FAILURE); 
        		}

        	// ------ empilhamento de bits
			
			reservatorio_amostras |= ((uint64_t)buff[i_buff] << bits_disponiveis); // coloca a próxima caixa na posição igual ao número de caixas existentes na pool, OR garante a preservação acumulada. 
        		bits_disponiveis += 8;// muda a posição de empilhamento
        		i_buff++; // avança no vetor de entropia. 
		
    		}

    			if(bits_disponiveis < (int)bits_por_amostra){
				limpeza_segura(buff, bytes); 

				fprintf(stderr, 
					"Entropia insuficiente.\n"); 
        			exit(EXIT_FAILURE); 
    			}

		// Aplicação da amostragem

    		size_t amostra  = reservatorio_amostras & mascara; // valor sempre será substituido pelos digitos menos significantes da mascara marcados na mascara. 

    		reservatorio_amostras >>= bits_por_amostra; // bits eliminados da pool
    		bits_disponiveis -= bits_por_amostra; // bits disponíveis são deduzidos da quantidade que bits possui

		// Rejection Sampling, amostragem por rejeição 
    		if(amostra  >= universo){// 
        	continue;
    		}

		// Aplicação do caractere 

    		char letra = obter_caractere(conjuntos,4,amostra);
    		senha[i_senha++] = letra;
		printf("%c", letra); // considerar apenas por motivos de visualização 
	}

	senha[i_senha] = '\0';

	// Resultados demonstrativos sem aplicação técnica 
	printf("\n"); 
	printf("Gerados %zu de %d\n", i_senha, tamanho); // unicamente demonstrativo
        printf("Bytes consumidos: %zu/%d\n", i_buff,bytes); 	// ## ## 
	//printf("\nSenha: %s\n", senha); acaba possuindo falhas de reprodução por algum motivo


	// limpeza de memória. 
	for(int k= 0; k <= 2; k++)
	{	
		limpeza_segura(buff, bytes); 
		limpeza_segura(senha, tamanho + 1); 

		limpeza_segura(&reservatorio_amostras, sizeof(reservatorio_amostras)); 
		limpeza_segura(&mascara, sizeof(mascara)); 
	} 
	bits_disponiveis = 0;
	i_buff = 0;
	i_senha = 0;
	universo = 0;
	bits_por_amostra = 0;

	return 0;
	} 
// -------- Fim da main -------	

void limpeza_segura(void *ponteiro, size_t tamanho)// void para ponteiro genérico aumentando reaproveitamento
{
    volatile unsigned char *p = ponteiro;

    while (tamanho--) {
        *p++ = 0; // consumindo bytes sobrescrevendo com zero
    }
}

size_t calcular_universo(Conjunto conjuntos[]) { 
	size_t universo= 0;

	for(int i= 0;i < 4; i++){ 
		if(conjuntos[i].habilitado){ 
			universo+= conjuntos[i].tamanho; 
		}
	}
	return universo; 
	} 

size_t bits_necessarios(size_t universo){ 
		// Os valores do universo são calculados conforme a base 2, se 2⁶ é 64 e universo possui 62, ele ira retornar com 6, pois é o menor número de bits necessários para representar todos os números do universo. 2^(bits).
		size_t bits= 0;
		size_t valor= 1;

		while(valor < universo){ // é menor que o universo? então 1 bit para valor, uma casa binaria
		valor <<= 1; // caucula porência de 2
		bits++; 
		} 
		return bits;
	} 
char obter_caractere(Conjunto conjuntos[],int qtd, size_t indice) // struct conjunto, quantidade de structs, indice posicional após teste de rejeição. 
	{
    		for(int i = 0; i < qtd; i++){// vasculha valores habilitados da struct
        		if(!conjuntos[i].habilitado){	
            		continue;
        	}

        	if(indice < conjuntos[i].tamanho){// se o indice for menor do que os conjuntos retorna valor válido
            		return conjuntos[i].caracteres[indice]; 
	       	}

        	indice-= conjuntos[i].tamanho; // se valido for maior do que o conjunto vasculhado, ele procura no próximo habilitado o número do indice. 
    		}
		
		fprintf(stderr, 
			"Erro interno: Indice=%zu não encontrado.\n Tente novamente!", indice) ;
		exit(EXIT_FAILURE); 
    		
	}
void calcular_forca(size_t N ,size_t x )
{ 	
	// size_t area = (size_t)pow(N,x); Devido a magnitude dos números não é possível na maioria dos casos exibilos.
	printf("\nArea de busca possível: %zu^%zu.\n", N, x); 
	
	return ; 
}
void entropia_final(size_t N, size_t x)
{
	double H = x * log2((double)N); 
	printf("Entropia: %.3f bits\n", H);
	return;
} 	
