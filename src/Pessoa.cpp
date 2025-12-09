#include "../include/Pessoa.h"
#include <iostream>
#include <map>

using namespace std;

// Construtor da classe base Pessoa
Pessoa::Pessoa(int nif,
               const string& nome,
               const string& tipo,
               int NEmprestimosTotal,
               int NEmprestimosAtivos,
               int NReservas,
               double MultaPorPagar,
               double MultaPaga)
    : nif(nif), nome(nome), tipo(tipo),
    NEmprestimosTotal(NEmprestimosTotal),
    NEmprestimosAtivos(NEmprestimosAtivos),
    NReservas(NReservas), MultaPorPagar(MultaPorPagar),
    MultaPaga(MultaPaga) {}

Pessoa::~Pessoa() {}

int Pessoa::getNIF() const { return nif; }
string Pessoa::getTipo() const {return tipo;}

// Mostra informaéées da Pessoa
void Pessoa::mostrarInformacoes() const {
    cout << "NIF: " << nif << endl;
    cout << "nome: " << nome << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Empréstimos Totais: " << NEmprestimosTotal << endl;
    cout << "Empréstimos Ativos: " << NEmprestimosAtivos << endl;
    cout << "Reservas: " << NReservas << endl;
    cout << "Multa por Pagar: " << MultaPorPagar << endl;
    cout << "Total Multa Paga: " << MultaPaga << endl;
}

void Pessoa::decrementarReservas() {
    if (NReservas > 0) {
        NReservas--;
    }
}

// ---------------------------------------- Leitor Comum ---------------------------------------- //
Comum::Comum(int nif, const string& nome, int NEmprestimosTotal, int NEmprestimosAtivos, int NReservas, double MultaPorPagar, double MultaPaga)
    : Pessoa(nif, nome, "Comum", NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga), maxLivros(3), descontoMulta(0.0) {}

void Comum::mostrarInformacoes() const {
    Pessoa::mostrarInformacoes();
    cout << "Max Livros Leitor Comum: " << maxLivros << endl;
    cout << "Desconto em Multas Leitor Comum: " << descontoMulta * 100 << "%" << endl;
}

// ---------------------------------------------------------------------------------------------- //

// ---------------------------------------- Estudante ---------------------------------------- //
Estudante::Estudante(int nif, const string& nome, int NEmprestimosTotal, int NEmprestimosAtivos, int NReservas, double MultaPorPagar, double MultaPaga, const string& curso)
    : Pessoa(nif, nome, "Estudante", NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga), maxLivros(5), descontoMulta(0.20), curso(curso) {}

void Estudante::mostrarInformacoes() const {
    Pessoa::mostrarInformacoes();
    cout << "Curso: " << curso << endl;
    cout << "Max Livros Estudante: " << maxLivros << endl;
    cout << "Desconto em Multas Estudante: " << descontoMulta * 100 << "%" << endl;
}

// ---------------------------------------------------------------------------------------------- //

// ---------------------------------------- Professor ---------------------------------------- //
Professor::Professor(int nif, const string& nome, int NEmprestimosTotal, int NEmprestimosAtivos, int NReservas, double MultaPorPagar, double MultaPaga, const string& departamento)
    : Pessoa(nif, nome, "Professor", NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga), maxLivros(7), descontoMulta(0.50), departamento(departamento) {}

void Professor::mostrarInformacoes() const {
    Pessoa::mostrarInformacoes();
    cout << "Departamento: " << departamento << endl;
    cout << "Max Livros Professor: " << maxLivros << endl;
    cout << "Desconto em Multas Professor: " << descontoMulta * 100 << "%" << endl;
}

// ---------------------------------------------------------------------------------------------- //

// ---------------------------------------- Senior ---------------------------------------- //
Senior::Senior(int nif, const string& nome, int NEmprestimosTotal, int NEmprestimosAtivos, int NReservas, double MultaPorPagar, double MultaPaga, int idade)
    : Pessoa(nif, nome, "Senior", NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga), maxLivros(4), descontoMulta(0.30), idade(idade) {}

void Senior::mostrarInformacoes() const {
    Pessoa::mostrarInformacoes();
    cout << "Idade: " << idade << endl;
    cout << "Max Livros Senior: " << maxLivros << endl;
    cout << "Desconto em Multas Senior: " << descontoMulta * 100 << "%" << endl;
}

// ---------------------------------------------------------------------------------------------- //

Pessoa* criarLeitor() {
    int nif;
    string nome;
    int tipoLeitor;

    cout << "=======================================\n";
    cout << "           ADICIONAR LEITOR            \n";
    cout << "=======================================\n";
    cout << "Digite o NIF: ";
    cin >> nif;
    cin.ignore();

    cout << "Digite o nome: ";
    getline(cin, nome);

    cout << "Escolha o tipo de leitor:\n";
    cout << "1. Comum\n";
    cout << "2. Estudante\n";
    cout << "3. Professor\n";
    cout << "4. Senior\n";
    cout << "Escolha (1-4): ";
    cin >> tipoLeitor;
    cin.ignore();

    int NEmprestimosTotal = 0, NEmprestimosAtivos = 0, NReservas = 0;
    double MultaPorPagar = 0.0, MultaPaga = 0.0;

    Pessoa* novoLeitor = nullptr;

    switch (tipoLeitor) {
        case 1:
            novoLeitor = new Comum(nif, nome, NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga);
            break;

        case 2: {
            string curso;
            cout << "Digite o curso do estudante: ";
            getline(cin, curso);
            novoLeitor = new Estudante(nif, nome, NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga, curso);
            break;
        }

        case 3: {
            string departamento;
            cout << "Digite o departamento do professor: ";
            getline(cin, departamento);
            novoLeitor = new Professor(nif, nome, NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga, departamento);
            break;
        }

        case 4: {
            int idade;
            cout << "Digite a idade do Senior: ";
            cin >> idade;
            cin.ignore();
            novoLeitor = new Senior(nif, nome, NEmprestimosTotal, NEmprestimosAtivos, NReservas, MultaPorPagar, MultaPaga, idade);
            break;
        }

        default:
            cout << "Opção inválida!\n";
            return nullptr;
    }

    return novoLeitor;
}

void Pessoa::adicionarMulta(double valor) {MultaPorPagar += valor;}

double Comum::calcularMulta(int diasAtraso) const {return diasAtraso * 1.0;} // Sem desconto
double Estudante::calcularMulta(int diasAtraso) const {return diasAtraso * 1.0 * 0.8;} // 20% de desconto
double Professor::calcularMulta(int diasAtraso) const {return diasAtraso * 1.0 * 0.5;} // 50% de desconto
double Senior::calcularMulta(int diasAtraso) const {return diasAtraso * 1.0 * 0.7;} // 30% de desconto

// Adiciona o empréstimo ao histérico
void Pessoa::adicionarEmprestimoAoHistorico(const Emprestimo& emprestimo) {
    historicoEmprestimos.push_back(emprestimo);
}

// Mostra histórico de empréstimo
void Pessoa::mostrarHistoricoEmprestimos() const {
    cout << "=== Histórico de Empréstimos de " << nome << " (" << tipo << ") ===" << endl;

    if (historicoEmprestimos.empty()) {
        cout << "Nenhum empréstimo registrado.\n";
        return;
    }

    // Mapa para categorizar os empréstimos por tipo de livro
    map<string, vector<Emprestimo>> emprestimosPorTipo;

    // Categoriza os empréstimos por tipo de livro
    for (const auto& emprestimo : historicoEmprestimos) {
        string tipoLivro = emprestimo.getLivro()->getTipo();
        emprestimosPorTipo[tipoLivro].push_back(emprestimo);
    }

    // Mostra os empréstimos categorizados
    for (const auto& par : emprestimosPorTipo) {
        string tipoLivro = par.first;
        const vector<Emprestimo>& emprestimos = par.second;

        cout << "\nTipo de Livro: " << tipoLivro << endl;
        cout << "---------------------------" << endl;

        for (const auto& emprestimo : emprestimos) {
            cout << "Livro: " << emprestimo.getLivro()->getTitulo() << endl;
            cout << "Data de Empréstimo: " << emprestimo.getDataEmprestimo() << endl;
            cout << "Data de Devoluééo: " << emprestimo.getDataDevolucao() << endl;
            cout << "---------------------------" << endl;
        }
    }
}

// Notificação para Leitor Comum
void Comum::notificarAtraso(const string& tituloLivro, int diasAtraso) const {
    cout << "Notificação para Leitor Comum:\n";
    cout << "O livro \"" << tituloLivro << "\" está atrasado por " << diasAtraso << " dias.\n";
    cout << "Multa aplicada: " << calcularMulta(diasAtraso) << " Euros.\n";
    cout << "Por favor, devolva o livro o mais rápido possível.\n";
}

// Notificação para Estudante
void Estudante::notificarAtraso(const string& tituloLivro, int diasAtraso) const {
    cout << "Notificação para Estudante:\n";
    cout << "O livro \"" << tituloLivro << "\" está atrasado por " << diasAtraso << " dias.\n";
    cout << "Multa aplicada: " << calcularMulta(diasAtraso) << " Euros.\n";
    cout << "Lembre-se de que você tem um desconto de 20% nas multas.\n";
    cout << "Por favor, devolva o livro o mais rápido possível.\n";
}

// Notificação para Professor
void Professor::notificarAtraso(const string& tituloLivro, int diasAtraso) const {
    cout << "Notificação para Professor:\n";
    cout << "O livro \"" << tituloLivro << "\" esté atrasado por " << diasAtraso << " dias.\n";
    cout << "Multa aplicada: " << calcularMulta(diasAtraso) << " Euros.\n";
    cout << "Vocé pode prorrogar o empréstimo se necessário.\n";
    cout << "Por favor, devolva o livro o mais répido possível.\n";
}

// Notificação para Sénior
void Senior::notificarAtraso(const string& tituloLivro, int diasAtraso) const {
    cout << "Notificação para Sénior:\n";
    cout << "O livro \"" << tituloLivro << "\" está atrasado por " << diasAtraso << " dias.\n";
    cout << "Multa aplicada: " << calcularMulta(diasAtraso) << " Euros.\n";
    cout << "Você tem um desconto de 30% nas multas.\n";
    cout << "Por favor, devolva o livro o mais rápido possível.\n";
}




