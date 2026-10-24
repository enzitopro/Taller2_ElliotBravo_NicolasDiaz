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

NodoAVL* AVL::balancear(NodoAVL* nodo) {
    actualizarAltura(nodo);
    int balance = factorBalance(nodo);
    string id = nodo->paciente->getId();

    if (balance < -1) {
        if (factorBalance(nodo->izquierda) <= 0) {
            cout << " Rotacion simple derecha (caso LL) en " << id << endl;
            return rotarDerecha(nodo);
        }
        cout << " Rotacion doble derecha-izquierda (caso RL) en " << id << endl;
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }
    return nodo;
}

bool AVL::insertar(Paciente *paciente) {
    if (paciente == nullptr) {
        return false;
    }
    bool insertado = false;
    raiz = insertar(raiz, paciente, insertado);
    return insertado;
}

NodoAVL *AVL::insertar(NodoAVL *nodo, Paciente *paciente, bool &insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoAVL(paciente);
    }

    string idNuevo = paciente->getId();
    string idActual = nodo->paciente->getId();

    if (idNuevo < idActual) {
        nodo->izquierda = insertar(nodo->izquierda, paciente, insertado);
    }
    else if (idNuevo > idActual) {
        nodo->derecha = insertar(nodo->derecha, paciente, insertado);
    }
    else {
        insertado = false;
        return nodo;
    }
    return balancear(nodo);
}

bool AVL::eliminar(string id) {
    bool eliminado = false;
    raiz = eliminar(raiz, id, eliminado);
    return eliminado;
}

NodoAVL *AVL::buscarMinimo(NodoAVL *nodo) {
    while (nodo->izquierda != nullptr) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

NodoAVL *AVL::eliminar(NodoAVL *nodo, std::string id, bool &eliminado) {
    if (nodo == nullptr) {
        return nullptr;
    }

    string idActual = nodo->paciente->getId();
    if (id < idActual) {
        nodo->izquierda = eliminar(nodo->izquierda, id, eliminado);
    }
    else if (id > idActual) {
        nodo->derecha = eliminar(nodo->derecha, id, eliminado);
    }
    else {
        eliminado = true;

        // caso sin hijos o con un solo hijo
        if (nodo->izquierda == nullptr || nodo->derecha == nullptr) {
            NodoAVL* hijo = nodo->izquierda;
            if (hijo == nullptr) {
                hijo = nodo->derecha;
            }
            delete nodo->paciente;
            delete nodo;
            return hijo;
        }

        //caso dos hijos
        NodoAVL* sucesor = buscarMinimo(nodo->derecha);
        Paciente* pacienteBorrado = nodo->paciente;
        nodo->paciente = sucesor->paciente;
        sucesor->paciente = pacienteBorrado;
        nodo->derecha = eliminar(nodo->derecha, pacienteBorrado->getId(), eliminado);
    }
    return balancear(nodo);
}

Paciente *AVL::buscarPorId(std::string id, std::string &ruta) {
    NodoAVL* actual = raiz;
    ruta = "";
    while (actual != nullptr) {
        string idActual = actual->paciente->getId();
        if (ruta != "") {
            ruta += " -> ";
        }
        ruta += idActual;

        if (id == idActual) {
            return actual->paciente;
        }
        if (id < idActual) {
            actual = actual->izquierda;
        }
        else {
            actual = actual->derecha;
        }
    }
    return nullptr;
}

Paciente *AVL::buscarPorNombre(std::string nombre) {
    return buscarPorNombre(raiz, nombre);
}

Paciente* AVL::buscarPorNombre(NodoAVL* nodo, std::string nombre) {
    if (nodo == nullptr) {
        return nullptr;
    }
    if (nodo->paciente->getNombre() == nombre) {
        return nodo->paciente;
    }
    Paciente* encontrado = buscarPorNombre(nodo->izquierda, nombre);
    if (encontrado != nullptr) {
        return encontrado;
    }
    return buscarPorNombre(nodo->derecha, nombre);
}


