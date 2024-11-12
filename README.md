# Mergesort

Trabalho prático desenvolvido para a disciplina de Sistemas Operacionais - TT304, da Faculdade de Tecnologia da Unicamp.

Grupo: 2Threads

Discentes: Hitallo Alves Teles Azevedo e João Pedro Calsavara

Docente: André Leon S. Gradvohl

## Descrição do problema
Este programa em C processa múltiplos arquivos de entrada, cada um contendo uma lista de inteiros desordenados (um em cada linha), utilizando threads. Ele realiza a leitura e ordenação simultânea dos arquivos, armazenando o resultado em um arquivo de saída. A implementação visa medir o impacto do aumento de threads no tempo de execução. 

## Instruções para executar o projeto 
O projeto foi desenvolvido utilizando linguagem C pura e a biblioteca POSIX threads para manipulação das threads. Portanto, para a execução do programa, é pré requisito que o sistema operacional seja baseado em Linux.


Com o terminal aberto e o GIT devidamente instalado, execute o comando a seguir para clonar o repositório.
```
  git clone https://github.com/hitalloazevedo/mergesort
```

Abrindo o repositório
```
cd mergesort
```

Compilando o programa
```
make
```

Executando o programa
```
./mergesort <T> <F1> <F2> <F3> -o <OF>
```
##### Argumentos
\<T\>: quantidade de threads que o programa irá utilizar. <br>
\<Fn\>: Nome do arquivo de entrada, deve incluir a extensão do arquivo.<br>
-o: Indica que o próximo argumento será o nome do arquivo de saída.<br>
\<OF\>: Nome do arquivo de saída, deve incluir a extensão do arquivo.

<strong>Após a execução do programa, o programa irá gerar um arquivo de saida que estará localizado em `/mergesort/outputs`.</strong>

#### Configurações essenciais para uma execução correta
Os arquivos de entrada com os valores inteiros devem estar localizados em `/mergesort/inputs`. <br>
É recomendado que as extensões dos arquivos de entrada e saída sejam `.dat` ou `.txt`.
