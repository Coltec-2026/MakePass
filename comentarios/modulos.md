# Importações 

O cabeçalho do código possui importações, essas importações são caracteristica da modularidade do código, em sua estrutura final é apresentado uma arquitetura modular, onde funções executam pequenas partes que permitem modificações sem a necessidade de reescrever todo o arquivo da main. 
Essa ideia é a implementação da arquitetura limpa, que permite ao programador incluir funcionalidades e modificar o sistema em mudanças de estrutura. A diferença entre um código que nasce sem vida, e um que permite manutenção e garante um ciclo de desenvolvimento longo.


# Entropia
  Em principio a função srand() foi utilizada para capturar do time() a semente inicial para entropia(aleatoriedade) da senha, a função rand foi usada posteriormente para inserir valores aleatórios nas posições em posições iniciais do array da senha, e depois a senha era embaralhada pelo algorítimo de ficher yates
O problema: Se um atacante souber que usei este software para gerar a senha, e ele usa a hora do sistema para capturar um valor pseudo aleatorio do sistema, não sendo entropia real, e passando por um sistema de embaralhamento previsivel, a engenharia reversa para que a senha seja quebrada se torna rápida, trivial e barata.
Como solução para esse problema, foi utilizado o arquivo urandon /dev/urandm do sistema (Baseado em linux). Esse arquivo contem aleatoriedade matematica, é uma interface para o gerador de números aleatórios criptograficamente seguros do kernel (CSPRNG) que é alimentado por diversas fontes de entropia; Pode ser movimento do mouse, pacotes de rede, operações de disco e etc. Se caso o mesmo método for usado no windows deverá ser feito pelo BCryptGenRandom da biblioteca Bcrypt.h.
Esse método  previne totalmente falhas de telemetria, inpossibilitando o processo engenharia reversa, caso nos  basearmos somente na entropia inicial. A derivação criptográfica costuma ser ser feita com protocolo Chaccha20 e funciona como um liquidificador do kernel. 

# Tamanho da senha


Conforme o estudo apresentado pela hive system usando hashcat, o tamanho da senha é principal diferença entre uma senha fraca e uma senha forte, significa que o esforço bruto aumenta exponencialmente a dificuldade apresentada para quebra da criptografia através da força bruta. Calculo matemático que será exibido mais a frente. 
 
Nos estudos usando hashcat senhas com até 8 caracteres, a depender do arsenal do atacante podem ser quebradas instantaneamente; Combinadas, juntamente com o padrão de criptografia do sistema atacado, sendo o mais antigo e obseleto do estudo,  MD5. 
Atualmente se utiliza para criptografias mais fortes,o bcrypt; Que aumenta significativamente o processo de quebra criptografica pelo esforço computacional.
Desde que os estudos foram iniciados em 2021, o uso do treinamento de inteligencia artificial como o chatgpt 3 e 4, representaram o maior impacto de todos em relação ao processamento; Modelos de IA tem aperfeiçoado o poder computacional do hardware em até 20 vezes, asssim como faz o Teoria da bussca Bayseana; 
Se fizermos uma analogia, poderia ajudar a reduzir o tempo de busca de um navio perdido no mar separando-o em pequenas células, e usando análise estatista e probabilistica a cada novo espaço procurado para acertar o local correto. Computação inteligente, usando dados para reduzir o tempo de busca de padrões aplicados a senhas.

Dado a essas circunstâncias o reuso das senhas é fator mais crítico para sistemas de segurança com senhas, pois um único vazamento faz com que seja quebrada instantâneamente. 

Em 2024 seria possível afirmar, que uma estruturas de bits de tamanho  
* 2⁴⁰ como fácil de ser quebrada
* 2⁵⁶ fácil
* 2⁶⁴ como possível
* 2⁸⁰ como razoavel
* 2¹²⁸ impossível. 
Nessa mesma época, o processamento de hashs da rede do Bitcoin atingiu 2⁸⁰ hashes por hora. 
Essa teoria é baseada na arquitetura de computadores atuais e na fisica termodinamica. Ainda hoje ainda é aceitada, pois mesmo com a implementação da inteligência artificial e a teoria da busca Bayseana, o desafío do `Bitcoin puzzle  transactions`  só registrou a quebra da chave de 130 bits.
Mas 130 bits não é inquebrável? Sim, essa quebra só ocorreu, por uma vulnerabilidade matemática da chave pública; O calculo das curvas elipticas derrubou o número de tentativas para 2⁶⁴, tornando possível para grandes poderes computacionais uma quebra criptográfica pelo processamento bruto. Ainda hoje o bitcoin é a maior referência de poder computacional do mundo. Seja pelos seus hashes por hora, seja pelos desafios de recompensas monetárias pela quebra das chaves públicas. 
Curiosidade: Satoshi nakamoto possui mais de um milhao de bitcoins espalhados em vários endereços com a chave publica exposta em tamanho de 256 bits. A recompensa pela quebra criptográfica é possívelmente a maior da história. 

A função de verificação de tamanho é modular e customizavel, sendo contruida recebendo o valor de tamanho, mínimo e máximo como parâmetros de função e validando o tamanho pedido; Para que seja interativo e a mensagem seja exibida na tela o `sprintf` armazena os valores das dos parâmetros da função. Enquanto o tamanho digitado pelo usuário não for válido a condição irá força-lo a colocar um valor aceito. 
Para a primeira etapa será  entre 16 e 512 caracteres correspondendo ao tamanho da senha, e como reutilização do código só aceitará valores entre 0 e 1.  

# Força

C = N⁽x⁾ 

N= O número de caracteres possíveis no conjunto; Se usar apenas letras minúsculas N=26. Maiusculas,números e simbolos  N=95. 
x = Comprimento. 
Portanto, enquanto o tipo de caratere multiplica a força da senha, o tamanho aumenta a força exponencialmente. Isso significa que se um invasor duplica o poder computacional para o hashcat  processar testes, reduz muito mais o tempo do que um pequeno aumento na quantidade de caracteres, que o tempo de processamento de alguns dias para milhões ou bilhões de anos.
 Orgãos como o NIST confirma que frases longas e fáceis de lembrar são infinitamente mais seguras do que senhas curtas, complexas e difíceis de digitar.

ATENÇÃO
Tudo o que foi falado vale para boas aplicações de geração de senhas é sobre a hipótese muito importante, que as senhas sejam geradas de formas verdadeiramente aleatória e uniforme, escolhendo cada caractere independentemente, dentro de um alfabeto de tamanho N..
**Senhas geradas por humanos** reduzem significativamente o tempo de ataque, pois pessoas usam palavras do dicionário, utilizam datas, nomes, padrões de teclas do teclado, substituições previsiveis de letras por caracteres especiais, reutilizam estruturas semelhantes. Portanto, o teste de força da senha é limitado.E o teste de força assume que a entropia é segura, e a distribuição é uniforme, aplica ``H= x log2(N)``.

Entropia prevista por caractere: 

*Apenas números(10)     3,32 bits  
*Letras minúsculas(26)  4,70 bits
*Letras + números(62)   5,95 bits
*ASCII imprimiveis(95) 6,57
 
Adicionar opção no código para teste de força de senha acaba sendo impraticável neste ponto de desenvolvimento. Caso não tenha sido gerada internamente no sistema, pois não é possível garantir a entropia da senha gerada por outros, nem prever ataques a senhas geradas por humanos.
 
-[] Alguns dos programas poderão ser compilados e usados individualmente, graças a isso podem se comportar com modularidade e serem atribuidos a variáveis de ambiente dentro do shell, sendo invocados como ferramentas de sistema importadas, semelhantes a ferramentas do padrão unix. O que não significa que sua formatação e função sirva para os propósitos intencionados, ou cubram com segurança as necessidades desejadas, apesar de não possuir código malicioso. 
 
# Verificar o tipo número  

Função que faz o tratamento de entrada de valores de caracteres digitados pelo usuário. Recebe do sistema mensagem de erro e enunciado a ser exibido na tela interativa e captura do usuário o valor digitado que se verdadeiro para tipo número retorna o valor digitado em uma variável simples, se não entra no laço e faz a limpeza do buffer repetindo até o valor ser válido imprimindo a mensagem de erro. 
