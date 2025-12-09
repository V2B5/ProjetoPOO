#ifndef LEITOR_H_INCLUDED
#define LEITOR_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

using namespace std;

// Classe base: Leitor
class Leitor {
    protected:
        string nome;
        string id;
        int maxLivros;

    public:
        Leitor(const string& nome, const string& id, int maxLivros);
        virtual ~Leitor();

        string getNome() const;
        string getId() const;
        int getMaxLivros() const;
};

// Subclasse: LeitorComum
class LeitorComum : public Leitor {
    public:
        LeitorComum(const string& nome, const string& id);
};

// Subclasse: Estudante
class Estudante : public Leitor {
    private:
        double descontoMulta;

    public:
        Estudante(const string& nome, const string& id, double descontoMulta);
        double getDescontoMulta() const;
};

// Subclasse: Professor
class Professor : public Leitor {
    private:
        double descontoMulta;
        int diasProrrogacao;

    public:
        Professor(const string& nome, const string& id, double descontoMulta, int diasProrrogacao);
        double getDescontoMulta() const;
        int getDiasProrrogacao() const;
};

// Subclasse: Senior
class Senior : public Leitor {
    private:
        bool acessoPrioritario;

    public:
        Senior(const string& nome, const string& id, bool acessoPrioritario);
        bool temAcessoPrioritario() const;
};

#endif // LEITOR_H_INCLUDED



