#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include "Pessoa.h"
#include "Livro.h"

class Pessoa;

class Emprestimo {
private:
    Pessoa* leitor;
    Livro* livro;
    string dataEmprestimo;
    string dataDevolucao;

public:
    // Construtor da classe Emprestimo
    Emprestimo(Pessoa* leitor, Livro* livro, const string& dataEmprestimo);

    // Método para manipulação de empréstimos
    Pessoa* getLeitor() const;
    Livro* getLivro() const;
    string getDataEmprestimo() const;
    string getDataDevolucao() const;

    void setDataDevolucao(const string& data);
    bool estaAtrasado() const;

    static string calcularDataDevolucao(const string& dataEmprestimo);


    void exibirInfo() const;
};

#endif



