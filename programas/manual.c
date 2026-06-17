#include <stdio.h> 
#include <math.h> 
int main(){ 
printf(
"         █████\n"
"         █████▓\n"
"█████████████▓▒\n"
"█████████████▓▒\n"
"         █████▓▒\n"
"         █████▓▒\n"
"Abaddom V1.0 \n"); 


printf("Valores expressos em bits de entropia.\n");
printf("+----------------------+----------+----------+----------+----------+\n");
printf("| Conjunto             | 16 car.  | 20 car.  | 24 car.  | 30 car.  |\n");
printf("+----------------------+----------+----------+----------+----------+\n");
printf("| Numeros (10)         |  53.1    |  66.4    |  79.7    |  99.6    |\n");
printf("| Minusculas (26)      |  75.2    |  94.0    | 112.8    | 141.0    |\n");
printf("| Alfanumerico (62)    |  95.2    | 119.0    | 142.8    | 178.5    |\n");
printf("| Alfa+Especial (77)   | 100.3    | 125.4    | 150.5    | 188.1    |\n");
printf("+----------------------+----------+----------+----------+----------+\n");

printf(" Tabela de classificação de dificuldades "); 
printf("+----------------------+-------------------+\n");
printf("| Entropia             | Classificacao     |\n");
printf("+----------------------+-------------------+\n");
printf("| Menor que 2^40       | Muito facil       |\n");
printf("| 2^40 ate 2^55        | Facil             |\n");
printf("| 2^56 ate 2^63        | Possivel          |\n");
printf("| 2^64 ate 2^79        | Dificil           |\n");
printf("| 2^80 ate 2^127       | Quase impossivel  |\n");
printf("| 2^128 ou superior    | Impossivel        |\n");
printf("+----------------------+-------------------+\n");

printf("Valores da potência expressos em bits de entropia.\n");

printf("\n- O universo N representa a quantidade de caracteres disponíveis para a geração da senha. O valor de x representará o comprimento.\n"); 
printf("\n- C = N^(x) representa o espaço de busca da senha. Calcula a quantidade total de combinações possíveis. "); 
printf("\n- H= x * log2(N) estima a entropia teorica da senha, medida em bits de incerteza. O universo simples mas grande em tamanho é mais incerto e difícil de ser determinado do que um universo complexo mas pequeno. O que significa que a complexidade multiplia o grau de incerteza, mas o tamanho a aumenta exponencialmente. \n"); 
printf("\n\nPara que o resultado de calculo de força represente a entropia teórica da senha, as seguintes condições deverão ser atendidas: "); 
printf("\n\t1. A fonte de entropia deverá fornecer aleatoriedade suficientemente imprevisível.\n\t2. A distribuição da probabilidade dos caracteres deverá ser uniforme.\n\t3. O viés estatístico deverá ser mitigado durante o processo de seleção. \n\t4. Cada caractere escolhido de forma independente dos demais.\n\t5. Somente quando todas as condições forem atendidas a força estimada poderá ser determinada. A precisão dessa estimativa depende da validade das hipóteses adotadas, da qualidade da fonte de aleatoriedade utilizada e da ausência de vieses no processo de geração. \n"); 
printf("\n\n- A incerteza final nunca pode ser maior do que a incerteza inicial.\n- A reutilização de senhas, se vazadas, atribui máxima certeza ao atacante. Guarde as certezas e as entregue somente para os meios e os fins determinados.\n- O tempo reduzirá as incertezas do passado se não se preparar para o futuro, olhe para frente e a incerteza será tão grande que somente você poderá encontrá-la. "); 
printf("\n\n\t Se cada senha possível fosse uma estrela, aumentar o conjunto de caracteres adicionaria mais estrelas a cada galáxia. Aumentar o comprimento criar novas galáxias inteiras. \n\n"); 

return 0; 
} 



