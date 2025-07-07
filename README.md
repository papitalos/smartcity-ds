# Smart City DS - Sistema de Gestão de Transportes Urbanos

Projeto de estruturas de dados em C para gestão de smart cities, implementando grafos, listas ligadas e algoritmos de busca. Originalmente desenvolvido em Visual Studio (Windows) e agora **totalmente compatível** com macOS e Linux.

## 🚀 Como Inicializar o Projeto

### Pré-requisitos
- **Windows**: Visual Studio 2019+ ou GCC
- **macOS/Linux**: GCC instalado (`gcc --version`)

### Compilação e Execução

#### Método Automático (Recomendado)
```bash
chmod +x build.sh  # Apenas na primeira vez
./build.sh
```

#### Windows
```cmd
# Visual Studio
# Abra o arquivo Projeto_EDA.sln e compile (Ctrl+Shift+B)

# Ou via linha de comando
cl *.c /Fe:smartcity.exe
```

#### macOS/Linux
```bash
make clean
make
./smartcity
```

#### Compilação Manual
```bash
gcc -Wall -Wextra -std=c99 -o smartcity Main.c Cliente.c Gestor.c Transporte.c Localizacao.c Grafo.c
```

### ⚠️ Warnings Esperados
Durante a compilação, você pode ver warnings como:
```
warning: unknown pragma ignored [-Wunknown-pragmas]
#pragma warning(disable : 4996)
```
**Isso é normal!** São pragmas específicos do Windows que são ignorados em outros sistemas.

## 📊 Executando o Sistema

Execute o programa com:
```bash
./smartcity
```

### 🔍 Interpretando a Saída

O programa exibirá uma saída similar a esta:

```
 1
 1  
 1
 1
 1
---------------- Grafo ----------------
Numero de vertices: 10
Numero de arestas: 30
Matriz de Adjacencia:
 0 170 0  0  0  0  0  0  0  0 
170 0 350 0  0  0  0  0  0  0 
...
Lista de Adjacencias:
Vertice 0 -> (1, peso: 170.0) -> NULL
Vertice 1 -> (2, peso: 350.0) -> (0, peso: 170.0) -> NULL
...
 1
 1
```

### 📋 Significado de Cada Seção

#### Códigos de Status Iniciais
```
 1  ← Leitura de clientes (cliente.txt) - SUCESSO
 1  ← Leitura de gestores (gestor.txt) - SUCESSO  
 1  ← Leitura de transportes (transporte.txt) - SUCESSO
 1  ← Leitura de localizações (local.txt) - SUCESSO
 1  ← Criação da matriz do grafo - SUCESSO
```

**Códigos de Retorno:**
- `1` = Operação bem-sucedida
- `2` = Erro no arquivo (não encontrado)
- `3` = Erro de formato (sscanf/sprintf)
- `4` = Lista vazia
- `-1` = Erro geral

#### Estrutura do Grafo
```
Numero de vertices: 10    ← 10 localizações na cidade
Numero de arestas: 30     ← 30 conexões entre localizações
```

#### Matriz de Adjacência
```
 0 170 0  0  0  0  0  0  0  0 
170 0 350 0  0  0  0  0  0  0 
```
- Cada linha/coluna representa uma localização (0-9)
- Valores > 0 = distância entre localizações  
- `0` = sem conexão direta
- Exemplo: distância do vértice 0 para vértice 1 = 170 unidades

#### Lista de Adjacências
```
Vertice 0 -> (1, peso: 170.0) -> NULL
```
- **Vértice 0**: localização de origem
- **(1, peso: 170.0)**: conectado ao vértice 1 com distância 170
- **NULL**: fim da lista de conexões

#### Códigos Finais
```
 1  ← Endereçamento de locais - SUCESSO
 1  ← Mapeamento de transportes - SUCESSO  
 1  ← Salvamento do grafo - SUCESSO
```

## 📁 Estrutura de Dados

### Arquivos de Entrada (pasta `Data/`)
- `cliente.txt` - Dados dos clientes do sistema
- `gestor.txt` - Dados dos gestores/administradores
- `transporte.txt` - Frota de veículos (bicicletas, scooters, etc.)
- `local.txt` - Pontos de interesse da cidade
- `grafo.bin` - Grafo salvo em formato binário

### Estruturas Implementadas
- **Listas Ligadas**: Clientes, Gestores, Transportes, Localizações
- **Grafos**: Representação da rede urbana
- **Matriz de Adjacência**: Distâncias entre pontos
- **Algoritmos**: DFS para busca de caminhos (comentado por questões de compatibilidade)

## 🔧 Arquivos de Compatibilidade

- `platform.h` - Macros para diferenças entre sistemas operacionais
- `Makefile` - Sistema de build para Unix-like systems  
- `build.sh` - Script automático multiplataforma

## ✅ Status de Compatibilidade

- ✅ **Windows** (Visual Studio 2019+)
- ✅ **macOS** (GCC/Clang)
- ✅ **Linux** (GCC)
- ✅ **Arquiteturas ARM64** (Apple Silicon)

## 🐛 Solução de Problemas

### Erro de Compilação
```bash
# Limpe e recompile
make clean
make
```

### Arquivos de Dados Não Encontrados
Certifique-se de que a pasta `Data/` existe com todos os arquivos `.txt`.

### Segmentation Fault
O projeto foi corrigido para evitar crashes. Se ocorrer, verifique se os arquivos de dados estão no formato correto.

## 📝 Notas Técnicas

- **Linguagem**: C (padrão C99)
- **Memória**: Alocação dinâmica com verificações de segurança
- **Algoritmos**: Busca em grafos, ordenação, manipulação de listas
- **Compatibilidade**: Preserva o código original do Windows

## 👨‍💻 Desenvolvimento

O código original foi mantido intacto. As únicas adições foram:
- Arquivos de compatibilidade multiplataforma
- Correções de memory leaks e buffer overflows
- Verificações de ponteiros NULL para maior robustez 