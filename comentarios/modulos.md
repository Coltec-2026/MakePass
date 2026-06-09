# Importações 

O cabeçalho do código possui importações, essas importações são caracteristica da modularidade do código, em sua estrutura final é apresentado uma arquitetura modular, onde funções executam pequenas partes que permitem modificações sem a necessidade de reescrever todo o arquivo da main. 
Essa ideia é a implementação da arquitetura limpa, que permite ao programador incluir funcionalidades e modificar o sistema em mudanças de estrutura. A diferença entre um código que nasce sem vida, e um que permite manutenção e garante um ciclo de desenvolvimento longo.


# Entropia
  Em principio a função srand() foi utilizada para capturar do time() a semente inicial para entropia(aleatoriedade) da senha, porém por se tratar de uma maquina binaria seus números são deterministicos e pseudo aleatórios, não gerando caos suficiente para que provoque imprevisibilidade. Diante desse problema a função urandon() foi adicionada. Capturando do arquivo de /dev/urandm uma única vez antes do loop verificando se o sistema retornou NULL caso não hava descritores de arquivos disponíveis. Se caso o mesmo método for usado no windows deverá ser feito pelo BCryptGenRandom da biblioteca Bcrypt.h. Esse tipo de método captura o ruido de ambiente do sistema ao invez do tempo e previne totalmente que a telemetria do sistema e a investigação do atacante consiga fazer o processo reverso por logs de sistema. A física envolvida inclui variações póssiveis como flutuações de busca em disco, discrepâncias de tempo de interrupção, instabilidade térmida e ruido elétrico. Ao invez do tempo do sistema é capturado uma função de derivação criptográfica podendo ser Chaccha20 e funciona como um liquidificador do kernel. Esse tipo de engenharia, previne ataques de engenharia reversa para descobrimento de senhas.

-[] Adicionar urandom 
# Tamanho da senha


Conforme o estudo apresentado pela hive system usando hashcat, o tamanho da senha é principal diferença entre uma senha fraca e uma senha forte, significa que o esforço bruto aumenta exponencialmente a dificuldade apresentada para quebra da criptografia através da força bruta. Calculo matemático que será exibido mais a frente. 
 
Nos estudos usando hashcat senhas com até 8 caracteres, a depender do arsenal do atacante podem ser quebradas instantaneamente combinadas juntamente com o algorítimo de criptografia utilizado pelo sistema, sendo o mais antigo e obseleto utilizado no estudo algorítimo MD5. Atualmente se utiliza para criptografia mais forte,o bcrypt; Que aumenta significativamente o processo de quebra criptografica pelo esforço computacional. Apesar do atraso no processamento de hashes desde que os estudos foram iniciados em 2021, o uso do treinamento de inteligencia artificial como o chatgpt 3 e 4, foram o que apresentaram o maior impacto de todos em relação ao processamento de hashes, aperfeiçoando o poder computacional do hardware em até 20 vezes, asssim como faz o Teoria da bussca Bayseana; Que em uma analogia, poderia ajudar a reduzir o tempo de busca de um navio perdido no mar o separando pequenas células, e usando análise estatista e probabilistica a cada novo espaço procurado para acertar o local correto. 
Dado a essas circunstâncias o reuso das senhas é fator crítico para sistemas de segurança, pois um único vazamento em mãos erradas faz com que seja quebrada instantâneamente. 

Em 2024 os maiores laboratórios computacionais do mundo, teriam  2⁴⁰ como fácil de ser quebrada, 2⁵⁶  razoavelmente fácil, 2⁶⁴ como possível, 2⁸⁰ como procimamente possível e 2¹²⁸ é impraticável. Essa teoria hoje ainda é aceitavei pois mesmo com a implementação da inteligência artificial e a teoria da busca Bayseana, o desafío do `Bitcoin puzzle transactions`  só registrou a quebra da chave de 130 bits, que só ocorreu por conta de uma vulnerabilidade matemática da chave pública com as curvas elipticas que derrubou o número de tentativas para 2⁶⁴, tornando possível e fácil para grandes poderes computacionais uma quebra criptográfica pelo processamento bruto. 


A função de verificação de tamanho é modular e customizavel, sendo contruida recebendo o valor de tamanho, mínimo e máximo como parâmetros de função e validando o tamanho pedido; Para que seja interativo e a mensagem seja exibida na tela o `sprintf` armazena os valores das dos parâmetros da função. Enquanto o tamanho digitado pelo usuário não for válido a condição irá força-lo a colocar um valor aceito. 
Para a primeira etapa será  entre 16 e 512 caracteres correspondendo ao tamanho da senha, e como reutilização do código só aceitará valores entre 0 e 1.  

# Força

C = N⁽x⁾ 

N= O número de caracteres possíveis no conjunto; Se usar apenas letras minúsculas N=26. Maiusculas,números e simbolos  N=95. 
x = Comprimento. 
Portanto, enquanto o tipo de caratere multiplica a força da senha, o tamanho aumenta a força exponencialmente. Isso significa que se um invasor duplica o poder computacional para o hashcat para processar testes ele anula facilmente um aumento no tipo de caractere; No entanto, quando se adiciona 4 caracteres a mais em uma frase secreta, você joga o tempo de quebra de alguns dias para bilhões  de anos, tornando o ataque de força bruta financeiramente e matematicamente impraticavel.

Orgãos como o NIST confirma que frases longas e fáceis de lembrar são infinitamente mais seguras do que senhas curtas, complexas e difíceis de digitar.

-[] Adicionar opção no código para teste de força de senha
-[] Alguns dos programas poderão ser compilados e usados individualmente, graças a isso podem se comportar com modularidade e serem atribuidos a variáveis de ambiente dentro do shell, sendo invocados como ferramentas de sistema importadas, semelhantes a ferramentas do padrão unix.
-[] Para garantir a execução, talvez seja possível a construção de um docker file, que pode ser distribuido dentro do programa ou acoplado em um html para garantir a execução dentro do github pages.

# Verificar o tipo número  

Função que faz o tratamento de entrada de valores de caracteres digitados pelo usuário. Recebe do sistema mensagem de erro e enunciado a ser exibido na tela interativa e captura do usuário o valor digitado que se verdadeiro para tipo número retorna o valor digitado em uma variável simples, se não entra no laço e faz a limpeza do buffer repetindo até o valor ser válido imprimindo a mensagem de erro. 
