
#ifndef TALLER2_ELLIOTBRAVO_NICOLASDIAZ_HOSPITAL_H
#define TALLER2_ELLIOTBRAVO_NICOLASDIAZ_HOSPITAL_H
#include "../Logica/ColaPacientes.h"
#include "../Logica/NodoServicio.h"
#include "../Logica/StackHistorial.h"

#include <string>


class Hospital {
    private:
    StackHistorial historial;

    ColaPacientes colaPacientes;
    NodoServicio* inicioServicios;
    Servicio* buscarServicio(std::string nombreBuscado);
    void agregarServicio(std::string nombre);
    void limpiarCampo(std::string &campo);
    bool convertirEntero(std::string texto, int &resultado);
    bool convertirDecimal(std::string texto, double &resultado);
    bool convertirBinario(std::string texto, bool &resultado);
    bool tipoDolorVariado(std::string tipo);

public:
    Hospital();
    ~Hospital();
    void lecturaPacientes();
    void mostrarPacientes();
    void atenderPacientes(int cantidad);
    void verDepartamento();
    void mostrarHistorial();
    Paciente* buscarPaciente(std:: string id);
    void preguntarId();

};

#endif
