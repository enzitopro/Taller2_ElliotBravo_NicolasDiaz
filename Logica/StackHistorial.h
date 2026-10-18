
#ifndef TALLER2_ELLIOTBRAVO_NICOLASDIAZ_STACKHISTORIAL_H
#define TALLER2_ELLIOTBRAVO_NICOLASDIAZ_STACKHISTORIAL_H

#include "NodoPaciente.h"

class StackHistorial {
private:
    NodoPaciente* Primero;

    public:
    StackHistorial();
    ~StackHistorial();

    void push(Paciente* paciente);
    void pop();
    Paciente* top();


    void mostrarHistorial();
};















#endif //TALLER2_ELLIOTBRAVO_NICOLASDIAZ_STACKHISTORIAL_H
