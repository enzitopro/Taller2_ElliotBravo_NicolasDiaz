#include "NodoDecision.h"

using namespace std;

NodoDecision::NodoDecision(int valor, string nombre) {
    this->valor = valor;
    this->nombre = nombre;
    izquierda=nullptr;
    derecha=nullptr;
}

int NodoDecision::getValor() {
    return valor;
}
string NodoDecision::getNombre() {
    return nombre;
}
NodoDecision* NodoDecision::getIzquierda() {
    return izquierda;
}
NodoDecision* NodoDecision::getDerecha() {
    return derecha;
}

void NodoDecision::setIzquierda(NodoDecision* izquierda) {
    this->izquierda = izquierda;
}
void NodoDecision::setDerecha(NodoDecision* derecha) {
    this->derecha = derecha;
}