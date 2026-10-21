#ifndef PACIENTE_H
#define PACIENTE_H
#include "Persona.h"
#include <string>

class Paciente : public Persona {
private:
    std::string id;
    double temperatura;
    int presionArterial;
    int dolor;
    std::string tipoDolor;
    bool trauma;
    bool sintomasNeurologicos;
    bool requiereCirugia;
    int diasHospitalizacion;
    std::string servicioDestino;
public:
    Paciente(std::string id, std::string nombre, int edad, double temperatura, int presionArterial, int dolor,
        std::string tipoDolor, bool trauma, bool sintomasNeurologicos, bool requiereCiruga, int diasHospitalizacion);
    std::string getId() const;
    double getTemperatura() const;
    int getPresionArterial() const;
    int getDolor() const;
    std::string getTipoDolor() const;
    bool getTrauma() const;
    bool getSintomasNeurologicos() const;
    bool getRequiereCirugia() const;
    int getDiasHospitalizacion() const;
    std::string getServicioDestino() const;

    void setServicioDestino(std::string servicio);
    void imprimirInfo() const;
};

#endif
