
#ifndef TALLER2_ELLIOTBRAVO_NICOLASDIAZ_ARBOL_H
#define TALLER2_ELLIOTBRAVO_NICOLASDIAZ_ARBOL_H
#include "NodoDecision.h"
#include "../Dominio/Paciente.h"
class Arbol {
private:
    NodoDecision* raiz;

    void arbolConstruir();
    bool pregunta(Paciente* p,int valor);


    void preorden(NodoDecision* nodo);
    void inorden(NodoDecision* nodo);
    void postorden(NodoDecision* nodo);
    void mostrarNodo(NodoDecision* nodo);

    void destruir(NodoDecision* nodo);
public:
    Arbol();
    ~Arbol();
    std::string clasificar(Paciente* p);

    void MostrarPreorden();
    void MostrarInorden();
    void MostrarPostorden();
};

#endif
















#endif //TALLER2_ELLIOTBRAVO_NICOLASDIAZ_ARBOL_H

