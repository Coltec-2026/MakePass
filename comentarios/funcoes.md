conjunto - valor escolhido pelo usuário para selecionar conjuntos da struct
buff - tipo char e tem 1 byte por possição, é um vetor de bits de aleatoriedade.tamanho - Valor escolhido pelo usuário para o tamanho da senha desejada.

bytes - recibo do retorno dos bytes de entropia e o tamanho recebido
universo - a soma total dos carateres de conjunto, definido na struct em um dos campos
bits - Recebe o resultado de 2^(bits) >= universo, enquanto o valor for menor do que o universo ele vai somar bits na função de bits necessários, com auxilio da variável local (valor) que calcula potência de 2. 

mascara - recebe em binário 1ULL todos os bits necessários, por exemplo 16 resultado da potência de dois que é 10000, porém com -1 vira 01111, e os bits 1 servirão como mascara de extração. A limitação matematica dessa variável é 64 bytes. Dado a potência de 2 em bits, porêm não existe um universo tão grande no código.Esse fatiamento de bytes ocorre para não desperciçãr entropia. Talvez, uma forma mais simples seja usar o byte mesmo, dividir por ele, jogar o restante fora e se der errado pedir entropia de novo. 

pool-acumulador - guarda bits dispensados pelo usu da masca, sua unica função é reaproveitar entropia. 
