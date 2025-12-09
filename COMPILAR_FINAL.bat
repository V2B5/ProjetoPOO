@echo off
cd /d "%~dp0"

echo ========================================
echo   CONFIGURAR AMBIENTE E COMPILAR
echo ========================================
echo.

REM Adicionar MinGW ao PATH temporariamente
set PATH=C:\Program Files\CodeBlocks\MinGW\bin;%PATH%

echo PATH configurado com MinGW
echo.

if not exist "bin\Debug" mkdir "bin\Debug"

echo Compilando...
echo.

g++ -v -std=c++17 -Iinclude main.cpp src\Biblioteca.cpp src\Livro.cpp src\Pessoa.cpp src\Emprestimo.cpp src\Leitor.cpp src\Geral.cpp src\Uteis.cpp -o bin\Debug\ProjetoPOO.exe

if exist bin\Debug\ProjetoPOO.exe (
    echo.
    echo ========================================
    echo   SUCESSO!
    echo ========================================
    echo.
    echo Executando...
    echo.
    bin\Debug\ProjetoPOO.exe
) else (
    echo.
    echo ========================================
    echo   ERRO NA COMPILACAO!
    echo ========================================
)

echo.
pause
