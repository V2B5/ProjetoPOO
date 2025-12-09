#include "../include/Emprestimo.h"
#include <ctime>
#include <sstream>

Emprestimo::Emprestimo(Pessoa* leitor, Livro* livro, const string& dataEmprestimo)
    : leitor(leitor), livro(livro), dataEmprestimo(dataEmprestimo) {
    //+14 dias no dia da data de emprestimo para devolucao
    dataDevolucao = calcularDataDevolucao(dataEmprestimo);
}

Pessoa* Emprestimo::getLeitor() const {return leitor;}
Livro* Emprestimo::getLivro() const {return livro;}
string Emprestimo::getDataEmprestimo() const {return dataEmprestimo;}
string Emprestimo::getDataDevolucao() const {return dataDevolucao.empty() ? "Em andamento" : dataDevolucao;}
void Emprestimo::setDataDevolucao(const string& data) {dataDevolucao = data;}

bool Emprestimo::estaAtrasado() const {
    //Implementação futura - Apenas um placeholder por enquanto
    return false;
}

void Emprestimo::exibirInfo() const {
    cout << "Leitor: " << leitor->getNome() << " (NIF: " << leitor->getNIF() << ")\n";
    cout << "Livro: " << livro->getTitulo() << " (" << livro->getAutor() << ")\n";
    cout << "Data de Empréstimo: " << dataEmprestimo << "\n";
    cout << "Data de Devolução: " << (dataDevolucao.empty() ? "Em andamento" : dataDevolucao) << "\n";
    cout << "---------------------------\n";
}

int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool AnoBissexto(int ano) {
        return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
    }

string Emprestimo::calcularDataDevolucao(const string& dataEmprestimo) {
    int dia, mes, ano;
    char separador;

    istringstream ss(dataEmprestimo);
    ss >> dia >> separador >> mes >> separador >> ano;

    dia += 14;

    if (mes == 2 && AnoBissexto(ano)) {
        diasNoMes[1] = 29;
    } else {
        diasNoMes[1] = 28;
    }

    while (dia > diasNoMes[mes - 1]) {
        dia -= diasNoMes[mes - 1];
        mes++;

        if (mes > 12) {
            mes = 1;
            ano++;
        }
    }

    ostringstream novaData;
    novaData << (dia < 10 ? "0" : "") << dia << "-"
             << (mes < 10 ? "0" : "") << mes << "-"
             << ano;

    return novaData.str();
}



