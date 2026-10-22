#include "Arbol.h"

Arbol::Arbol() {
    raiz = nullptr;
    arbolConstruir();
}

void Arbol::arbolConstruir() {
    //URGENCIAS-> PEDIATRIA -> TRAUMA/CIRUGIA -> NEUROLOGIA -> CARDIOLOGIA -> HOPITALIZACION -> MEDICINA GENERAL
    raiz = new NodoDecision(1, "");

    NodoDecision* edad = new NodoDecision(2, "");
    NodoDecision* trauma = new NodoDecision(3, "");
    NodoDecision* cirugia= new NodoDecision(4, "");
    NodoDecision* cirugiaSinTrauma = new NodoDecision(4, "");
    NodoDecision* neurologico = new NodoDecision(5, "");
    NodoDecision* pecho = new NodoDecision(6, "");
    NodoDecision* hospitalizacion = new NodoDecision(7, "");

    //Urgencias
    raiz->setIzquierda(new NodoDecision(0,"Urgencias"));
    raiz->setDerecha(edad);
    //pediatria
    edad->setIzquierda(new NodoDecision(0,"Pediatria"));
    edad->setDerecha(trauma);
    //trauma
    trauma->setIzquierda(cirugia);
    trauma->setDerecha(cirugiaSinTrauma);
    //cirugia
    cirugia->setIzquierda(new NodoDecision(0,"Cirugia"));
    cirugia->setDerecha(new NodoDecision(0,"Traumatologia"));
    cirugiaSinTrauma->setIzquierda(new NodoDecision(0,"Cirugia"));
    cirugiaSinTrauma->setDerecha(neurologico);
    //Neurologico
    neurologico->setIzquierda(new NodoDecision(0,"Neurologia"));
    neurologico->setDerecha(pecho);
    // cardiologia
    pecho->setIzquierda(new NodoDecision(0,"Cardiologia"));
    pecho->setDerecha(hospitalizacion);
    //hospitalizacion
    hospitalizacion->setIzquierda(new NodoDecision(0,"Hospitalizacion"));
    hospitalizacion->setDerecha(new NodoDecision(0,"Medicina General"));
}

bool Arbol::pregunta(Paciente *p, int valor) {
    if (valor == 1) {
        return p->getTemperatura() >= 40.0 || p->getDolor() >= 9;
    }

    if (valor == 2) {
        return p->getEdad() < 14;
    }
    if (valor == 3) {
        return p->getTrauma();
    }
    if (valor == 4) {
        return p->getRequiereCirugia();
    }
    if (valor == 5) {
        return p->getSintomasNeurologicos() || p->getTipoDolor() == "cabeza";
    }
    if (valor == 6) {
        return p->getTipoDolor() == "pecho";
    }
    if (valor == 7) {
        return p->getDiasHospitalizacion() >= 2;
    }
    return false;
}
