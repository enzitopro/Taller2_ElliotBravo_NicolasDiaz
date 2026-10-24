//
// Created by mewgant on 24-10-2026.
//

#include "AVL.h"
#include <iostream>
using namespace std;

AVL::AVL() {
    raiz = nullptr;
}

AVL::~AVL() {
    destruir(raiz);
    raiz = nullptr;
}

void AVL::destruir(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }
    destruir(nodo->izquierda);
    destruir(nodo->derecha);
    delete nodo->paciente;
    delete nodo;
}

int AVL::altura (NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return altura(nodo->derecha) - altura(nodo->izquierda);
}

void AVL::actualizarAltura(NodoAVL *nodo) {
    int alturaIzquierda = altura(nodo->izquierda);
    int alturaDerecha = altura(nodo->derecha);
    if (alturaIzquierda > alturaDerecha) {
        nodo->altura = alturaIzquierda + 1;
    }
    else {
        nodo->altura = alturaDerecha + 1;
    }
}


