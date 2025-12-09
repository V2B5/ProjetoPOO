#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>

#include "Livro.h"
#include "Pessoa.h"
#include "Emprestimo.h"

using namespace std;

class Biblioteca {
    private:
        vector<Livro*> livros;                                      // Armazena os livros num vetor
        map<int, Pessoa*> leitores;                                 // Mapa para armazenar os leitores, usa o NIF como chave
        vector<Emprestimo> emprestimos;                             // Lista de emprástimos que estão ativos
        map<string, queue<Pessoa*>> reservasNormais;                //Mapa para as reservas (fazer a fila de requisitos dos leitores)
        map<string, queue<Pessoa*>> reservasPrioritarias;
        map<int, double> multasRegistradas;

        int calcularDiasAtraso(const string& dataEmprestimo, const string& dataDevolucao) const;

    public:
        Biblioteca();
        ~Biblioteca();

        // Carregar pessoas e livros dos ficheiros Pessoas.txt e Livros.txt
        void carregarPessoas(const string& ficheiro); //Feito
        void carregarLivros(const string& ficheiro); //Feito

        // Métodos para Gestão de livros
        void adicionarLivro(Livro* livro); //Feito
        void editarLivro(Livro* livro); //Feito
        void listarLivrosPorTipo(const string& tipo) const; //Feito
        Livro* procurarLivro(const string& titulo) const; //Feito

        // Métodos para Gestão de leitores
        void adicionarLeitor(Pessoa* leitor); //Feito
        void editarLeitor(Pessoa* leitor); //Feito
        void listarLeitoresPorTipo(const string& tipo) const; //Feito
        Pessoa* procurarLeitor(int nif) const; //Feito

        // Métodos para Gestão de empréstimos
        void realizarEmprestimo(Pessoa* leitor, Livro* livro, const string& dataEmprestimo); //Feito
        void reservarLivro(Pessoa* leitor, const string& tituloLivro); //Feito
        void devolverLivro(int nifLeitor, const string& tituloLivro, const string& dataDevolucao); //Feito
        void listarEmprestimos() const; //Feito
        void prorrogarEmprestimo(int nifLeitor, const string& tituloLivro, const string& novaData); //Feito

        // Métodos para Gestão de relatórios
        void gerarRelatorioEmprestimos(ofstream* arquivo = nullptr) const;
        void gerarRelatorioMultas(ofstream* arquivo = nullptr) const;
        void gerarRelatorioLivrosCategoria(ofstream* arquivo = nullptr) const;

        // Métodos para Persistência de dados
        void gravarDados(const string& ficheiro) const;
        void gravarDadosEmFicheiro();

};

#endif



