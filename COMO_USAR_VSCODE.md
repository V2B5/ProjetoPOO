# Como Usar o Projecto no VS Code

## MÉTODO MAIS SIMPLES (Recomendado)

### Fazer double click no `COMPILAR_FINAL.bat` (Com o compiler do g++ do CodeBlocks)

Este script:
1. Configura o ambiente automaticamente
2. Compila o projecto
3. Executa o programa se não houver erros

---

## Passo 1: Abrir o Projecto no VS Code
1. No VS Code: `File` → `Open Folder...`
2. Seleccionar a pasta `d:\Projetos_GitHub\ProjetoPOO`
3. Clicar em "Seleccionar Pasta"

## Passo 2: Compilar

### Opção A - Atalho de Teclado (Recomendado)
- Pressionar **`Ctrl+Shift+B`**
- Seleccionar "Compilar Projecto"

### Opção B - Menu Terminal
1. Menu: `Terminal` → `Run Task...`
2. Seleccionar "Compilar Projecto"

### Opção C - Script Batch (Mais Fiável)
- Fazer double click no `COMPILAR_FINAL.bat`

### Opção D - Terminal Manual (PowerShell) (Isto com o compliador g++ do codeblocks, se não tens o compilador não dá.)
```powershell
& 'C:\Program Files\CodeBlocks\MinGW\bin\g++.exe' -g -std=c++17 -Iinclude main.cpp src\Biblioteca.cpp src\Livro.cpp src\Pessoa.cpp src\Emprestimo.cpp src\Leitor.cpp src\Geral.cpp src\Uteis.cpp -o bin\Debug\ProjetoPOO.exe
```

**IMPORTANTE**: Não usar apenas `g++` porque não está no PATH. Usar o caminho completo com `&` e aspas, ou usar `COMPILAR_FINAL.bat`!

## Passo 3: Executar

### Opção A - Após Compilar
Se usou `COMPILAR_FINAL.bat`, o programa executa automaticamente.

### Opção B - Terminal
```bash
.\bin\Debug\ProjetoPOO.exe
```

### Opção C - Duplo Clique
- Navegar até `bin\Debug\` no explorador
- Fazer duplo clique em `ProjetoPOO.exe`

### Opção D - Task do VS Code
1. Pressionar **`Ctrl+Shift+P`**
2. Escrever "Run Task"
3. Seleccionar "Compilar e Executar"

## Passo 4: Depurar (Opcional)
1. Colocar breakpoints (clicar à esquerda do número da linha)
2. Pressionar **`F5`**
3. O programa será compilado e executado em modo debug

## Atalhos Rápidos

| Atalho | Acção |
|--------|-------|
| **Ctrl+Shift+B** | Compilar |
| **F5** | Depurar |
| **Ctrl+`** | Abrir/Fechar Terminal |
| **Ctrl+Shift+P** | Paleta de Comandos |

## Estrutura do Projecto

```
ProjetoPOO/
├── .vscode/              ← Configuração do VS Code
├── include/              ← Ficheiros .h (cabeçalhos)
├── src/                  ← Ficheiros .cpp (implementação)
├── bin/Debug/            ← Executável final
├── obj/Debug/            ← Ficheiros objecto
├── main.cpp              ← Ponto de entrada
├── Pessoas.txt           ← Base de dados de leitores
├── Livros.txt            ← Base de dados de livros
├── Biblioteca.txt        ← Estado da biblioteca
├── COMPILAR_FINAL.bat    ← Script de compilação
└── Projecto_POO.cbp      ← Projecto Code::Blocks
```

## Diferenças Code::Blocks vs VS Code

| Code::Blocks | VS Code |
|--------------|---------|
| Abrir `.cbp` | Abrir pasta |
| Build → Build | `Ctrl+Shift+B` |
| Build → Run | Task ou Terminal |
| F9 (Build and Run) | F5 (Debug) |
| Configuração automática | Configuração manual (.vscode/) |

## Resolução de Problemas

### Erro: "g++ não reconhecido"

**Causa**: O compilador g++ não está no PATH do sistema.

**Solução**:
- Usar o script `COMPILAR_FINAL.bat` que configura o PATH automaticamente
- Ou adicionar `C:\Program Files\CodeBlocks\MinGW\bin` ao PATH do Windows manualmente

### Erro: Não encontra ficheiros .h

**Causa**: IntelliSense não está configurado correctamente.

**Solução**:
- A pasta `.vscode/` já contém a configuração necessária
- Se persistir, pressionar `Ctrl+Shift+P` → "C/C++: Edit Configurations"
- Verificar que `includePath` contém `${workspaceFolder}/include`

### Erro: Não encontra Pessoas.txt ou Livros.txt

**Causa**: O programa executa numa pasta diferente.

**Solução**:
- Executar sempre a partir da pasta raiz do projecto (`ProjetoPOO/`)
- Os ficheiros `.txt` devem estar na mesma pasta que `main.cpp`
- Não executar directamente de `bin/Debug/`

### Erro: Código compila mas não executa (0xc000007b)

**Causa**: DLLs do MinGW não estão acessíveis.

**Solução**:
- Usar `COMPILAR_FINAL.bat` que adiciona MinGW ao PATH temporariamente
- Ou compilar com flag `-static` para incorporar bibliotecas no executável

### Aviso: "CMake: build" ou "CMake: clean rebuild"

**Este projecto NÃO usa CMake!**

**Solução**:
- Usar apenas as tasks configuradas: "Compilar Projecto", "Executar Programa", "Compilar e Executar"
- Ou usar o ficheiro `COMPILAR_FINAL.bat`
- Ignorar tasks relacionadas com CMake

## Configuração do VS Code

A pasta `.vscode/` contém:

### tasks.json
Define as tarefas de compilação e execução:
- **Compilar Projecto**: Compila todos os ficheiros
- **Executar Programa**: Executa o programa compilado
- **Compilar e Executar**: Compila e executa em sequência

### launch.json
Configuração de depuração (debug):
- Usa gdb (GNU Debugger) do MinGW
- Breakpoints, step-through, watch variables

### c_cpp_properties.json
Configuração do IntelliSense:
- Paths para ficheiros de cabeçalho
- Standard C++17
- Compilador MinGW

### settings.json
Configurações específicas do projecto:
- Codificação UTF-8
- Associações de ficheiros C++

## Fluxo de Trabalho Recomendado

1. **Desenvolvimento**:
   - Editar ficheiros `.cpp` e `.h` no VS Code
   - IntelliSense ajuda com autocompletar e verificação de sintaxe

2. **Compilação**:
   - Pressionar `Ctrl+Shift+B` para compilar
   - Verificar erros no painel "Problems"

3. **Teste**:
   - Executar com `.\bin\Debug\ProjetoPOO.exe`
   - Testar funcionalidades do sistema

4. **Depuração**:
   - Colocar breakpoints nos locais de interesse
   - Pressionar `F5` para iniciar debug
   - Usar `F10` (step over), `F11` (step into), `F5` (continue)

5. **Gravar**:
   - O sistema grava automaticamente em `Biblioteca.txt`
   - Usar opção "Gravar e Sair" no menu principal

## Dicas Úteis

- O VS Code trabalha directamente com ficheiros `.cpp` e `.h`, não precisa do `.cbp`
- Pode abrir múltiplos ficheiros em tabs para edição simultânea
- Use `Ctrl+P` para procurar ficheiros rapidamente
- Use `Ctrl+F` para procurar dentro de um ficheiro
- Use `Ctrl+Shift+F` para procurar em todos os ficheiros do projecto
- O terminal integrado (`Ctrl+``) permite executar comandos sem sair do editor
- IntelliSense mostra documentação ao passar o rato sobre funções e classes

## Comparação com Code::Blocks

### Vantagens do VS Code:
- Editor mais moderno e leve
- Melhor integração com Git
- Extensões poderosas (Copilot, GitLens, etc.)
- Terminal integrado
- Pesquisa avançada em múltiplos ficheiros
- Personalização extensa

### Vantagens do Code::Blocks:
- Configuração automática do compilador
- Interface mais simples para iniciantes
- Gestão de projectos integrada
- Build system nativo

Ambos são válidos para este projecto. Use o que preferir!
