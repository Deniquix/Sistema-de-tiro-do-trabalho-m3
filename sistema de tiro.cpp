#include <iostream>
#include <windows.h>
#include <conio.h>
#define TAM 25

using namespace std;

int mapa[TAM][TAM] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

};
// posição do personagem
int x = 23, y = 23;

// tiro
bool projetilAtivo = false;
int px = -1, py = -1;
DWORD ultimoTempo = GetTickCount();

COORD coord = {0, 0};

//Nao mexer
void inicializarConsole() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
}
//Nao mexer

// printador do mapa, personagem e projétil
void desenharMapa() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (i == x && j == y) {
                cout << char(36); // personagem
            } else if (projetilAtivo == true && i == px && j == py) {
                cout << "^"; // tiro
            } else {
                switch (mapa[i][j]) {
                    case 0: cout << " "; break;
                    case 1: cout << char(219); break;
                }
            }
        }
        cout << "\n";
    }
}

// movimento do disparo
void atualizarProjetil() {
    if (projetilAtivo && GetTickCount() - ultimoTempo > 100) {
        px--;
        if (px < 0 or mapa[px][py] == 1) {
            projetilAtivo = false;
        }
        ultimoTempo = GetTickCount();
    }
}

// disparo 1 por vez
void dispararProjetil() {
    if (projetilAtivo == false) {
        projetilAtivo = true;
        px = x - 1;
        py = y;
        ultimoTempo = GetTickCount();
    }
}

// mover e atirar
void tecla() {
    if (_kbhit()) {
        char tecla = getch();
        switch (tecla) {
            case 75: case 'a': if (mapa[x][y - 1] != 1) y--; break;
            case 77: case 'd': if (mapa[x][y + 1] != 1) y++; break;
            case 32: dispararProjetil(); break;
        }
    }
}

int main() {
    inicializarConsole();

    while (true) {
        atualizarProjetil();
        desenharMapa();
        tecla();
    }

    return 0;
}
