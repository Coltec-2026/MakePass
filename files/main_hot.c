#include <stdint.h> 
#include <stdio.h> 
#include <sys/random.h> 
#include <string.h>
#include <sys/types.h> 
#define SENHA_MAX 128

typedef struct { 
	const char *nome; 
	const char *caracteres; 
	size_t tamanho; 
	int habilitado;
} Conjunto; 
size_t calcular_universo(Conjunto conjuntos[]);
size_t bits_necessarios(size_t universo);
char obter_caractere(Conjunto conjuntos[],int qtd,size_t indice);

/* Cada campo representa: 
 	nome -> descrição do conjunto;
	caracteres -> string contendo os cadatcetes válidos
	tamanho -> quantidade de caracteres. 
	habilitado -> 0 ou 1.
*/ 

int main() { 
	//Preferencias  p= {0,0,0,0}; 
	int conjunto; 
	int tamanho = 0; 
	unsigned char buff[64]; 

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
	
	printf("Escolha os caracteres que serão usados na sua senha: \n");
        printf("\t1- Apenas números \n\t2- Letras minúsculas \n\t3-Alfanumerico \n\t4- Alfanumerico + simbolos: \t"); 
	
	while(scanf("%d", &conjunto) != 1) { 
		printf("\nDigite um valor válido: "); 		
		while(getchar() != '\n');
	} 	
	
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
	//printf("\nOs valores preenchidos são: %d, %d, %d e %d. ", p.numeros, p.minusculas, p.maiusculas, p.especiais); 

	printf("\nDigite o tamanho da senha, deverá ser entre 16 e 128 caracteres: "); 
	while(scanf("%d", &tamanho) != 1 || tamanho < 16 || tamanho > SENHA_MAX){ 
		printf("\nDigite um valor válido: "); 
		while(getchar() != '\n'); 
	} 
	ssize_t bytes = getrandom(buff, sizeof(buff), 0); 
	if(bytes == -1){ 
		perror("getrandom"); 
		return 1; 
	} 
	printf("Foram gerados %zd bytes \n", bytes); 
	for( int i= 0; i < bytes; i++){ 

		printf("%02X", buff[i]); 
	}
	printf("\n"); 

		
	
	size_t universo = calcular_universo(conjuntos); 
	size_t bits = bits_necessarios(universo);
	char obter_caractere(
    Conjunto conjuntos[],
    int qtd,
    size_t indice)
{
    for(int i = 0; i < qtd; i++)
    {
        if(!conjuntos[i].habilitado)
        {
            continue;
        }

        if(indice < conjuntos[i].tamanho)
        {
            return conjuntos[i].caracteres[indice];
        }

        indice -= conjuntos[i].tamanho;
    }

    return '?';
}
//-----------------
	uint64_t mascara = (1ULL << bits) - 1;
	uint64_t pool_acumulador = 0;
	int bits_disponiveis = 0;
	size_t pos_buff = 0;
	char senha[SENHA_MAX + 1];
	size_t pos_senha = 0;

while(pos_senha < (size_t)tamanho)
{
    while(bits_disponiveis < (int)bits)
    {
        if(pos_buff >= (size_t)bytes)
        {
            break;
        }

        pool_acumulador |=
            ((uint64_t)buff[pos_buff] << bits_disponiveis);

        bits_disponiveis += 8;

        pos_buff++;
    }

    if(bits_disponiveis < (int)bits)
    {
        break;
    }

    size_t valor =
        pool_acumulador & mascara;

    pool_acumulador >>= bits;

    bits_disponiveis -= bits;

    if(valor >= universo)
    {
        continue;
    }

    char letra =
        obter_caractere(
            conjuntos,
            4,
            valor
        );

    senha[pos_senha++] = letra;
}

senha[pos_senha] = '\0';

printf("\nSenha: %s\n", senha);

return 0;
} 
size_t calcular_universo(Conjunto conjuntos[]) 
{ 
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

	while(valor < universo)
	{ 
		valor <<= 1;
		bits++; 
	} 
	return bits;
} 

