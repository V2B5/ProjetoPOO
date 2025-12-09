#ifndef LIVRO_H
#define LIVRO_H

#include <iostream>

using namespace std;

class Livro {
    protected:
        string tipo; // Tipo do livro (Ficcao, Cientifico, Educativo, Revista, Jornal)
        string titulo;
        string autor;
        int anoPublicacao;
        bool disponivel;

    public:
        Livro(const string& tipo, const string& titulo, const string& autor, int anoPublicacao, bool disponivel);
        virtual ~Livro();

        virtual void mostrarInformacoesLivro() const;
        string getTipo() const { return tipo; }
        string getTitulo() const { return titulo; }
        string getAutor() const { return autor; }
        int getAnoPublicacao() const { return anoPublicacao; }
        bool estaDisponivel() const { return disponivel; }

        void setTitulo(const string& novoTitulo) { titulo = novoTitulo; }
        void setAutor(const string& novoAutor) { autor = novoAutor; }
        void setAnoPublicacao(int novoAno) { anoPublicacao = novoAno; }
        void setDisponibilidade(bool status) { disponivel = status; }
};

//-------------------- Subclasse: LivroFiccao --------------------//
class LivroFiccao : public Livro {
    private:
        string genero;
        string isbn;

    public:
        LivroFiccao(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, const string& genero, const string& isbn);
        void mostrarInformacoesLivro() const override ;
        string getGenero() const { return genero; }
        void setGenero(const string& novoGenero) { genero = novoGenero; }
        friend class Biblioteca;
};

//-------------------- Subclasse: LivroCientifico --------------------//
class LivroCientifico : public Livro {
    private:
        string areaCientifica;
        string isbn;

    public:
        LivroCientifico(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, const string& areaCientifica, const string& isbn);
        void mostrarInformacoesLivro() const override;
        string getAreaCientifica() const { return areaCientifica; }
        void setAreaCientifica(const string& novaArea) { areaCientifica = novaArea; }
        friend class Biblioteca;
};

//-------------------- Subclasse: LivroEducativo --------------------//
class LivroEducativo : public Livro {
    private:
        string nivelEducacional;
        string isbn;

    public:
        LivroEducativo(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, const string& nivelEducacional, const string& isbn);
        void mostrarInformacoesLivro() const override;
        string getNivelEducacional() const { return nivelEducacional; }
        void setNivelEducacional(const string& novoNivel) { nivelEducacional = novoNivel; }
        friend class Biblioteca;
};

//-------------------- Subclasse: Revista --------------------//
class Revista : public Livro {
    private:
        int numeroEdicao;

    public:
        Revista(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, int numeroEdicao);
        void mostrarInformacoesLivro() const override;
        int getNumeroEdicao() const { return numeroEdicao; }
        void setNumeroEdicao(int novoNumero) { numeroEdicao = novoNumero; }
        friend class Biblioteca;
};

//-------------------- Subclasse: Jornal --------------------//
class Jornal : public Livro {
    private:
        string dataPublicacao;

    public:
        Jornal(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, const string& dataPublicacao);
        void mostrarInformacoesLivro() const override;
        string getDataPublicacao() const { return dataPublicacao; }
        void setDataPublicacao(const string& novaData) { dataPublicacao = novaData; }
        friend class Biblioteca;
};

#endif



