//
// Created by nicol on 21-10-2026.
//

#ifndef TALLER2_ELLIOTBRAVO_NICOLASDIAZ_NODODECISION_H
#define TALLER2_ELLIOTBRAVO_NICOLASDIAZ_NODODECISION_H
#include <string>




class NodoDecision {
private:
    int valor;
    std::string nombre;
    NodoDecision* izquierda;
    NodoDecision* derecha;
public:
    NodoDecision(int valor, std::string nombre);
    NodoDecision* getIzquierda();
    NodoDecision* getDerecha();
    void setIzquierda(NodoDecision* izquierda);
    void setDerecha(NodoDecision* derecha);
    int getValor();
    std::string getNombre();
};




#endif //TALLER2_ELLIOTBRAVO_NICOLASDIAZ_NODODECISION_H