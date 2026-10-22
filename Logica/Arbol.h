//
// Created by nicol on 22-10-2026.
//

#ifndef TALLER2_ELLIOTBRAVO_NICOLASDIAZ_ARBOL_H
#define TALLER2_ELLIOTBRAVO_NICOLASDIAZ_ARBOL_H
#include "NodoDecision.h"
#include "../Dominio/Paciente.h"
class Arbol {
private:
    NodoDecision* raiz;

    void arbolConstruir();
    bool pregunta(Paciente* p,int valor);
public:
    Arbol();
    ~Arbol();


};
















#endif //TALLER2_ELLIOTBRAVO_NICOLASDIAZ_ARBOL_H

