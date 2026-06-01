#include <stdio.h>

int verificarDigitacao(const char *mensagem_inicial,const char *mensagem_err){
	int buff, valor_digitado;
	
	printf("%s", mensagem_inicial);
	while (scanf("%d", &valor_digitado) != 1){ // verifica o retorno de scanf, se diferente de número, executa o laço.	

		printf("%s", mensagem_err);
		
		
		while((buff = getchar()) != '\n' && buff != EOF); // limpa o buffer do teclaco
	}
		while((buff = getchar()) != '\n' && buff != EOF); // limpa o enter da digitação

return valor_digitado;
	}

