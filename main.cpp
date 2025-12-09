#include <locale.h>
#include <time.h>
#include <windows.h>
#include "Biblioteca.h"
#include "Uteis.h"

int main() {

    // Configurar codificação para Português (Windows-1252)
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);

    srand(0);

    setlocale(LC_ALL, "Portuguese");

    Biblioteca biblioteca;

    // Passa as pessoas do ficheiro para a memória
    biblioteca.carregarPessoas("Pessoas.txt");
    biblioteca.carregarLivros("Livros.txt");
    // Mostra o menu principal
    Uteis::menuPrincipal(biblioteca);

    return 0;
}
