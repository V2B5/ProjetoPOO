# Sistema de Gestão de Biblioteca

Sistema de gestão de biblioteca desenvolvido em C++ com programação orientada a objectos (POO). Permite gerir livros, leitores, empréstimos e reservas de forma eficiente.

## Descrição

Sistema completo de gestão bibliotecária que implementa:
- Gestão de diferentes tipos de livros (Ficção, Científico, Educativo, Revistas, Jornais)
- Gestão de diferentes tipos de leitores (Comum, Estudante, Professor, Sénior)
- Controlo de empréstimos e devoluções
- Sistema de reservas com prioridades
- Cálculo automático de multas por atraso
- Geração de relatórios detalhados
- Persistência de dados em ficheiros

## Características Principais

### Hierarquia de Classes

#### Classes de Livros
- **Livro** (classe base)
  - **LivroFiccao**: Género e ISBN
  - **LivroCientifico**: Área científica e ISBN
  - **LivroEducativo**: Nível educacional e ISBN
  - **Revista**: Número de edição
  - **Jornal**: Data de publicação

#### Classes de Pessoas
- **Pessoa** (classe base abstracta)
  - **Comum**: Leitor padrão (máx. 2 reservas)
  - **Estudante**: Com curso associado (máx. 5 reservas, desconto em multas)
  - **Professor**: Com departamento (máx. 4 reservas, desconto em multas)
  - **Senior**: Para idosos (máx. 3 reservas, isenção de multas)

### Funcionalidades do Sistema

#### Gestão de Livros
- Adicionar novos livros
- Editar informações de livros existentes
- Listar livros por tipo/categoria
- Procurar livros por título
- Controlo de disponibilidade

#### Gestão de Leitores
- Registar novos leitores
- Editar informações de leitores
- Listar leitores por tipo
- Procurar leitores por NIF
- Histórico de empréstimos por leitor

#### Gestão de Empréstimos
- Realizar empréstimos com data automática de devolução (14 dias)
- Devolver livros com cálculo automático de multas
- Prorrogar empréstimos
- Sistema de reservas (normal e prioritária)
- Fila de espera automática para livros indisponíveis

#### Sistema de Multas
- Cálculo automático baseado em dias de atraso
- Diferentes taxas por tipo de leitor:
  - Comum: 0,50€ por dia
  - Estudante: 0,30€ por dia (desconto)
  - Professor: 0,40€ por dia (desconto)
  - Sénior: Isento de multas
- Registo de multas pagas e por pagar

#### Relatórios
- **Relatório de Empréstimos**: Lista todos os empréstimos activos
- **Relatório de Multas**: Detalhes de multas por leitor
- **Relatório de Livros por Categoria**: Organização por tipo de livro

## Estrutura do Projecto

```
ProjetoPOO/
├── include/                    # Ficheiros de cabeçalho (.h)
│   ├── Biblioteca.h           # Classe principal do sistema
│   ├── Livro.h                # Hierarquia de livros
│   ├── Pessoa.h               # Hierarquia de leitores
│   ├── Emprestimo.h           # Gestão de empréstimos
│   ├── Leitor.h               # Interface de leitura
│   ├── Geral.h                # Funções gerais
│   └── Uteis.h                # Utilitários e menus
├── src/                       # Implementação (.cpp)
│   ├── Biblioteca.cpp         # Lógica da biblioteca
│   ├── Livro.cpp              # Implementação de livros
│   ├── Pessoa.cpp             # Implementação de leitores
│   ├── Emprestimo.cpp         # Lógica de empréstimos
│   ├── Leitor.cpp             # Operações de leitura
│   ├── Geral.cpp              # Funções auxiliares
│   └── Uteis.cpp              # Interface de utilizador
├── bin/Debug/                 # Executáveis compilados
├── obj/Debug/                 # Ficheiros objecto
├── .vscode/                   # Configuração VS Code
├── main.cpp                   # Ponto de entrada do programa
├── Pessoas.txt                # Base de dados de leitores
├── Livros.txt                 # Base de dados de livros
├── Biblioteca.txt             # Estado da biblioteca
├── COMPILAR_FINAL.bat         # Script de compilação
├── COMO_USAR_VSCODE.md        # Guia de uso do VS Code
├── .gitignore                 # Ficheiros ignorados pelo Git
└── README.md                  # Este ficheiro
```

## Requisitos

- **Compilador C++**: g++ (GCC) com suporte para C++17 ou superior
- **IDE**: Code::Blocks (recomendado) ou VS Code
- **Sistema Operativo**: Windows, Linux ou macOS

## Compilação e Execução

### Método Mais Simples (Windows)

**Fazer duplo-clique em `COMPILAR_FINAL.bat`**

Este script:
1. Configura o ambiente automaticamente
2. Compila o projecto
3. Executa o programa

### Usando Code::Blocks

1. Abrir o ficheiro `Projecto_POO.cbp` no Code::Blocks
2. Pressionar F9 (Build and Run)
3. O programa será compilado e executado automaticamente

### Usando VS Code

1. Abrir a pasta do projecto no VS Code
2. Pressionar `Ctrl+Shift+B` para compilar
3. Ou usar o menu `Terminal` → `Run Task...` → "Compilar e Executar"

Consultar `COMO_USAR_VSCODE.md` para instruções detalhadas.

### Usando g++ (linha de comandos)

```bash
# Windows (PowerShell)
cd ProjetoPOO
set PATH=C:\Program Files\CodeBlocks\MinGW\bin;%PATH%
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o bin/Debug/ProjetoPOO.exe

# Linux/macOS
cd ProjetoPOO
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o bin/Debug/ProjetoPOO
```

## Utilização

### Menu Principal

Ao iniciar o programa, apresenta um menu com as seguintes opções:

1. **Gestão de Livros**
   - Adicionar livro
   - Editar livro
   - Listar livros
   - Procurar livro

2. **Gestão de Leitores**
   - Adicionar leitor
   - Editar leitor
   - Listar leitores
   - Procurar leitor

3. **Gestão de Empréstimos**
   - Realizar empréstimo
   - Devolver livro
   - Prorrogar empréstimo
   - Reservar livro
   - Listar empréstimos activos

4. **Relatórios**
   - Relatório de empréstimos
   - Relatório de multas
   - Relatório de livros por categoria

5. **Gravar e Sair**

### Formato dos Ficheiros de Dados

#### Pessoas.txt
```
NIF    Nome    Tipo    NEmprestimosTotal    NEmprestimosAtivos    NReservas    MultaPorPagar    MultaPaga    [Informação Adicional]
```

#### Livros.txt
```
TIPO    Título    Autor    AnoPublicação    Disponível    [Campos Específicos]
```

## Conceitos de POO Implementados

### Encapsulamento
- Atributos privados/protegidos
- Getters e setters para acesso controlado
- Validação de dados

### Herança
- Classe base `Livro` com 5 subclasses especializadas
- Classe base abstracta `Pessoa` com 4 subclasses
- Reutilização de código e especialização

### Polimorfismo
- Métodos virtuais (`virtual`)
- Métodos virtuais puros (`= 0`)
- Sobrecarga de métodos (`override`)
- Comportamento específico por tipo

### Abstracção
- Classes abstractas (`Pessoa`)
- Interfaces através de métodos puros
- Separação entre interface e implementação

### Gestão de Memória
- Alocação dinâmica com `new`
- Libertação correcta com `delete`
- Destrutores virtuais
- Prevenção de memory leaks

## Algoritmos e Estruturas de Dados

- **Vector**: Armazenamento dinâmico de livros e empréstimos
- **Map**: Pesquisa eficiente de leitores por NIF (O(log n))
- **Queue**: Fila de reservas (FIFO - First In, First Out)
- **Prioridades**: Sistema de reservas prioritárias vs normais
- **Algoritmos de pesquisa**: Linear e binária
- **Ordenação**: Por tipo, nome, disponibilidade

## Funcionalidades Avançadas

### Sistema de Reservas
- Fila prioritária para Professores e Seniores
- Fila normal para Estudantes e Comuns
- Notificação automática quando livro fica disponível
- Gestão automática de transferência de reservas

### Cálculo de Multas
- Algoritmo de cálculo de dias de atraso
- Aplicação automática de taxas por tipo de leitor
- Registo histórico de multas pagas
- Desconto para estudantes e professores

### Persistência de Dados
- Leitura de ficheiros na inicialização
- Gravação automática de alterações
- Formato de texto estruturado
- Recuperação de estado completo

## Exemplos de Uso

### Realizar um Empréstimo
```
1. Seleccionar "Gestão de Empréstimos"
2. Escolher "Realizar empréstimo"
3. Inserir NIF do leitor
4. Inserir título do livro
5. Sistema verifica disponibilidade
6. Data de devolução calculada automaticamente (+14 dias)
```

### Devolver com Multa
```
1. Seleccionar "Gestão de Empréstimos"
2. Escolher "Devolver livro"
3. Inserir NIF e título
4. Inserir data de devolução
5. Sistema calcula dias de atraso
6. Multa calculada e registada automaticamente
```

## Tratamento de Erros

- Validação de NIF (deve existir)
- Verificação de disponibilidade de livros
- Controlo de limites de reservas por tipo
- Tratamento de ficheiros inexistentes
- Protecção contra divisão por zero
- Validação de datas

## Resolução de Problemas

### Windows: Erro ao compilar
- Verificar se o Code::Blocks está instalado em `C:\Program Files\CodeBlocks\`
- Usar o script `COMPILAR_FINAL.bat` que configura o PATH automaticamente

### Linux/macOS: Comando g++ não encontrado
```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS
xcode-select --install
```

### Erro: Não encontra ficheiros .txt
- Executar o programa na pasta raiz do projecto
- Os ficheiros `Pessoas.txt`, `Livros.txt` e `Biblioteca.txt` devem estar na mesma pasta que `main.cpp`

## Melhorias Futuras

- Interface gráfica (GUI) com Qt ou wxWidgets
- Base de dados SQL para melhor desempenho
- Sistema de autenticação de utilizadores
- Notificações por email
- Códigos de barras/QR codes
- Estatísticas e gráficos
- API REST para integração
- Aplicação móvel

## Contribuir

Contribuições são bem-vindas! Para contribuir:

1. Fazer fork do projecto
2. Criar branch para funcionalidade (`git checkout -b feature/MinhaFuncionalidade`)
3. Fazer commit das alterações (`git commit -m 'Adiciona MinhaFuncionalidade'`)
4. Fazer push para a branch (`git push origin feature/MinhaFuncionalidade`)
5. Abrir Pull Request

## Licença

Este projecto é desenvolvido para fins educacionais no âmbito da disciplina de Programação Orientada a Objectos.

## Autores

- Projecto académico de POO

## Contacto

Para questões ou sugestões sobre o projecto, abrir uma issue no repositório.

---

**Nota**: Este é um projecto académico desenvolvido para demonstração de conceitos de Programação Orientada a Objectos em C++.
- Gestão de diferentes tipos de livros (Ficção, Científico, Educativo, Revistas, Jornais)
- Gestão de diferentes tipos de leitores (Comum, Estudante, Professor, Sénior)
- Controlo de empréstimos e devoluções
- Sistema de reservas com prioridades
- Cálculo automático de multas por atraso
- Geração de relatórios detalhados
- Persistência de dados em ficheiros

## Características Principais

### Hierarquia de Classes

#### Classes de Livros
- **Livro** (classe base)
  - **LivroFiccao**: Género e ISBN
  - **LivroCientifico**: Área científica e ISBN
  - **LivroEducativo**: Nível educacional e ISBN
  - **Revista**: Número de edição
  - **Jornal**: Data de publicação

#### Classes de Pessoas
- **Pessoa** (classe base abstracta)
  - **Comum**: Leitor padrão (máx. 2 reservas)
  - **Estudante**: Com curso associado (máx. 5 reservas, desconto em multas)
  - **Professor**: Com departamento (máx. 4 reservas, desconto em multas)
  - **Senior**: Para idosos (máx. 3 reservas, isenção de multas)

### Funcionalidades do Sistema

#### Gestão de Livros
- Adicionar novos livros
- Editar informações de livros existentes
- Listar livros por tipo/categoria
- Procurar livros por título
- Controlo de disponibilidade

#### Gestão de Leitores
- Registar novos leitores
- Editar informações de leitores
- Listar leitores por tipo
- Procurar leitores por NIF
- Histórico de empréstimos por leitor

#### Gestão de Empréstimos
- Realizar empréstimos com data automática de devolução (14 dias)
- Devolver livros com cálculo automático de multas
- Prorrogar empréstimos
- Sistema de reservas (normal e prioritária)
- Fila de espera automática para livros indisponíveis

#### Sistema de Multas
- Cálculo automático baseado em dias de atraso
- Diferentes taxas por tipo de leitor:
  - Comum: 0,50€ por dia
  - Estudante: 0,30€ por dia (desconto)
  - Professor: 0,40€ por dia (desconto)
  - Sénior: Isento de multas
- Registo de multas pagas e por pagar

#### Relatórios
- **Relatório de Empréstimos**: Lista todos os empréstimos activos
- **Relatório de Multas**: Detalhes de multas por leitor
- **Relatório de Livros por Categoria**: Organização por tipo de livro

## Estrutura do Projecto

```
ProjetoPOO/
├── include/                    # Ficheiros de cabeçalho (.h)
│   ├── Biblioteca.h           # Classe principal do sistema
│   ├── Livro.h                # Hierarquia de livros
│   ├── Pessoa.h               # Hierarquia de leitores
│   ├── Emprestimo.h           # Gestão de empréstimos
│   ├── Leitor.h               # Interface de leitura
│   ├── Geral.h                # Funções gerais
│   └── Uteis.h                # Utilitários e menus
├── src/                       # Implementação (.cpp)
│   ├── Biblioteca.cpp         # Lógica da biblioteca
│   ├── Livro.cpp              # Implementação de livros
│   ├── Pessoa.cpp             # Implementação de leitores
│   ├── Emprestimo.cpp         # Lógica de empréstimos
│   ├── Leitor.cpp             # Operações de leitura
│   ├── Geral.cpp              # Funções auxiliares
│   └── Uteis.cpp              # Interface de utilizador
├── bin/Debug/                 # Executáveis compilados
├── obj/Debug/                 # Ficheiros objecto
├── main.cpp                   # Ponto de entrada do programa
├── Pessoas.txt                # Base de dados de leitores
├── Livros.txt                 # Base de dados de livros
├── Biblioteca.txt             # Estado da biblioteca
├── RelatorioEmprestimos.txt   # Relatório gerado
├── RelatorioMultas.txt        # Relatório gerado
├── RelatorioLivrosCategoria.txt # Relatório gerado
├── .gitignore                 # Ficheiros ignorados pelo Git
└── README.md                  # Este ficheiro
```

## Requisitos

- **Compilador C++**: g++ (GCC) ou equivalente com suporte para C++11 ou superior
- **IDE**: Code::Blocks (recomendado) ou qualquer IDE C++
- **Sistema Operativo**: Windows, Linux ou macOS

## Compilação e Execução

### Usando Code::Blocks

1. Abrir o ficheiro `Projecto_POO.cbp` no Code::Blocks
2. Pressionar F9 (Build and Run) ou clicar em Build > Build and Run
3. O programa será compilado e executado automaticamente

### Usando g++ (linha de comandos)

```bash
# Compilar todos os ficheiros
g++ -std=c++11 -Iinclude main.cpp src/*.cpp -o biblioteca

# Executar
./biblioteca
```

### Usando CMake (opcional)

```bash
mkdir build
cd build
cmake ..
make
./biblioteca
```

## Utilização

### Menu Principal

Ao iniciar o programa, é apresentado um menu com as seguintes opções:

1. **Gestão de Livros**
   - Adicionar livro
   - Editar livro
   - Listar livros
   - Procurar livro

2. **Gestão de Leitores**
   - Adicionar leitor
   - Editar leitor
   - Listar leitores
   - Procurar leitor

3. **Gestão de Empréstimos**
   - Realizar empréstimo
   - Devolver livro
   - Prorrogar empréstimo
   - Reservar livro
   - Listar empréstimos activos

4. **Relatórios**
   - Relatório de empréstimos
   - Relatório de multas
   - Relatório de livros por categoria

5. **Gravar e Sair**

### Formato dos Ficheiros de Dados

#### Pessoas.txt
```
NIF    Nome    Tipo    NEmprestimosTotal    NEmprestimosAtivos    NReservas    MultaPorPagar    MultaPaga    [Informação Adicional]
```

#### Livros.txt
```
TIPO    Título    Autor    AnoPublicação    Disponível    [Campos Específicos]
```

## Conceitos de POO Implementados

### Encapsulamento
- Atributos privados/protegidos
- Getters e setters para acesso controlado
- Validação de dados

### Herança
- Classe base `Livro` com 5 subclasses especializadas
- Classe base abstracta `Pessoa` com 4 subclasses
- Reutilização de código e especialização

### Polimorfismo
- Métodos virtuais (`virtual`)
- Métodos virtuais puros (`= 0`)
- Sobrecarga de métodos (`override`)
- Comportamento específico por tipo

### Abstracção
- Classes abstractas (`Pessoa`)
- Interfaces através de métodos puros
- Separação entre interface e implementação

### Gestão de Memória
- Alocação dinâmica com `new`
- Libertação correcta com `delete`
- Destrutores virtuais
- Prevenção de memory leaks

## Algoritmos e Estruturas de Dados

- **Vector**: Armazenamento dinâmico de livros e empréstimos
- **Map**: Pesquisa eficiente de leitores por NIF (O(log n))
- **Queue**: Fila de reservas (FIFO - First In, First Out)
- **Prioridades**: Sistema de reservas prioritárias vs normais
- **Algoritmos de pesquisa**: Linear e binária
- **Ordenação**: Por tipo, nome, disponibilidade

## Funcionalidades Avançadas

### Sistema de Reservas
- Fila prioritária para Professores e Seniores
- Fila normal para Estudantes e Comuns
- Notificação automática quando livro fica disponível
- Gestão automática de transferência de reservas

### Cálculo de Multas
- Algoritmo de cálculo de dias de atraso
- Aplicação automática de taxas por tipo de leitor
- Registo histórico de multas pagas
- Desconto para estudantes e professores

### Persistência de Dados
- Leitura de ficheiros na inicialização
- Gravação automática de alterações
- Formato de texto estruturado
- Recuperação de estado completo

## Exemplos de Uso

### Realizar um Empréstimo
```
1. Seleccionar "Gestão de Empréstimos"
2. Escolher "Realizar empréstimo"
3. Inserir NIF do leitor
4. Inserir título do livro
5. Sistema verifica disponibilidade
6. Data de devolução calculada automaticamente (+14 dias)
```

### Devolver com Multa
```
1. Seleccionar "Gestão de Empréstimos"
2. Escolher "Devolver livro"
3. Inserir NIF e título
4. Inserir data de devolução
5. Sistema calcula dias de atraso
6. Multa calculada e registada automaticamente
```

## Tratamento de Erros

- Validação de NIF (deve existir)
- Verificação de disponibilidade de livros
- Controlo de limites de reservas por tipo
- Tratamento de ficheiros inexistentes
- Protecção contra divisão por zero
- Validação de datas

## Melhorias Futuras

- Interface gráfica (GUI) com Qt ou wxWidgets
- Base de dados SQL para melhor desempenho
- Sistema de autenticação de utilizadores
- Notificações por email
- Códigos de barras/QR codes
- Estatísticas e gráficos
- API REST para integração
- Aplicação móvel

## Contribuir

Contribuições são bem-vindas! Para contribuir:

1. Fazer fork do projecto
2. Criar branch para funcionalidade (`git checkout -b feature/MinhaFuncionalidade`)
3. Fazer commit das alterações (`git commit -m 'Adiciona MinhaFuncionalidade'`)
4. Fazer push para a branch (`git push origin feature/MinhaFuncionalidade`)
5. Abrir Pull Request

## Licença

Este projecto é desenvolvido para fins educacionais no âmbito da disciplina de Programação Orientada a Objectos.

## Autores

- Desenvolvido como projecto académico de POO

## Contacto

Para questões ou sugestões sobre o projecto, por favor abrir uma issue no repositório.

---

**Nota**: Este é um projecto académico desenvolvido para demonstração de conceitos de Programação Orientada a Objectos em C++.