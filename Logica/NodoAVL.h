//
// Created by mewgant on 24-10-2026.
//

#ifndef TALLER2_ELLIOTBRAVO_NICOLASDIAZ_NODOAVL_H
#define TALLER2_ELLIOTBRAVO_NICOLASDIAZ_NODOAVL_H
#include "../Dominio/Paciente.h"
struct NodoAVL {
    Paciente* paciente;
    NodoAVL* izquierda;
    NodoAVL* derecha;
    int altura;

    NodoAVL(Paciente* p) {
        paciente = p;
        izquierda = nullptr;
        derecha = nullptr;
        altura = 1;
    }
};


#endif //TALLER2_ELLIOTBRAVO_NICOLASDIAZ_NODOAVL_H
