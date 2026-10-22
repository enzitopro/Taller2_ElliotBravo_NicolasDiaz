//
// Created by nicol on 21-10-2026.
//

#ifndef TALLER2_ELLIOTBRAVO_NICOLASDIAZ_NODODECISION_H
#define TALLER2_ELLIOTBRAVO_NICOLASDIAZ_NODODECISION_H
#include <string>

#include "NodoPaciente.h"


class NodoDecision {
    private:
    int valor;
    std::string nombre;
    NodoDecision* izquierda;
    NodoDecision* derecha;
    public:
    NodoDecision(int valor, std::string nombre);
    nodoDecision* getIzquierda();
    nodoDecision* getDerecha();
    void setIzquierda(nodoDecision* izquierda);
    void setDerecha(nodoDecision* derecha);
};




#endif //TALLER2_ELLIOTBRAVO_NICOLASDIAZ_NODODECISION_H
