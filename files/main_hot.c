#include <stdio.h> 

typedef struct {
	int numeros;
	int minusculas;
	int maiusculas; 
	int especiais; 
} Preferencias;  

int main() { 
	Preferencias  p= {0,0,0,0}; 
	int conjunto; 
	int tamanho = 0; 

	printf("Escolha os caracteres que serão usados na sua senha: \n");
        printf("\t1- Apenas números \n\t2- Apenas letras minúsculas \n\t3- Letras maiúsculas, minúsculas e números \n\t4- ASCII completo, todas as opções + simbolos: \t"); 
	
	while(scanf("%d", &conjunto) != 1 || conjunto > 4 || conjunto <= 0) { 
		printf("\nDigite um valor válido: "); 		while(getchar() != '\n');
	} 	
	switch (conjunto){ 
		case 1: 
			p.numeros = 1;
			break; 
		case 2:  
			p.minusculas = 1; 
			break;
		case 3: 
			p.minusculas = 1;
			p.maiusculas = 1; 
			p.numeros = 1; 
			break;
		case 4:
		       	p.minusculas = 1;
			p.maiusculas = 1; 
			p.numeros = 1; 
			p.especiais = 1;
			break;
		default: 
			return 1; 
	} 
	printf("\nOs valores preenchidos são: %d, %d, %d e %d. ", p.numeros, p.minusculas, p.maiusculas, p.especiais); 

	return 0;
} 
