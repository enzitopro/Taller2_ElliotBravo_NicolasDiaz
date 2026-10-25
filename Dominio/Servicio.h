#ifndef SERVICIO_H
#define SERVICIO_H
#include <string>
#include "../Logica/AVL.h"

class Servicio {
private:
    std::string nombre;


    AVL pacientes;
public:
    Servicio(std::string nombre);

    std::string getNombre() const;

    bool recibirPaciente(Paciente* p);

    void mostrarEstado() ;
    void mostrarRecorridos();

    Paciente* buscarPaciente(std:: string id);
    Paciente* buscarPorId(std:: string id,std:: string &ruta);
    Paciente* buscarPorNombre(std::string nombre);

    bool eliminarPaciente(std:: string id);
};

#endif