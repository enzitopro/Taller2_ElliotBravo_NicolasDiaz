#include "Arbol.h"
#include <iostream>
using namespace std;

Arbol::Arbol() {
    raiz = nullptr;
    arbolConstruir();
}

Arbol::~Arbol() {
    destruir(raiz);
    raiz = nullptr;
}

void Arbol::destruir(NodoDecision* nodo) {
    if (nodo == nullptr) {
        return;
    }
    destruir(nodo->getIzquierda());
    destruir(nodo->getDerecha());
    delete nodo;
}

void Arbol::arbolConstruir() {
    //URGENCIAS-> PEDIATRIA -> TRAUMA/CIRUGIA -> NEUROLOGIA -> CARDIOLOGIA -> HOPITALIZACION -> MEDICINA GENERAL
    raiz = new NodoDecision(1, "Temperatura >= 40 o Dolor >= 9");

    NodoDecision* edad = new NodoDecision(2, "Edad < 14");
    NodoDecision* trauma = new NodoDecision(3, "Trauma == 1");
    NodoDecision* cirugia = new NodoDecision(4, "RequiereCirugia == 1");
    NodoDecision* cirugiaSinTrauma = new NodoDecision(4, "RequiereCirugia == 1");
    NodoDecision* neurologico = new NodoDecision(5, "SintomasNeurologicos == 1 o TipoDolor == cabeza");
    NodoDecision* pecho = new NodoDecision(6, "TipoDolor == pecho o PresionArterial >= 160");
    NodoDecision* urgenciaModerada = new NodoDecision(8, "Temperatura >= 38.5 o Dolor >= 7");
    NodoDecision* hospitalizacion = new NodoDecision(7, "DiasHospitalizacion >= 2");

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
    pecho->setDerecha(urgenciaModerada);
    //urgencia moderada
    urgenciaModerada->setIzquierda(new NodoDecision(0,"Urgencias"));
    urgenciaModerada->setDerecha(hospitalizacion);
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
        return p->getTipoDolor() == "pecho" || p->getPresionArterial() >= 160;
    }
    if (valor == 7) {
        return p->getDiasHospitalizacion() >= 2;
    }
    if (valor == 8) {
        return p->getTemperatura() >= 38.5 || p->getDolor() >= 7;
    }
    return false;
}
string Arbol::clasificar(Paciente *p) {
    if (p== nullptr) {
        cout << "Paciente invalido, no se puede clasificar" << endl;
        return "";
    }

    NodoDecision* actual = raiz;
    string ruta = "";

    while (actual != nullptr) {
        if (actual->getValor()==0) {
            cout << "Ruta: " << ruta << actual->getNombre() << endl;
            p->setServicioDestino(actual->getNombre());
            return actual->getNombre();
        }

        ruta += actual->getNombre();
        if (pregunta(p,actual->getValor())) {
            ruta += " (SI) -> ";
            actual = actual->getIzquierda();
        }else {
            ruta += " (NO) -> ";
            actual = actual->getDerecha();
        }

    }
    cout << "No se pudo determinar un servicio" << endl;
    return "";
}

void Arbol::preorden(NodoDecision* nodo) {
    if (nodo == nullptr) {
        return;
    }

    mostrarNodo(nodo);
    preorden(nodo->getIzquierda());
    preorden(nodo->getDerecha());
}

void Arbol::inorden(NodoDecision *nodo) {
    if (nodo == nullptr) {
        return;
    }
    inorden(nodo->getIzquierda());
    mostrarNodo(nodo);
    inorden(nodo->getDerecha());
}

void Arbol::postorden(NodoDecision* nodo) {
    if (nodo == nullptr) {
        return;
    }
    postorden(nodo->getIzquierda());
    postorden(nodo->getDerecha());
    mostrarNodo(nodo);
}

void Arbol::mostrarNodo(NodoDecision* nodo) {
    if (nodo->getValor() == 0) {
        cout << "Servicio: " << nodo->getNombre() << endl;
    }else {
        cout << "Condicion: " << nodo->getValor() << " "<< nodo->getNombre() << endl;
    }
}

void Arbol::MostrarInorden() {
    cout << "=== INORDEN ===" << endl;
    inorden(raiz);
}
void Arbol::MostrarPreorden() {
    cout << "=== PREORDEN ===" << endl;
    preorden(raiz);
}
void Arbol::MostrarPostorden() {
    cout << "=== POSTORDEN ===" << endl;
    postorden(raiz);
}


