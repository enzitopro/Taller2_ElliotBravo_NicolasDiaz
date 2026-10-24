//
// Created by mewgant on 24-10-2026.
//

#ifndef TALLER2_ELLIOTBRAVO_NICOLASDIAZ_AVL_H
#define TALLER2_ELLIOTBRAVO_NICOLASDIAZ_AVL_H
#include "NodoAVL.h"
#include <string>

class AVL {
private:
    NodoAVL* raiz;

    int altura(NodoAVL* nodo);
    int factorBalance(NodoAVL* nodo);
    void actualizarAltura(NodoAVL* nodo);

    NodoAVL* rotarDerecha(NodoAVL* nodo);
    NodoAVL* rotarIzquierda(NodoAVL* nodo);
    NodoAVL* balancear(NodoAVL* nodo);

    NodoAVL* insertar(NodoAVL* nodo, Paciente* paciente, bool &insertado);
    NodoAVL* eliminar(NodoAVL* nodo, std::string id, bool &eliminado);
    NodoAVL* buscarMinimo(NodoAVL* nodo);
    Paciente* buscarPorNombre(NodoAVL* nodo, std::string nombre);

    void inorden(NodoAVL* nodo);
    void preorden(NodoAVL* nodo);
    void postorden(NodoAVL* nodo);
    void mostrarFactores(NodoAVL* nodo);
    void listarPacientes(NodoAVL* nodo);
    void destruir(NodoAVL* nodo);

public:
    AVL();
    ~AVL();

    bool insertar(Paciente* paciente);
    bool eliminar(std::string id);
    Paciente* buscarPorId(std::string id, std::string &ruta);
    Paciente* buscarPorNombre(std::string nombre);

    bool estaVacio();
    int getAltura();
    void mostrarInorden();
    void mostrarPreorden();
    void mostrarPostorden();
    void mostrarFactoresBalance();
    void mostrarPacientes();

};


#endif //TALLER2_ELLIOTBRAVO_NICOLASDIAZ_AVL_H
