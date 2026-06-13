# Importações 

O cabeçalho do código possui importações, essas importações são caracteristica da modularidade do código, em sua estrutura final é apresentado uma arquiteturamonolitica modular atravez da compilação com gcc, onde funções executam pequenas partes que permitem modificações sem a necessidade de reescrever todo o arquivo da main. 
Essa ideia é a implementação da arquitetura limpa, que permite ao programador incluir funcionalidades e modificar o sistema em mudanças de estrutura. A diferença entre um código que nasce sem vida, e um que permite manutenção, garantindo um ciclo de desenvolvimento longo.


# Entropia
  Em principio, a função srand() foi utilizada com time() para zerar a contagem atravez do relógio do computador. Entretanto, a entropia(aleatoriedade) da senha atravez da função rand(), que foi usada para inserir valores que mais tarde, foram identificados como pseudo aleatórios, estes que eram inseridos  em posições iniciais do vetor da senha, e depois a senha era embaralhada pelo algorítimo de ficher yates.
O problema: Se um atacante souber que usei este software para gerar a senha, e ele usa a hora do sistema para capturar um valor pseudo aleatorio gerado. Essa não é uma entropia real. Passar por um algoritimo de embaralhamento previsivel e aberto, automaticamente causaria a engenharia reversa para que a senha seja quebrada se torna rápida, trivial e barata.
Como solução para esse problema, foi utilizado o arquivo urandon /dev/urandm do sistema (Baseado em linux). Esse arquivo contem números pseudoaleatorios criptograficamente seguros derivado de fontes físicas, é uma interface para o gerador de números  criptograficamente seguros do kernel (CSPRNG) que é alimentado por diversas fontes de entropia; Pode ser movimento do mouse, pacotes de rede, operações de disco e etc. Se caso o mesmo método for usado no windows deverá ser feito pelo BCryptGenRandom da biblioteca Bcrypt.h.
Esse método  reduz drasticamente falhas relacionadas a telemetria reduzindo drasticamente a viabilidade de engenharia reversa, basearmos semente do gerador. A derivação criptográfica costuma ser ser feita com protocolo Chaccha20 e funciona como um liquidificador do kernel. 

# Tamanho da senha


Conforme o estudo apresentado pela hive system usando hashcat, o tamanho da senha é a principal diferença entre uma senha fraca e uma senha forte, significa que o esforço bruto aumenta exponencialmente a dificuldade apresentada para quebra da criptografia através da força bruta. Calculo matemático que será exibido mais a frente. 
 
Nos estudos usando hashcat senhas com até 8 caracteres, a depender do arsenal do atacante podem ser quebradas instantaneamente; Combinadas, juntamente com o padrão de criptografia do sistema atacado, sendo o mais antigo e obseleto do estudo,  MD5. 
Atualmente se utiliza para criptografias mais fortes,o bcrypt; Que aumenta significativamente o processo de quebra criptografica pelo esforço computacional.
Desde que os estudos foram iniciados em 2021, o uso do treinamento de inteligencia artificial como o chatgpt 3 e 4, representaram o maior impacto de todos em relação ao processamento; Modelos de IA tem aperfeiçoado o poder de busca computacional significativamente, reduzindo o espaço de busca ao priorizar senhas mais provaveis, asssim como faz o Teoria da bussca Bayseana; 
Se fizermos uma analogia, poderia ajudar a reduzir o tempo de busca de um navio perdido no mar separando-o em pequenas células, e usando análise estatista e probabilistica a cada novo espaço procurado para acertar o local correto. Computação inteligente, usando dados para reduzir o tempo de busca de padrões aplicados a senhas.

Dado a essas circunstâncias o reuso das senhas é fator mais crítico para sistemas de segurança com senhas, pois um único vazamento faz com que seja quebrada instantâneamente. 

Em 2024, uma estruturas de bits dos seguintes tamanhos representavam as seguintes dificuldade para grandes poderes computacionais: 
* 2⁴⁰ como muito fácil de ser quebrada
* 2⁵⁶ fácil
* 2⁶⁴ como possível
* 2⁸⁰ como razoavel
* 2¹²⁸ impossível. 
Nessa mesma época, o processamento de hashs da rede do Bitcoin atingiu 2⁸⁰ hashes **por hora.** 
Essa teoria é baseada na arquitetura de computadores atuais e na fisica termodinamica, levando em conta o calor, a energia necessária para o processamento e o poder computacional exigido. Na data desta publicação em 2026, os números ainda são aceitos. Pois mesmo com a implementação da inteligência artificial e a teoria da busca Bayseana, o desafío do `Bitcoin puzzle  transactions`  só registrou a quebra da chave de 130 bits.
Mas 130 bits não é inquebrável? Sim, essa quebra só ocorreu mas não representa uma quebra do ECDSA ou da curva secp256k1. O criador reduziu o espaço de busca, tornando possível sua recuperação por força bruta. Ainda hoje o bitcoin é a maior referência de poder computacional do mundo. Seja pelos seus hashes por hora, seja pelos desafios de recompensas monetárias pela quebra das chaves públicas. 
Curiosidade: Satoshi nakamoto possui mais de um milhao de bitcoins espalhados em vários endereços com a chave publica exposta em tamanho de 256 bits. A recompensa pela quebra criptográfica é possívelmente a maior da história. 

A função de verificação de tamanho é modular e customizavel, sendo contruida recebendo o valor de tamanho mínimo e máximo como parâmetros de função e validando o tamanho pedido; Para que seja interativo e a mensagem seja exibida na tela o `sprintf` armazena os valores das dos parâmetros da função. Enquanto o tamanho digitado pelo usuário não for válido, a condição irá força-lo a colocar um valor aceito. 
Para a primeira etapa será  entre 16 e 512 caracteres correspondendo ao tamanho da senha, podendo ser reaproveitado para outros valores.  

# Força

C = N⁽x⁾ 

N= O número de caracteres possíveis no conjunto; Se usar apenas letras minúsculas N=26. Maiusculas,números e simbolos  N=95. 
x = Comprimento. 
Portanto, enquanto o tipo de caratere multiplica a força da senha, o tamanho aumenta a força exponencialmente. Isso significa que se um invasor duplica o poder computacional para o hashcat  processar testes, reduz muito mais o tempo em relação a adicionar um tipo de caractere especial, maiuscula ou minuscula, mas um pequeno aumento na quantidade de caracteres, eleva o processamento de alguns dias para milhões ou bilhões de anos.
 Orgãos como o NIST confirma que frases longas e fáceis de lembrar são exponencialmente mais seguras do que senhas curtas, complexas e difíceis de digitar.

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


# O problema resolvido

Este programa visa resolver o problema matematico da geração de senhas fortes e imprevisíveis. Buscando boas práticas no desenvolvimento, limpeza de memória de baixo nível. Foi feita ampla pesquisa para base de calculo de precisão e lógica necessária para atingir o objetivo específico de geração de senhas, seguindo boas práticas de mercado para construção deste MVP, a partir da data da publicação da V-1.0.  

O programa que aqui segue, possui limitações que estão descritas neste arquivo, uma delas é:  

* Armazenamento de senhas
* limitação de entropia final, baseado na entropia inicial


Apesar de funcional como MVP, não está apto para ser usado sem a previa implementação de um gerenciador de senhas. Podendo inicialmente ser implementado uma camada provisória de ofuscação, posteriormente.kbdx.   

Existe um plano de desenvolvimento continuo e os principais problemas a serem resolvidos são: 

* Aumento do volume de entropia. 
    * Atravez do SHA512, as senhas aqui geradas, que serviriam para expanção deterministida de dados criptograficos com uso do `size_t` para até 4gb de, que por sua vez seria um CHECKSUM, gerando mais volume de entropia atravez de uma unica semente e um único processo para os transcritores de arquivo.  
    * O checksum resultante dividido em 11 partes, virando uma master seed e se transformando em minemonicos. 
    * Os minemonicos resultantes garantiriam que houvesse recuperação humana possível atravez de bom gerenciamento com folha de papel
    * A recuperação se tornaria possível transformando a master seed em chave privada e chave públida através de multiplas rodadas de hash.
O método descrito acima é uma simplificação do plano de implementação inspirado no funcionamento do bip 39. 
Estes passos seriam seguidos pelos caminhos deterministicos de derivação do bip 32. 
Este por sua vez daria espaço ao bip 85. 

O problema resolvido pelo programa atualmente é a alta entropia, mas cria o problema classico do gerenciamento de senha e a manutenção de senhas complexas. 
Os proximos passos vizam resolver esse problema, criando padrões deterministicos e matematicamente recuperaveis, através de uma frase minemonica e uma formula matemática em conjunto. Maxima soberania no controle e segurança dos dados para o indivíduo consciente. Pois o problema resolvido será outro, como a manutenção de serviços de gerenciadores de senhas do google e iphone, e futuramente a possibilidade de uma forma aberta de substituição de dispositivos de assinatura como yubikey.  
