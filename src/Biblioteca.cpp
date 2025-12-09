#include "../include/Biblioteca.h"
#include <algorithm>

using namespace std;

// Construtor
Biblioteca::Biblioteca() {}

// Destrutor
Biblioteca::~Biblioteca() {
    // Limpa a memória de todos os livros
    for (auto livro : livros) {
        delete livro;
    }
    livros.clear(); // Limpa a lista de livros

    // Limpa a memória que foi alocada a todos os leitores
    for (auto& par : leitores) {
        delete par.second;
    }
    leitores.clear(); // Esvazia o mapa de leitores

    // Limpar a fila de reservas priorit?rias
    for (auto& par : reservasPrioritarias) {
        while (!par.second.empty()) {
            par.second.pop();
        }
    }

    reservasPrioritarias.clear(); // Limpa o mapa de reservas priorit?rias

    // Limpar a fila de reservas normais
    for (auto& par : reservasNormais) {
        while (!par.second.empty()) {
            par.second.pop();
        }
    }
    reservasNormais.clear(); // Limpa o mapa de reservas normais
}


void limparTela();

int Biblioteca::calcularDiasAtraso(const string& dataEmprestimo, const string& dataDevolucao) const {
    // Conversão da data de empréstimo
    int diaEmp = stoi(dataEmprestimo.substr(0, 2));
    int mesEmp = stoi(dataEmprestimo.substr(3, 2));
    int anoEmp = stoi(dataEmprestimo.substr(6, 4));

    // Conversão da data de devolução
    int diaDev = stoi(dataDevolucao.substr(0, 2));
    int mesDev = stoi(dataDevolucao.substr(3, 2));
    int anoDev = stoi(dataDevolucao.substr(6, 4));

    // Cálculo do atraso
    return (anoDev - anoEmp) * 365 + (mesDev - mesEmp) * 30 + (diaDev - diaEmp) - 14;
}


// Função para carregar as pessoas do ficheiro Pessoas.txt
void Biblioteca::carregarPessoas(const string& ficheiro) {
    ifstream inFile(ficheiro);
    if (!inFile) {
        cerr << "Erro ao abrir o ficheiro: " << ficheiro << endl;
        return;
    }

        string linha;

        while (getline(inFile, linha)) {
            istringstream ss(linha);
            int nif, NEmprestimosTotal, NEmprestimosAtivos, NReservas;
            string nome, tipo;
            double MultaPorPagar, MultaPaga;

            // Ler os dados do ficheiro
            ss >> nif;
            ss.ignore(); // Ignora a tabulação
            getline(ss, nome, '\t'); // Lê o nome atá à próxima tabulação
            ss >> tipo >> NEmprestimosTotal >> NEmprestimosAtivos >> NReservas >> MultaPorPagar >> MultaPaga;

            // Criar o objeto correspondente ao tipo de leitor
            Pessoa* novaPessoa = nullptr;
            if (tipo == "Estudante") {
                string curso;
                ss.ignore();
                getline(ss, curso);
                novaPessoa = new Estudante(nif, nome, NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga, curso);
            } else if (tipo == "Comum") {
                novaPessoa = new Comum(nif, nome, NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga);
            } else if (tipo == "Professor") {
                string departamento;
                ss.ignore();
                getline(ss, departamento);
                novaPessoa = new Professor(nif, nome, NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga, departamento);
            } else if (tipo == "Senior") {
                int idade;
                ss >> idade;
                novaPessoa = new Senior(nif, nome, NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga, idade);
            }

            // Adicionar ao mapa se a pessoa foi criada com sucesso
            if (novaPessoa) {
                leitores[nif] = novaPessoa;
            }
    }

    inFile.close();
    cout << "Pessoas carregadas com sucesso!" << endl;
}

void Biblioteca::carregarLivros(const string& ficheiro) {
    ifstream inFile(ficheiro);
    if (!inFile) {
        cerr << "Erro ao abrir o ficheiro: " << ficheiro << endl;
        return;
    }

    string linha;
    int livrosCarregados = 0; // Contador para depuração

        while (getline(inFile, linha)) {
        istringstream ss(linha);
        string tipo, titulo, autor, genero, isbn, areaCientifica, nivelEducacional, dataPublicacao;
        int anoPublicacao, numeroEdicao;
        bool disponivel;

        getline(ss, tipo, '\t');
        getline(ss, titulo, '\t');
        getline(ss, autor, '\t');
        ss >> anoPublicacao >> disponivel;

        Livro* novoLivro = nullptr;

        if (tipo == "FICCAO") {
            ss.ignore();
            getline(ss, genero, '\t');
            getline(ss, isbn);
            novoLivro = new LivroFiccao(titulo, autor, anoPublicacao, disponivel, genero, isbn);
        }
        else if (tipo == "CIENTIFICO") {
            ss.ignore();
            getline(ss, areaCientifica, '\t');
            getline(ss, isbn);
            novoLivro = new LivroCientifico(titulo, autor, anoPublicacao, disponivel, areaCientifica, isbn);
        }
        else if (tipo == "EDUCATIVO") {
            ss.ignore();
            getline(ss, nivelEducacional, '\t');
            getline(ss, isbn);
            novoLivro = new LivroEducativo(titulo, autor, anoPublicacao, disponivel, nivelEducacional, isbn);
        }
        else if (tipo == "REVISTA") {
            ss.ignore();
            ss >> numeroEdicao;
            novoLivro = new Revista(titulo, autor, anoPublicacao, disponivel, numeroEdicao);
        }
        else if (tipo == "JORNAL") {
            ss.ignore();
            getline(ss, dataPublicacao);
            novoLivro = new Jornal(titulo, autor, anoPublicacao, disponivel, dataPublicacao);
        }

        if (novoLivro) {
            livros.push_back(novoLivro);
            livrosCarregados++;
            cout << "Livro carregado: " << titulo << " (" << tipo << ")" << endl; // DEBUG
        }
    }

    inFile.close();
    cout << "Total de livros carregados: " << livrosCarregados << endl;
}

void Biblioteca::listarLivrosPorTipo(const string& tipo) const {
    vector<Livro*> listaFiltrada;

    // Filtra os livros por tipo usando if-else direto
    for (const auto& livro : livros) {
        if ((tipo == "FICCAO" && livro->getTipo() == "Ficcao") ||
            (tipo == "CIENTIFICO" && livro->getTipo() == "Cientifico") ||
            (tipo == "EDUCATIVO" && livro->getTipo() == "Educativo") ||
            (tipo == "REVISTA" && livro->getTipo() == "Revista") ||
            (tipo == "JORNAL" && livro->getTipo() == "Jornal") ||
            tipo.empty()) {
            listaFiltrada.push_back(livro);
        }
    }

    if (listaFiltrada.empty()) {
        cout << "N?o h? livros do tipo '" << (tipo.empty() ? "Todos" : tipo) << "' registados.\n";
        return;
    }

    int total = listaFiltrada.size();
    int pagina = 0;
    const int porPagina = 5;
    char opcao;

    do {
        limparTela();
        cout << "=== LISTAGEM DE " << (tipo.empty() ? "TODOS OS LIVROS" : tipo)
             << " === (P?gina " << pagina + 1 << " de " << ((total + porPagina - 1) / porPagina) << ")\n";

        int inicio = pagina * porPagina;
        int fim = min(inicio + porPagina, total);
        for (int i = inicio; i < fim; i++) {
            listaFiltrada[i]->mostrarInformacoesLivro();
            cout << "---------------------------" << endl;
        }

        cout << "[P] Pr?xima p?gina | [A] P?gina anterior | [S] Sair" << endl;
        cout << "Escolha uma op??o: ";
        cin >> opcao;
        opcao = tolower(opcao);

        if (opcao == 'p' && fim < total) pagina++;
        if (opcao == 'a' && pagina > 0) pagina--;

    } while (opcao != 's');
}

void Biblioteca::adicionarLivro(Livro* livro) {
    if (!livro) {
        cout << "Erro: Livro inv?lido.\n";
        return;
    }

    // Verifica se existe algum livro com o mesmo t?tulo
    for (const auto& l : livros) {
        if (l->getTitulo() == livro->getTitulo()) {
            cout << "Erro: Já existe um livro com este título.\n";
            delete livro; // Evita fuga de memória
            return;
        }
    }

    livros.push_back(livro);
    cout << "Livro adicionado com sucesso!\n";
}

void Biblioteca::editarLivro(Livro* livro) {
    if (!livro) {
        cout << "Erro: Livro inválido.\n";
        return;
    }

    limparTela();
    cout << "=======================================\n";
    cout << "           EDITAR LIVRO               \n";
    cout << "=======================================\n";
    cout << "Editando livro: " << livro->getTitulo() << endl;

    string novoTitulo, novoAutor;
    int novoAnoPublicacao;
    bool novaDisponibilidade;

    // Editar o título
    cout << "Novo título (deixe vazio para manter o atual): ";
    cin.ignore();
    getline(cin, novoTitulo);
    if (!novoTitulo.empty()) {
        livro->setTitulo(novoTitulo);
    }

    // Editar o autor
    cout << "Novo autor (deixe vazio para manter o atual): ";
    getline(cin, novoAutor);
    if (!novoAutor.empty()) {
        livro->setAutor(novoAutor);
    }

    // Editar ano de publicação
    cout << "Novo ano de publicação (digite 0 para manter o atual): ";
    cin >> novoAnoPublicacao;
    cin.ignore();
    if (novoAnoPublicacao > 0) {
        livro->setAnoPublicacao(novoAnoPublicacao);
    }

    // Editar disponibilidade
    cout << "Disponibilidade (1 = Sim, 0 = não): ";
    cin >> novaDisponibilidade;
    cin.ignore();
    livro->setDisponibilidade(novaDisponibilidade);

    // Edição dos atributos privados das subclasses
    if (LivroFiccao* ficcao = dynamic_cast<LivroFiccao*>(livro)) {
        cout << "Gênero atual: " << ficcao->genero << endl;  // Acessar diretamente o atributo privado
        cout << "Novo gênero (deixe vazio para manter o atual): ";
        string novoGenero;
        getline(cin, novoGenero);
        if (!novoGenero.empty()) {
            ficcao->genero = novoGenero;  // Modifica diretamente o atributo privado
        }
    }
    else if (LivroCientifico* cientifico = dynamic_cast<LivroCientifico*>(livro)) {
        cout << "Área científica atual: " << cientifico->areaCientifica << endl;  // Acessa diretamente o atributo privado
        cout << "Nova área científica (deixe vazio para manter o atual): ";
        string novaArea;
        getline(cin, novaArea);
        if (!novaArea.empty()) {
            cientifico->areaCientifica = novaArea;  // Modifica diretamente o atributo privado
        }
    }
    else if (LivroEducativo* educativo = dynamic_cast<LivroEducativo*>(livro)) {
        cout << "Nível educacional atual: " << educativo->nivelEducacional << endl;  // Acessa diretamente o atributo privado
        cout << "Novo nível educacional (deixe vazio para manter o atual): ";
        string novoNivel;
        getline(cin, novoNivel);
        if (!novoNivel.empty()) {
            educativo->nivelEducacional = novoNivel;  // Modifica diretamente o atributo privado
        }
    }
    else if (Revista* revista = dynamic_cast<Revista*>(livro)) {
        cout << "Número de edição atual: " << revista->numeroEdicao << endl;  // Acessa diretamente o atributo privado
        cout << "Novo número de edição (digite 0 para manter o atual): ";
        int novoNumero;
        cin >> novoNumero;
        cin.ignore();
        if (novoNumero > 0) {
            revista->numeroEdicao = novoNumero;  // Modifica diretamente o atributo privado
        }
    }
    else if (Jornal* jornal = dynamic_cast<Jornal*>(livro)) {
        cout << "Data de publicação atual: " << jornal->dataPublicacao << endl;  // Acessa diretamente o atributo privado
        cout << "Nova data de publicação (deixe vazio para manter a atual): ";
        string novaData;
        getline(cin, novaData);
        if (!novaData.empty()) {
            jornal->dataPublicacao = novaData;  // Modifica diretamente o atributo privado
        }
    }

    cout << "Livro atualizado com sucesso!\n";
}

void Biblioteca::listarLeitoresPorTipo(const string& tipo) const {
    bool encontrou = false;
    cout << "===============================" << endl;
    cout << "  LISTA DE LEITORES - " << (tipo.empty() ? "TODOS" : tipo) << endl;
    cout << "===============================" << endl;

    for (const auto& par : leitores) {
        if (tipo.empty() || par.second->getTipo() == tipo) {
            par.second->mostrarInformacoes();
            cout << "---------------------------" << endl;
            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "não há leitores do tipo '" << tipo << "' registados.\n";
    }
}

Livro* Biblioteca::procurarLivro(const string& titulo) const {
    for (const auto& livro : livros) {
        if (livro->getTitulo() == titulo) {
            return livro; // Faz retorno do ponteiro para o livro encontrado
        }
    }
    return nullptr; // Faz retorno do nullptr se o livro não for encontrado
}

Pessoa* Biblioteca::procurarLeitor(int nif) const {
    auto it = leitores.find(nif);
    return (it != leitores.end()) ? it->second : nullptr;
}


void Biblioteca::adicionarLeitor(Pessoa* leitor) {
    if (!leitor) {
        cout << "Erro: Leitor inválido.\n";
        return;
    }

    // Verifica se o NIF já existe
    if (leitores.find(leitor->getNIF()) != leitores.end()) {
        cout << "Erro: Já existe um leitor com este NIF.\n";
        delete leitor; // Evita perda de memória
        return;
    }

    leitores[leitor->getNIF()] = leitor;
    cout << "Leitor adicionado com sucesso!\n";
}

void Biblioteca::editarLeitor(Pessoa* leitor) {
    if (!leitor) {
        cout << "Erro: Leitor inválido.\n";
        return;
    }

    limparTela();
    cout << "=======================================\n";
    cout << "           EDITAR LEITOR               \n";
    cout << "=======================================\n";
    cout << "Editando leitor com NIF: " << leitor->getNIF() << endl;
    cout << "Nome atual: " << leitor->getNome() << endl;

    string novoNome;
    cout << "Novo nome (deixe vazio para manter o atual): ";
    cin.ignore();
    getline(cin, novoNome);

    if (!novoNome.empty()) {
        leitor->setNome(novoNome);
    }

    // Verifica o tipo do leitor e edita atributos espec?ficos
    if (Estudante* estudante = dynamic_cast<Estudante*>(leitor)) {
        cout << "Curso atual: " << estudante->curso << endl;  // Acessa o atributo privado
        cout << "Novo curso (deixe vazio para manter o atual): ";
        string novoCurso;
        getline(cin, novoCurso);
        if (!novoCurso.empty()) {
            estudante->curso = novoCurso;  // Modifica diretamente o atributo privado
        }
    }
    else if (Professor* professor = dynamic_cast<Professor*>(leitor)) {
        cout << "Departamento atual: " << professor->departamento << endl;  // Acessa diretamente o atributo privado
        cout << "Novo departamento (deixe vazio para manter o atual): ";
        string novoDepartamento;
        getline(cin, novoDepartamento);
        if (!novoDepartamento.empty()) {
            professor->departamento = novoDepartamento;  // Modifica diretamente o atributo privado
        }
    }
    else if (Senior* senior = dynamic_cast<Senior*>(leitor)) {
        cout << "Idade atual: " << senior->idade << endl;  // Acessa diretamente o atributo privado
        cout << "Nova idade (digite 0 para manter a atual): ";
        int novaIdade;
        cin >> novaIdade;
        cin.ignore();
        if (novaIdade > 0) {
            senior->idade = novaIdade;  // Modifica diretamente o atributo privado
        }
    }

    cout << "Leitor atualizado!\n";
}

void Biblioteca::realizarEmprestimo(Pessoa* leitor, Livro* livro, const string& dataEmprestimo) {
    if (!leitor || !livro) {
        cout << "Erro: Leitor ou livro inválido.\n";
        return;
    }

    if (!livro->estaDisponivel()) {
        cout << "Erro: O livro já está emprestado.\n";
        return;
    }

    Emprestimo novoEmprestimo(leitor, livro, dataEmprestimo);
    emprestimos.push_back(novoEmprestimo);

    // Adicionar o empréstimo ao histórico do leitor
    leitor->adicionarEmprestimoAoHistorico(novoEmprestimo);

    // Atualizar disponibilidade do livro
    livro->setDisponibilidade(false);

    cout << "empréstimo realizado com sucesso!\n";
    cout << "Data de Devolução: " << novoEmprestimo.getDataDevolucao() << "\n";
}

void Biblioteca::reservarLivro(Pessoa* leitor, const string& tituloLivro) {
    Livro* livro = procurarLivro(tituloLivro);
    if (!livro) {
        cout << "Erro: Livro não encontrado.\n";
        return;
    }

    // Se o livro estiver disponível, perguntar se quer requisitar já
    if (livro->estaDisponivel()) {
        string dataReserva;
        cout << "O livro '" << tituloLivro << "' está disponível.\n";
        cout << "Deseja requisitar imediatamente? (S/N): ";
        char escolha;
        cin >> escolha;
        cin.ignore();

        if (tolower(escolha) == 's') {
            cout << "Digite a data do empr?stimo (DD-MM-AAAA): ";
            getline(cin, dataReserva);
            realizarEmprestimo(leitor, livro, dataReserva);
            return;
        } else {
            cout << "Reserva cancelada.\n";
            return;
        }
    }

    // Se o livro não estiver disponível, faz a reserva normalmente
    cout << "O livro '" << tituloLivro << "' já está emprestado, deseja reservar? (S/N): ";
    char opcao;
    cin >> opcao;
    cin.ignore();

    if (tolower(opcao) == 's') {
        if (dynamic_cast<Estudante*>(leitor) && livro->getTipo() == "Educativo") {
            reservasPrioritarias[tituloLivro].push(leitor);
            cout << "O livro '" << tituloLivro << "' foi reservado como prioridade para o estudante " << leitor->getNome() << "!\n";
        } else {
            reservasNormais[tituloLivro].push(leitor);
            cout << "O livro '" << tituloLivro << "' foi reservado para " << leitor->getNome() << "!\n";
        }
    } else {
        cout << "Reserva cancelada.\n";
    }
}


void Biblioteca::devolverLivro(int nifLeitor, const string& tituloLivro, const string& dataDevolucao) {
    auto leitorIt = leitores.find(nifLeitor);
    if (leitorIt == leitores.end()) {
        cout << "Erro: Nenhum leitor encontrado com o NIF " << nifLeitor << ".\n";
        return;
    }

    Pessoa* leitor = leitorIt->second;
    Livro* livro = procurarLivro(tituloLivro);
    if (!livro) {
        cout << "Erro: Livro '" << tituloLivro << "' não encontrado.\n";
        return;
    }

    if (emprestimos.empty()) {
        cout << "não há empréstimos ativos para devolver.\n";
        return;
    }

    auto it = emprestimos.begin();
    while (it != emprestimos.end()) {
        if (it->getLeitor()->getNIF() == nifLeitor && it->getLivro()->getTitulo() == tituloLivro) {
            string dataEmprestimo = it->getDataEmprestimo();
            it->getLivro()->setDisponibilidade(true);

            int atrasoDias = calcularDiasAtraso(dataEmprestimo, dataDevolucao);

            if (atrasoDias > 0) {
                double multa = leitor->calcularMulta(atrasoDias);
                cout << "\nAtenção! O livro '" << tituloLivro << "' foi devolvido com " << atrasoDias << " dias de atraso.\n";
                cout << "Multa aplicada: " << multa << " Euros.\n";

                // Notifica o leitor sobre o atraso
                leitor->notificarAtraso(tituloLivro, atrasoDias);

                // Armazena a multa no mapa `multasRegistradas`
                multasRegistradas[nifLeitor] += multa;
            } else {
                cout << "\nLivro devolvido com sucesso!\n";
            }

            // Remove o empr?stimo
            it = emprestimos.erase(it);

            // Se houver reservas, passa para o pr?ximo leitor da fila
            if (!reservasNormais[tituloLivro].empty()) {
                Pessoa* proximoLeitor = reservasNormais[tituloLivro].front();
                reservasNormais[tituloLivro].pop();
                proximoLeitor->decrementarReservas();

                realizarEmprestimo(proximoLeitor, livro, dataDevolucao);
                cout << "O livro foi automaticamente emprestado para " << proximoLeitor->getNome() << "!\n";
            }

            return;
        } else {
            ++it;
        }
    }

    cout << "Erro: Nenhum empréstimo encontrado para o livro '" << tituloLivro << "' pelo leitor de NIF " << nifLeitor << ".\n";
}

void Biblioteca::listarEmprestimos() const {
    if (emprestimos.empty()) {
        cout << "não há empréstimos ativos no momento.\n";
        return;
    }

    cout << "=======================================\n";
    cout << "         LISTA DE EMPR?STIMOS          \n";
    cout << "=======================================\n";

    for (const auto& emprestimo : emprestimos) {
        cout << "Leitor: " << emprestimo.getLeitor()->getNome()
             << " (NIF: " << emprestimo.getLeitor()->getNIF() << ")\n";
        cout << "Livro: " << emprestimo.getLivro()->getTitulo()
             << " (" << emprestimo.getLivro()->getAutor() << ")\n";
        cout << "Data de empréstimo: " << emprestimo.getDataEmprestimo() << "\n";
        cout << "Data de Devolução: " << emprestimo.getDataDevolucao() << "\n";
        cout << "---------------------------\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void Biblioteca::prorrogarEmprestimo(int nifLeitor, const string& tituloLivro, const string& novaData) {
    // Verifica se o leitor existe
    auto leitorIt = leitores.find(nifLeitor);
    if (leitorIt == leitores.end()) {
        cout << "Erro: Nenhum leitor encontrado com o NIF " << nifLeitor << ".\n";
        return;
    }

    Pessoa* leitor = leitorIt->second;

    if (!(dynamic_cast<Estudante*>(leitor) || dynamic_cast<Professor*>(leitor))) {
        cout << "Erro: Apenas estudantes e professores podem prorrogar empréstimos!\n";
        return;
    }

    for (auto& emprestimo : emprestimos) {
        if (emprestimo.getLeitor()->getNIF() == nifLeitor &&
            emprestimo.getLivro()->getTitulo() == tituloLivro) {

            emprestimo.setDataDevolucao(novaData);
            cout << "empréstimo prorrogado com sucesso para " << novaData << "!\n";
            return;
        }
    }

    cout << "Erro: Nenhum empréstimo encontrado para o leitor e livro informados.\n";
}

void Biblioteca::gerarRelatorioEmprestimos(ofstream* arquivo) const {
    if (emprestimos.empty()) {
        cout << "não há empréstimos ativos para gerar relatório.\n";
        return;
    }

    // Abrir ficheiro se não for passado um stream externo
    ofstream relatorio;
    if (!arquivo) {
        relatorio.open("RelatorioEmprestimos.txt");
        if (!relatorio) {
            cout << "Erro ao criar o ficheiro de relatório.\n";
            return;
        }
    }

    ofstream& saida = arquivo ? *arquivo : relatorio;

    saida << "=======================================\n";
    saida << "    RELATÓRIO DE empréstimos POR TIPO  \n";
    saida << "=======================================\n\n";

    map<string, vector<Emprestimo>> emprestimosPorCategoria;
    map<string, map<string, int>> contagemLeitoresPorCategoria; // string = [categoria]
                                                                // map<string, int> = [tipoLeitor]++

    for (const auto& emprestimo : emprestimos) {
        string categoria = emprestimo.getLivro()->getTipo();
        string tipoLeitor = emprestimo.getLeitor()->getTipo();
        emprestimosPorCategoria[categoria].push_back(emprestimo);
        contagemLeitoresPorCategoria[categoria][tipoLeitor]++;
    }

    for (const auto& categoria : emprestimosPorCategoria) {
        saida << "Categoria: " << categoria.first << "\n";
        saida << "---------------------------------------\n";

        for (const auto& emprestimo : categoria.second) {
            saida << "Leitor: " << emprestimo.getLeitor()->getNome()
                  << " (NIF: " << emprestimo.getLeitor()->getNIF() << ")\n";
            saida << "Tipo de Leitor: " << emprestimo.getLeitor()->getTipo() << "\n";
            saida << "Livro: " << emprestimo.getLivro()->getTitulo()
                  << " (" << emprestimo.getLivro()->getAutor() << ")\n";
            saida << "Data de empréstimo: " << emprestimo.getDataEmprestimo() << "\n";
            saida << "Data de Devolução: " << emprestimo.getDataDevolucao() << "\n";
            saida << "---------------------------------------\n";
        }

        string tipoMaisFrequente;
        int maxRequisicoes = 0;
        for (const auto& [tipoLeitor, quantidade] : contagemLeitoresPorCategoria[categoria.first]) {
            if (quantidade > maxRequisicoes) {
                maxRequisicoes = quantidade;
                tipoMaisFrequente = tipoLeitor;
            }
        }

        saida << "Tipo de leitor que mais requisitou esta categoria: "
              << tipoMaisFrequente << " (" << maxRequisicoes << " empréstimos)\n\n";
    }

    if (!arquivo) {
        relatorio.close();
        cout << "Relatório de empréstimos gerado: RelatorioEmprestimos.txt\n";
    }
}

void Biblioteca::gerarRelatorioLivrosCategoria(ofstream* arquivo) const {
    ofstream relatorio;
    if (!arquivo) {
        relatorio.open("RelatorioLivrosCategoria.txt");
        if (!relatorio) {
            cout << "Erro ao criar o arquivo de relatório de livros.\n";
            return;
        }
    }

    ofstream& saida = arquivo ? *arquivo : relatorio;

    saida << "============================================\n";
    saida << "       RELATÓRIO DE LIVROS POR CATEGORIA   \n";
    saida << "============================================\n\n";

    map<string, vector<Livro*>> livrosPorCategoria;

    for (const auto& livro : livros) {
        livrosPorCategoria[livro->getTipo()].push_back(livro);
    }

    for (const auto& categoria : livrosPorCategoria) {
        saida << "Categoria: " << categoria.first << "\n";
        saida << "--------------------------------------------\n";

        for (const auto& livro : categoria.second) {
            saida << "título: " << livro->getTitulo() << "\n";
            saida << "Autor: " << livro->getAutor() << "\n";
            saida << "Ano de Publicação: " << livro->getAnoPublicacao() << "\n";
            saida << "Disponível: " << (livro->estaDisponivel() ? "Sim" : "não") << "\n";
            saida << "--------------------------------------------\n";
        }

        saida << "\n";
    }

    if (!arquivo) {
        relatorio.close();
        cout << "Relatório de livros por categoria gerado: RelatorioLivrosCategoria.txt\n";
    }
}



void Biblioteca::gerarRelatorioMultas(ofstream* arquivo) const {
    ofstream relatorio;
    if (!arquivo) {
        relatorio.open("RelatorioMultas.txt");
        if (!relatorio) {
            cout << "Erro ao criar o arquivo de relatório de multas.\n";
            return;
        }
    }

    ofstream& saida = arquivo ? *arquivo : relatorio;

    saida << "=======================================\n";
    saida << "       RELATÓRIO DE MULTAS             \n";
    saida << "=======================================\n";

    double totalMultas = 0;

    for (const auto& par : multasRegistradas) {
        int nif = par.first;
        double valorMulta = par.second;

        Pessoa* leitor = procurarLeitor(nif);
        if (leitor) {
            saida << "Nome: " << leitor->getNome() << "\n";
            saida << "NIF: " << leitor->getNIF() << "\n";
            saida << "Tipo: " << leitor->getTipo() << "\n";
            saida << "Multa Total: " << valorMulta << " Euros\n";
            saida << "---------------------------------------\n";

            totalMultas += valorMulta;
        }
    }

    saida << "\n=======================================\n";
    saida << "TOTAL DE MULTAS NO SISTEMA: " << totalMultas << " Euros\n";

    if (!arquivo) {
        relatorio.close();
        cout << "Relatório de multas gerado: RelatorioMultas.txt\n";
    }
}


void Biblioteca::gravarDadosEmFicheiro() {
    string nomeFicheiro;

    cout << "Digite o nome do ficheiro para salvar os dados (ex: BibliotecaBackup.txt): ";
    cin.ignore();
    getline(cin, nomeFicheiro);

    ofstream gravacao(nomeFicheiro);
    if (!gravacao) {
        cout << "Erro ao criar o ficheiro " << nomeFicheiro << ".\n";
        return;
    }

    gravacao << "====================================\n";
    gravacao << "        LISTA DE LEITORES           \n";
    gravacao << "====================================\n";
    for (const auto& par : leitores) {
        Pessoa* leitor = par.second;
        gravacao << leitor->getNIF() << "\t" << leitor->getNome() << "\t"
                 << leitor->getTipo() << "\t" << leitor->getMultaPorPagar() << " Euros\n";
    }

    gravacao << "\n====================================\n";
    gravacao << "        LISTA DE LIVROS             \n";
    gravacao << "====================================\n";
    for (const auto& livro : livros) {
        gravacao << livro->getTipo() << "\t" << livro->getTitulo() << "\t"
                 << livro->getAutor() << "\t" << livro->getAnoPublicacao() << "\t"
                 << (livro->estaDisponivel() ? "Disponível" : "Emprestado") << "\n";
    }

    gerarRelatorioEmprestimos(&gravacao);
    gerarRelatorioMultas(&gravacao);
    gerarRelatorioLivrosCategoria(&gravacao);

    gravacao.close();
    cout << "Dados gravados com sucesso em " << nomeFicheiro << "!\n";
}


