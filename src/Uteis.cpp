#include <ctime>
#include "../include/Uteis.h"

using namespace std;

void limparTela() {
    system("cls");
}

// Exibir o menu principal
void Uteis::menuPrincipal(Biblioteca& biblioteca) {
    int opcao;
    do {
        limparTela();
        cout << "=======================================" << endl;
        cout << "       SISTEMA DE GESTÃO DE BIBLIOTECA " << endl;
        cout << "=======================================" << endl;
        cout << "1. Gestão de Livros" << endl;
        cout << "2. Gestão de Leitores" << endl;
        cout << "3. Gestão de Empréstimos" << endl;
        cout << "4. Relatórios" << endl;
        cout << "5. Gravação/Recuperação de dados" << endl;
        cout << "0. Sair" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma Opção: ";
        opcao = obterEscolha(0, 5);

        switch (opcao) {
            case 1:
                menuGestaoLivros(biblioteca);
                system("cls");
                break;
            case 2:
                menuGestaoLeitores(biblioteca);
                system("cls");
                break;
            case 3:
                menuGestaoEmprestimos(biblioteca);
                system("cls");
                break;
            case 4:
                menuRelatorios(biblioteca);
                system("cls");
                break;
            case 5:
                biblioteca.gravarDadosEmFicheiro();
                system("cls");
                break;
            case 0:
                //Se biblioteca fosse um ponteiro (Biblioteca* biblioteca = new Biblioteca();)
                //Teria que fazer delete biblioteca;
                //O biblioteca.~Biblioteca(); também não é necessário aqui porque como foi chamado ãoo main como Biblioteca biblioteca;
                //Destrutor é chamado automaticamente ao sair do main().
                //Se fosse colocado aqui biblioteca.~Biblioteca(); , daria erro de memória pois estaria a eliminar a biblioteca 2 vezes
                //Ou seja Eliminar uma coisa que não existe não é possível.
                cout << "A sair do sistema..." << endl;
                break;
            default:
                cout << "Opção inválida." << endl;
        }
    } while (opcao != 0);
}

// Submenu: Gestão de Livros
void Uteis::menuGestaoLivros(Biblioteca& biblioteca) {
    int opcao;
    do {
        limparTela();
        cout << "=======================================" << endl;
        cout << "          GESTÃO DE LIVROS             " << endl;
        cout << "=======================================" << endl;
        cout << "1. Adicionar Livro" << endl;
        cout << "2. Editar Livro" << endl;
        cout << "3. Listar Livros" << endl;
        cout << "4. Pesquisar Livro" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma Opção: ";
        opcao = obterEscolha(0, 4);

        switch (opcao) {
            case 1:
                menuAdicionarLivro(biblioteca);
                break;
            case 2:
                menuEditarLivro(biblioteca);
                break;
            case 3:
                menuListarLivros(biblioteca);
                break;
            case 4:
                menuProcurarLivro(biblioteca);
                break;
            case 0:
                cout << "A voltar ao Menu Principal..." << endl;
                break;
            default:
                cout << "Opção inválida." << endl;
        }
    } while (opcao != 0);
}

void Uteis::menuListarLivros(Biblioteca& biblioteca) {
    int opcao;
    do {
        limparTela();
        cout << "=======================================" << endl;
        cout << "        LISTAGEM DE LIVROS             " << endl;
        cout << "=======================================" << endl;
        cout << "1. Listar Todos" << endl;
        cout << "2. Apenas Ficção" << endl;
        cout << "3. Apenas Científico" << endl;
        cout << "4. Apenas Educativo" << endl;
        cout << "5. Apenas Revistas" << endl;
        cout << "6. Apenas Jornais" << endl;
        cout << "0. Voltar" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma Opção: ";
        opcao = obterEscolha(0, 6);

        switch (opcao) {
            case 1:
                biblioteca.listarLivrosPorTipo("");
                break;
            case 2:
                biblioteca.listarLivrosPorTipo("FICCAO");
                break;
            case 3:
                biblioteca.listarLivrosPorTipo("CIENTIFICO");
                break;
            case 4:
                biblioteca.listarLivrosPorTipo("EDUCATIVO");
                break;
            case 5:
                biblioteca.listarLivrosPorTipo("REVISTA");
                break;
            case 6:
                biblioteca.listarLivrosPorTipo("JORNAL");
                break;
            case 0:
                cout << "A voltar ao Menu de Gestão de Livros..." << endl;
                break;
        }

        if (opcao != 0) {
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcao != 0);
}

void Uteis::menuAdicionarLivro(Biblioteca& biblioteca) {
    limparTela();

    string tipo, titulo, autor;
    int anoPublicacao;
    bool disponivel;
    Livro* novoLivro = nullptr;

    cout << "=======================================\n";
    cout << "           ADICIONAR LIVRO             \n";
    cout << "=======================================\n";
    cout << "Digite o título: ";
    cin.ignore();
    getline(cin, titulo);

    cout << "Digite o autor: ";
    getline(cin, autor);

    cout << "Digite o ano de publicação: ";
    cin >> anoPublicacao;

    cout << "Disponível? (1 = Sim, 0 = Não): ";
    cin >> disponivel;
    cin.ignore();

    cout << "Escolha o tipo de livro:\n";
    cout << "1. Ficção\n";
    cout << "2. Científico\n";
    cout << "3. Educativo\n";
    cout << "4. Revista\n";
    cout << "5. Jornal\n";
    cout << "Escolha (1-5): ";
    int escolha;
    cin >> escolha;
    cin.ignore();

    switch (escolha) {
        case 1: {
            string genero, isbn;
            cout << "Digite o género: ";
            getline(cin, genero);
            cout << "Digite o ISBN: ";
            getline(cin, isbn);
            novoLivro = new LivroFiccao(titulo, autor, anoPublicacao, disponivel, genero, isbn);
            break;
        }
        case 2: {
            string area, isbn;
            cout << "Digite a área científica: ";
            getline(cin, area);
            cout << "Digite o ISBN: ";
            getline(cin, isbn);
            novoLivro = new LivroCientifico(titulo, autor, anoPublicacao, disponivel, area, isbn);
            break;
        }
        case 3: {
            string nivel, isbn;
            cout << "Digite o nível educacional: ";
            getline(cin, nivel);
            cout << "Digite o ISBN: ";
            getline(cin, isbn);
            novoLivro = new LivroEducativo(titulo, autor, anoPublicacao, disponivel, nivel, isbn);
            break;
        }
        case 4: {
            int numero;
            cout << "Digite o número da edição: ";
            cin >> numero;
            cin.ignore();
            novoLivro = new Revista(titulo, autor, anoPublicacao, disponivel, numero);
            break;
        }
        case 5: {
            string data;
            cout << "Digite a data de publicação (YYYY-MM-DD): ";
            getline(cin, data);
            novoLivro = new Jornal(titulo, autor, anoPublicacao, disponivel, data);
            break;
        }
        default:
            cout << "Opção inválida! Cancelando operação...\n";
            return;
    }

    biblioteca.adicionarLivro(novoLivro);
}

void Uteis::menuEditarLivro(Biblioteca& biblioteca) {
    limparTela();
    string titulo;

    cout << "=======================================\n";
    cout << "           EDITAR LIVRO               \n";
    cout << "=======================================\n";
    cout << "Digite o título do livro a editar: ";
    cin.ignore();
    getline(cin, titulo);

    Livro* livro = biblioteca.procurarLivro(titulo);
    if (livro) {
        biblioteca.editarLivro(livro);
    } else {
        cout << "Erro: Nenhum livro encontrado com o título \"" << titulo << "\".\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Submenu: Gestão de Leitores
void Uteis::menuGestaoLeitores(Biblioteca& biblioteca) {
    int opcao;
    do {
        limparTela();
        cout << "=======================================" << endl;
        cout << "          GESTÃO DE LEITORES           " << endl;
        cout << "=======================================" << endl;
        cout << "1. Adicionar Leitor" << endl;
        cout << "2. Editar Leitor" << endl;
        cout << "3. Listar Leitores" << endl;
        cout << "4. Pesquisar Leitor" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma Opção: ";
        opcao = obterEscolha(0, 4);

        switch (opcao) {
            case 1:
                menuAdicionarLeitor(biblioteca);
                break;
            case 2:
                menuEditarLeitor(biblioteca);
                break;
            case 3:
                menuListarLeitores(biblioteca);
                break;
            case 4:
                menuProcurarLeitor(biblioteca);
                break;
            case 0:
                cout << "A voltar ao Menu Principal..." << endl;
                break;
            default:
                cout << "Opção inválida." << endl;
        }
    } while (opcao != 0);
}

void Uteis::menuAdicionarLeitor(Biblioteca& biblioteca) {
    limparTela();

    Pessoa* novoLeitor = criarLeitor();
    if (novoLeitor) {
        biblioteca.adicionarLeitor(novoLeitor);
    } else {
        cout << "Falha ao adicionar leitor.\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void Uteis::menuEditarLeitor(Biblioteca& biblioteca) {
    limparTela();
    int nif;

    cout << "=======================================\n";
    cout << "           EDITAR LEITOR               \n";
    cout << "=======================================\n";
    cout << "Digite o NIF do leitor a editar: ";
    cin >> nif;

    Pessoa* leitor = biblioteca.procurarLeitor(nif);
    if (leitor) {
        biblioteca.editarLeitor(leitor);
    } else {
        cout << "Erro: Nenhum leitor encontrado com o NIF " << nif << ".\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void Uteis::menuProcurarLeitor(Biblioteca& biblioteca) {
    limparTela();
    int nif;

    cout << "=======================================\n";
    cout << "           PROCURAR LEITOR             \n";
    cout << "=======================================\n";
    cout << "Digite o NIF do leitor a procurar: ";
    cin >> nif;

    Pessoa* leitor = biblioteca.procurarLeitor(nif);
    if (leitor) {
        cout << "Leitor encontrado!\n";
        leitor->mostrarInformacoes(); // Exibe os detalhes do leitor
    } else {
        cout << "Erro: Nenhum leitor encontrado com o NIF " << nif << ".\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void Uteis::menuProcurarLivro(Biblioteca& biblioteca) {
    limparTela();
    string titulo;

    cout << "=======================================\n";
    cout << "           PROCURAR LIVRO             \n";
    cout << "=======================================\n";
    cout << "Digite o nome do livro a procurar: ";
    cin >> titulo;

    Livro* livros = biblioteca.procurarLivro(titulo);
    if (livros) {
        cout << "Livro encontrado!\n";
        livros->mostrarInformacoesLivro(); // Exibe os detalhes do leitor
    } else {
        cout << "Erro: Nenhum livro encontrado com o titulo " << titulo << ".\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void Uteis::menuListarLeitores(Biblioteca& biblioteca) {
    int opcao;
    do {
        limparTela();
        cout << "=======================================" << endl;
        cout << "        LISTAGEM DE LEITORES           " << endl;
        cout << "=======================================" << endl;
        cout << "1. Listar Todos" << endl;
        cout << "2. Apenas Estudantes" << endl;
        cout << "3. Apenas Comum" << endl;
        cout << "4. Apenas Professores" << endl;
        cout << "5. Apenas Seniors" << endl;
        cout << "0. Voltar" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma Opção: ";
        opcao = obterEscolha(0, 5);

        switch (opcao) {
            case 1:
                biblioteca.listarLeitoresPorTipo(""); // Lista todos
                break;
            case 2:
                biblioteca.listarLeitoresPorTipo("Estudante");
                break;
            case 3:
                biblioteca.listarLeitoresPorTipo("Comum");
                break;
            case 4:
                biblioteca.listarLeitoresPorTipo("Professor");
                break;
            case 5:
                biblioteca.listarLeitoresPorTipo("Senior");
                break;
            case 0:
                cout << "A voltar ao Menu de Gestão de Leitores..." << endl;
                break;
        }

        if (opcao != 0) {
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcao != 0);
}

// Submenu: Gestão de Empréstimos
void Uteis::menuGestaoEmprestimos(Biblioteca& biblioteca) {
    int opcao;
    do {
        limparTela();
        cout << "=======================================\n";
        cout << "        GESTÃO DE EMPRÉSTIMOS          \n";
        cout << "=======================================\n";
        cout << "1. Realizar Empréstimo\n";
        cout << "2. Reservar Livro\n";
        cout << "3. Devolver Livro\n";
        cout << "4. Listar Empréstimos\n";
        cout << "5. Prorrogar Empréstimo\n";
        cout << "6. Histórico de Empréstimos\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "=======================================\n";
        cout << "Escolha uma Opção: ";
        opcao = obterEscolha(0, 6);

        switch (opcao) {
            case 1:
                menuRealizarEmprestimo(biblioteca);
                break;
            case 2:
                menuReservarLivro(biblioteca);
                break;
            case 3:
                menuDevolverLivro(biblioteca);
                break;
            case 4:
                menuListarEmprestimos(biblioteca);
                cin.ignore();
                cin.get();
                break;
            case 5:
                menuProrrogarEmprestimo(biblioteca);
                break;
            case 6:
                menuExibirHistoricoEmprestimos(biblioteca);
                break;
            case 0:
                cout << "A voltar ao Menu Principal...\n";
                break;
            default:
                cout << "Opção inválida. Tente novamente!\n";
        }
    } while (opcao != 0);
}

void Uteis::menuRealizarEmprestimo(Biblioteca& biblioteca) {
    limparTela();
    int nif;
    string tituloLivro;
    string dataEmprestimo;

    cout << "=======================================\n";
    cout << "       REALIZAR EMPRÉSTIMO             \n";
    cout << "=======================================\n";
    cout << "Digite o NIF do leitor: ";
    cin >> nif;
    cin.ignore();

    cout << "Digite o título do livro: ";
    getline(cin, tituloLivro);

    cout << "Digite a data do empréstimo (DD-MM-AAAA): ";
    cin >> dataEmprestimo;

    Pessoa* leitor = biblioteca.procurarLeitor(nif);
    Livro* livro = biblioteca.procurarLivro(tituloLivro);

    if (leitor && livro) {
        biblioteca.realizarEmprestimo(leitor, livro, dataEmprestimo);
    } else {
        cout << "Erro: Leitor ou livro não encontrado.\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void Uteis::menuReservarLivro(Biblioteca& biblioteca) {
    int nif;
    string tituloLivro;

    cout << "Digite o NIF do leitor: ";
    cin >> nif;
    cout << "Digite o título do livro a reservar: ";
    cin.ignore();
    getline(cin, tituloLivro);

    Pessoa* leitor = biblioteca.procurarLeitor(nif);
    if (!leitor) {
        cout << "Erro: Leitor não encontrado.\n";
        return;
    }

    biblioteca.reservarLivro(leitor, tituloLivro);
}

void Uteis::menuDevolverLivro(Biblioteca& biblioteca) {
    limparTela();
    cout << "=======================================\n";
    cout << "            DEVOLVER LIVRO             \n";
    cout << "=======================================\n";

    int nifLeitor;
    cout << "Digite o NIF do leitor que deseja devolver o livro: ";
    cin >> nifLeitor;
    cin.ignore();

    string tituloLivro;
    cout << "Digite o título do livro que deseja devolver: ";
    getline(cin, tituloLivro);

    cout << "Digite a data de devolução (DD-MM-AAAA): ";
    string dataDevolucao;
    cin >> dataDevolucao;

    biblioteca.devolverLivro(nifLeitor, tituloLivro, dataDevolucao);
    cin.ignore();

    cout << "Pressione Enter para continuar...";
    cin.get();
}

void Uteis::menuListarEmprestimos(Biblioteca& biblioteca) {
    limparTela();
    biblioteca.listarEmprestimos();
}

void Uteis::menuProrrogarEmprestimo(Biblioteca& biblioteca) {
    limparTela();
    int nif;
    string tituloLivro;
    string novaDataDevolucao;

    cout << "=======================================\n";
    cout << "        PRORROGAR EMPRÉSTIMO           \n";
    cout << "=======================================\n";
    cout << "Digite o NIF do leitor: ";
    cin >> nif;
    cin.ignore();

    cout << "Digite o título do livro: ";
    getline(cin, tituloLivro);

    cout << "Digite a nova data de devolução (DD-MM-AAAA): ";
    cin >> novaDataDevolucao;

    // Chamar a função da Biblioteca para prorrogar o empréstimo
    biblioteca.prorrogarEmprestimo(nif, tituloLivro, novaDataDevolucao);

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void Uteis::menuExibirHistoricoEmprestimos(Biblioteca& biblioteca) {
    limparTela();
    int nif;

    cout << "=======================================\n";
    cout << "  EXIBIR HISTéRICO DE EMPRÉSTIMOS      \n";
    cout << "=======================================\n";
    cout << "Digite o NIF do leitor: ";
    cin >> nif;

    Pessoa* leitor = biblioteca.procurarLeitor(nif);
    if (leitor) {
        cout << "\nTipo de Leitor: " << leitor->getTipo() << endl;
        leitor->mostrarHistoricoEmprestimos();
    } else {
        cout << "Erro: Nenhum leitor encontrado com o NIF " << nif << ".\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Submenu: Relatórios
void Uteis::menuRelatorios(Biblioteca& biblioteca) {
    int opcao;
    do {
        limparTela();
        cout << "=======================================" << endl;
        cout << "          RELATéRIOS                   " << endl;
        cout << "=======================================" << endl;
        cout << "1. Relatério de Empréstimos" << endl;
        cout << "2. Relatério de Multas" << endl;
        cout << "3. Relatério de Livros por Categoria" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma Opção: ";
        opcao = obterEscolha(0, 3);

        switch (opcao) {
            case 1:
                biblioteca.gerarRelatorioEmprestimos();
                break;
            case 2:
                biblioteca.gerarRelatorioMultas();
                break;
            case 3:
                biblioteca.gerarRelatorioLivrosCategoria();
                break;
            case 0:
                cout << "A voltar ao Menu Principal..." << endl;
                break;
            default:
                cout << "Opção inválida." << endl;
        }
    } while (opcao != 0);
}

// Função auxiliar para validar entrada do utilizador
int Uteis::obterEscolha(int min, int max) {
    int escolha;
    while (!(cin >> escolha) || escolha < min || escolha > max) {
        cout << "Entrada inválida! Escolha um número entre " << min << " e " << max << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return escolha;
}




