#ifndef TALLER2_ELLIOTBRAVO_NICOLASDIAZ_LISTAPACIENTES_H
#define TALLER2_ELLIOTBRAVO_NICOLASDIAZ_LISTAPACIENTES_H


#include "NodoPaciente.h"

class ListaPacientes {
 private:
   NodoPaciente* inicio;

 public:
   ListaPacientes();

   ~ListaPacientes();
    //metodos
    Paciente* buscarPaciente(std:: string id);
   void agregarPaciente(Paciente* p);
   void mostrarPacientes() const;
    int getCantidad() const;

};

#endif