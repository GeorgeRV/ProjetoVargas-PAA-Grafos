# ProjetoVargas-PAA-Grafos

Este projeto visa modelar a cidade de Vargas, utilizando grafos para planejamento de transporte, como a definição de linhas de metrô e otimização das rotas de transporte público. Ele foi desenvolvido em C++ e utiliza várias bibliotecas para manipulação de grafos, heap e leitura de dados. A seguir, apresento um guia para compilar e executar o projeto.

## Requisitos

- **C++**: O código foi desenvolvido em C++ e requer um compilador compatível com a versão C++11 ou superior.
- **Bibliotecas**: 
  - **"graph.h"**: Define a estrutura e os métodos para manipulação do grafo.
  - **"heap.h"**: Utilizado para a implementação de uma fila de prioridade.
  - **"edge.h"**: Define a estrutura de arestas do grafo.
  - **"data.h"**: Contém métodos auxiliares para leitura de dados.

## Compilando e Executando

### Passo 1: Preparar o Ambiente
Certifique-se de ter o compilador C++ instalado. Se você estiver usando Linux ou macOS, o `g++` geralmente já está disponível. No Windows, você pode usar o **MinGW** ou o **Visual Studio** para compilar o código.

### Passo 2: Arquivos de Código

O código principal está no arquivo `main.cpp`. As bibliotecas utilizadas, como `graph.h`, `heap.h`, `edge.h`, e `data.h`, devem estar no mesmo diretório ou em um diretório de inclusão apropriado.

### Passo 3: Compilar o Código

Execute o seguinte comando no terminal (para sistemas Unix, como Linux ou macOS):

```bash
g++ -o projetoVargas main.cpp -std=c++11
```

No Windows, usando o MinGW, o comando seria:

```bash
g++ -o projetoVargas main.cpp -std=c++11
```

Este comando compila o código e gera um executável chamado `projetoVargas`.

### Passo 4: Executar o Código

Após a compilação, execute o programa gerado:

```bash
./projetoVargas
```

No Windows, apenas digite:

```bash
projetoVargas.exe
```

### Passo 5: Saída

O programa irá gerar a linha de metrô com base na conectividade das regiões e imprimirá o tempo de execução da operação, além de exibir as informações da linha de metrô gerada. O tempo será mostrado em segundos.

Exemplo de saída:

```bash
Tempo de execucao: 0.004567 segundos
```

## Estrutura de Arquivos

- **main.cpp**: Contém a função `main` que executa o fluxo principal do programa, incluindo a criação do grafo, a definição da linha de metrô, e a medição do tempo de execução.
- **graph.h**: Definição da classe `GraphCity` e seus métodos para manipulação de grafos e cálculo das rotas.
- **heap.h**: Implementação da estrutura de heap para manipulação eficiente de filas de prioridade.
- **edge.h**: Definição da classe `Edge` para representar as arestas do grafo.
- **data.h**: Funções auxiliares para leitura e manipulação de dados.

## Possíveis Melhorias

- A implementação do grafo pode ser otimizada para suportar grafos maiores.
- Melhorias podem ser feitas na manipulação de memória, especialmente para grandes quantidades de dados.
- A interface gráfica para visualização do grafo poderia ser uma adição interessante para o projeto.

## Conclusão

Este projeto demonstra o uso de grafos e algoritmos clássicos para resolver problemas urbanos, como planejamento de transporte e otimização de rotas. A modelagem e implementação no C++ permite um desempenho eficiente para manipulação de dados grandes e complexos.
