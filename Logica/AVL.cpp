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

NodoAVL *AVL::rotarDerecha(NodoAVL *nodo) {
    NodoAVL* hijo = nodo->izquierda;
    NodoAVL* subarbolMedio = hijo->derecha;

    hijo->derecha = nodo;
    nodo->izquierda = subarbolMedio;

    actualizarAltura(nodo);
    actualizarAltura(hijo);
    return hijo;
}

NodoAVL *AVL::rotarIzquierda(NodoAVL *nodo) {
    NodoAVL* hijo = nodo->derecha;
    NodoAVL* subarbolMedio = hijo->izquierda;

    hijo->izquierda = nodo;
    nodo->derecha = subarbolMedio;

    actualizarAltura(nodo);
    actualizarAltura(hijo);
    return hijo;
}

NodoAVL* AVL::balancear(NodoAVL* nodo) {}
