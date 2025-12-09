#ifndef UTEIS_H
#define UTEIS_H

#include <stdlib.h>
#include <iostream>
#include "Biblioteca.h"

class Uteis {
public:
    // Função para mostrar o menu principal
    static void menuPrincipal(Biblioteca& biblioteca);
    static int calcularDiferencaDias(const string& data1, const string& data2);
    static void menuExibirHistoricoEmprestimos(Biblioteca& biblioteca);

private:
    //--------------- Livros ---------------//
    static void menuGestaoLivros(Biblioteca& biblioteca);
    static void menuAdicionarLivro(Biblioteca& biblioteca);
    static void menuEditarLivro(Biblioteca& biblioteca);
    static void menuListarLivros(Biblioteca& biblioteca);
    //--------------- Leitores ---------------//
    static void menuGestaoLeitores(Biblioteca& biblioteca);
    static void menuAdicionarLeitor(Biblioteca& biblioteca);
    static void menuEditarLeitor(Biblioteca& biblioteca);
    static void menuProcurarLeitor(Biblioteca& biblioteca);
    static void menuListarLeitores(Biblioteca& biblioteca);
    static void menuProcurarLivro(Biblioteca& biblioteca);
    //--------------- Emprestimos ---------------//
    static void menuGestaoEmprestimos(Biblioteca& biblioteca);
    static void menuRealizarEmprestimo(Biblioteca& biblioteca);
    static void menuReservarLivro(Biblioteca& biblioteca);
    static void menuDevolverLivro(Biblioteca& biblioteca);
    static void menuListarEmprestimos(Biblioteca& biblioteca);
    static void menuProrrogarEmprestimo(Biblioteca& biblioteca);
    //--------------- Relatórios ---------------//
    static void menuRelatorios(Biblioteca& biblioteca);
    void menuGerarRelatorioMultasPendentes(Biblioteca& biblioteca);

    // Função auxiliar para exibir opções e obter escolha do utilizador
    static int obterEscolha(int min, int max);
};

#endif



