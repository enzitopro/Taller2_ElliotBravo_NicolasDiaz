#include "Servicio.h"

#include <iostream>
#include <ostream>

#include "Paciente.h"

using namespace std;

Servicio::Servicio(std::string n) {
    nombre = n;
}

string Servicio::getNombre() const {
    return nombre;
}

bool Servicio::recibirPaciente(Paciente* p) {
    return pacientes.insertar(p);
}

void Servicio::mostrarEstado()  {
    cout << "=== ESTADO " << nombre << " ===" << endl;
    if (pacientes.estaVacio()) {
        cout << "Sin Pacientes "<< endl;
        return;
    }


    cout << "Pacientes en el departamento de " << nombre << ": " << endl;
    pacientes.mostrarPacientes();
}
void Servicio::mostrarRecorridos() {
    cout << "=== AVL de " << nombre << " ===" << endl;

    if (pacientes.estaVacio()) {
        cout << "Sin Pacientes "<< endl;
        return;
    }
    pacientes.mostrarInorden();
    pacientes.mostrarPreorden();
    pacientes.mostrarPostorden();

    cout << "Altura del arbol: " << pacientes.getAltura() << endl;
    cout << "Factores de balance" << endl;
    pacientes.mostrarFactoresBalance();


}

Paciente *Servicio::buscarPaciente(string id) {
    string ruta;
    return pacientes.buscarPorId(id, ruta);
}
Paciente* Servicio::buscarPorId(string id,string &ruta) {
    return pacientes.buscarPorId(id,ruta);

}

Paciente *Servicio::buscarPorNombre(string nombre) {
    return pacientes.buscarPorNombre(nombre);
}

bool Servicio::eliminarPaciente(string id) {
    return pacientes.eliminar(id);

}
