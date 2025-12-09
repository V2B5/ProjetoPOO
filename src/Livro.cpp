#include "../include/Livro.h"

// Construtor da classe base Livro
Livro::Livro(const string& tipo, const string& titulo, const string& autor, int anoPublicacao, bool disponivel)
    : tipo(tipo), titulo(titulo), autor(autor), anoPublicacao(anoPublicacao), disponivel(disponivel) {}

Livro::~Livro() {}

void Livro::mostrarInformacoesLivro() const {
    cout << "Título: " << titulo << endl;
    cout << "Autor: " << autor << endl;
    cout << "Ano de Publicação: " << anoPublicacao << endl;
    cout << "Disponível: " << (disponivel ? "Sim" : "Não") << endl;
}

// ------------------ Subclasse: LivroFiccao ------------------ //
LivroFiccao::LivroFiccao(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, const string& genero, const string& isbn)
    : Livro("Ficcao", titulo, autor, anoPublicacao, disponivel), genero(genero), isbn(isbn) {}

void LivroFiccao::mostrarInformacoesLivro() const {
    Livro::mostrarInformacoesLivro();
    cout << "Género: " << genero << endl;
    cout << "ISBN: " << isbn << endl;
}

// ------------------ Subclasse: LivroCientifico ------------------ //
LivroCientifico::LivroCientifico(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, const string& areaCientifica, const string& isbn)
    : Livro("Cientifico", titulo, autor, anoPublicacao, disponivel), areaCientifica(areaCientifica), isbn(isbn) {}

void LivroCientifico::mostrarInformacoesLivro() const {
    Livro::mostrarInformacoesLivro();
    cout << "Área Científica: " << areaCientifica << endl;
    cout << "ISBN: " << isbn << endl;
}

// ------------------ Subclasse: LivroEducativo ------------------ //
LivroEducativo::LivroEducativo(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, const string& nivelEducacional, const string& isbn)
    : Livro("Educativo", titulo, autor, anoPublicacao, disponivel), nivelEducacional(nivelEducacional), isbn(isbn) {}

void LivroEducativo::mostrarInformacoesLivro() const {
    Livro::mostrarInformacoesLivro();
    cout << "Nível Educacional: " << nivelEducacional << endl;
    cout << "ISBN: " << isbn << endl;
}

// ------------------ Subclasse: Revista ------------------ //
Revista::Revista(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, int numeroEdicao)
    : Livro("Revista", titulo, autor, anoPublicacao, disponivel), numeroEdicao(numeroEdicao) {}

void Revista::mostrarInformacoesLivro() const {
    Livro::mostrarInformacoesLivro();
    cout << "Número da Edição: " << numeroEdicao << endl;
}

// ------------------ Subclasse: Jornal ------------------ //
Jornal::Jornal(const string& titulo, const string& autor, int anoPublicacao, bool disponivel, const string& dataPublicacao)
    : Livro("Jornal", titulo, autor, anoPublicacao, disponivel), dataPublicacao(dataPublicacao) {}

void Jornal::mostrarInformacoesLivro() const {
    Livro::mostrarInformacoesLivro();
    cout << "Data de Publicação: " << dataPublicacao << endl;
}



