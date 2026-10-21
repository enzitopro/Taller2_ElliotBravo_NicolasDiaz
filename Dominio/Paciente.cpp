#include "Paciente.h"
#include <iostream>
using namespace std;

Paciente::Paciente(string i, string n, int e, double temp, int presion,
                int d, string tipo, bool tra, bool sn, bool rc, int dias)  : Persona(n, e){
    id = i;
    temperatura = temp;
    presionArterial = presion;
    dolor = d;
    tipoDolor = tipo;
    trauma = tra;
    sintomasNeurologicos = sn;
    requiereCirugia = rc;
    diasHospitalizacion = dias;
    servicioDestino = "";
}

string Paciente::getId() const {
    return id;
}

double Paciente::getTemperatura() const {
    return temperatura;
}

int Paciente::getPresionArterial() const {
    return presionArterial;
}

int Paciente::getDolor() const {
    return dolor;
}

string Paciente::getTipoDolor() const {
    return tipoDolor;
}

bool Paciente::getTrauma() const {
    return trauma;
}

bool Paciente::getSintomasNeurologicos() const {
    return sintomasNeurologicos;
}

bool Paciente::getRequiereCirugia() const {
    return requiereCirugia;
}

int Paciente::getDiasHospitalizacion() const {
    return diasHospitalizacion;
}

string Paciente::getServicioDestino() const {
    return servicioDestino;
}

void Paciente::setServicioDestino(string servicio) {
    servicioDestino = servicio;
}

void Paciente::imprimirInfo() const {
    cout << "Id: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << endl;
    cout << "Temperatura: " << temperatura << endl;
    cout << "Presion Arterial: " << presionArterial << endl;
    cout << "Dolor: " << dolor << endl;
    cout << "Tipo de Dolor: " << tipoDolor << endl;
    cout << "Trauma: " << trauma << endl;
    cout << "Sintomas Neurologicos: " << sintomasNeurologicos << endl;
    cout << "Requie Cirugia: " << requiereCirugia << endl;
    cout << "Dias de Hospitalizacion: " << diasHospitalizacion << endl;
    if (servicioDestino != "") {
        cout << "Servicio: " << servicioDestino << endl;
    }
}
