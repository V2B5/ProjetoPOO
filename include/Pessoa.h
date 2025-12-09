#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
#include <vector>
#include <string>
#include "Emprestimo.h"

class Emprestimo; // Declaração
using namespace std;

class Pessoa {
    protected:
        int nif;
        string nome;
        string tipo;
        int NEmprestimosTotal;
        int NEmprestimosAtivos;
        int NReservas;
        double MultaPorPagar;
        double MultaPaga;
        vector<Emprestimo> historicoEmprestimos;

    public:
        Pessoa(int nif, const string& nome, const string& tipo, int NEmprestimosTotal, int NEmprestimosAtivos, int NReservas, double MultaPorPagar, double MultaPaga);
        virtual ~Pessoa();
        virtual void mostrarInformacoes() const = 0;
        virtual double calcularMulta(int diasAtraso) const = 0;
        virtual int getMaxReservas() const = 0;
        virtual void notificarAtraso(const string& tituloLivro, int diasAtraso) const = 0;

        int getNIF() const;
        string getTipo() const;
        string getNome() const { return nome; }
        double getMultaPorPagar() const { return MultaPorPagar; }

        void setNome(const string& novoNome) { nome = novoNome; }

        void adicionarMulta(double valor);
        void decrementarReservas();

        void adicionarEmprestimoAoHistorico(const Emprestimo& emprestimo);
        void mostrarHistoricoEmprestimos() const;

};

//-------------------- Subclasse: Comum --------------------//
class Comum : public Pessoa {
    private:
        int maxLivros;
        double descontoMulta;

    public:
        Comum(int nif, const string& nome, int NEmprestimosTotal, int NEmprestimosAtivos, int NReservas, double MultaPorPagar, double MultaPaga);
        void mostrarInformacoes() const override;
        double calcularMulta(int diasAtraso) const override;
        int getMaxReservas() const override { return 2; }
        void notificarAtraso(const string& tituloLivro, int diasAtraso) const override;
        friend class Biblioteca;
};

//-------------------- Subclasse: Estudante --------------------//
class Estudante : public Pessoa {
private:
    int maxLivros;
    double descontoMulta;
    string curso;

public:
    Estudante(int nif, const string& nome, int NEmprestimosTotal, int NEmprestimosAtivos, int NReservas, double MultaPorPagar, double MultaPaga, const string& curso);
    void mostrarInformacoes() const override;
    double calcularMulta(int diasAtraso) const override;
    string getCurso() const { return curso; }
    void setCurso(const string& novoCurso) { curso = novoCurso; }
    int getMaxReservas() const override { return 5; }
    void notificarAtraso(const string& tituloLivro, int diasAtraso) const override;
    friend class Biblioteca;
};

//-------------------- Subclasse: Professor --------------------//
class Professor : public Pessoa {
    private:
        int maxLivros;
        double descontoMulta;
        string departamento;

    public:
        Professor(int nif, const string& nome, int NEmprestimosTotal, int NEmprestimosAtivos, int NReservas, double MultaPorPagar, double MultaPaga, const string& departamento);
        void mostrarInformacoes() const override;
        double calcularMulta(int diasAtraso) const override;
        string getDepartamento() const { return departamento; }
        void setDepartamento(const string& novoDepartamento) { departamento = novoDepartamento; }
        int getMaxReservas() const override { return 4; }
        void notificarAtraso(const string& tituloLivro, int diasAtraso) const override;
        friend class Biblioteca;
};

//-------------------- Subclasse: Senior --------------------//
class Senior : public Pessoa {
    private:
        int maxLivros;
        double descontoMulta;
        int idade;

    public:
        Senior(int nif, const string& nome, int NEmprestimosTotal, int NEmprestimosAtivos, int NReservas, double MultaPorPagar, double MultaPaga, int idade);
        void mostrarInformacoes() const override;
        double calcularMulta(int diasAtraso) const override;
        int getIdade() const { return idade; }
        void setIdade(int novaIdade) { idade = novaIdade; }
        int getMaxReservas() const override { return 3; }
        void notificarAtraso(const string& tituloLivro, int diasAtraso) const override;
        friend class Biblioteca;
};

Pessoa* criarLeitor();

#endif



