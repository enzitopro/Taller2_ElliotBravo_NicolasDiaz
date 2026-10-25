#include "Hospital.h"
#include <iostream>
#include <fstream> // libreria para leer
#include <sstream>// libreria para separar
#include <string>

#include "Paciente.h"
#include "Servicio.h"
#include "../Logica/ColaPacientes.h"
using namespace std;

void Hospital::limpiarCampo(std::string &campo) {
    if (campo.empty()) return;
    char* inicio = &campo[0];
    char* fin = inicio + campo.size() - 1;

    while (fin >= inicio && (*fin == '\r' || *fin == '\n' || *fin == ' ')) {
        fin--;
    }

    long nuevaLongitud = (fin - inicio) + 1;
    campo.resize(nuevaLongitud);
}

bool Hospital::convertirEntero(std::string texto, int &resultado) {
    stringstream conversor(texto);
    conversor >> resultado;
    return !conversor.fail() && conversor.eof();
}

bool Hospital::convertirDecimal(std::string texto, double &resultado) {
    stringstream conversor(texto);
    conversor >> resultado;
    return !conversor.fail() && conversor.eof();
}

bool Hospital::convertirBinario(std::string texto, bool &resultado) {
    if (texto == "1") {
        resultado = true;
        return true;
    }
    if (texto == "0") {
        resultado = false;
        return true;
    }
    return false;
}

bool Hospital::tipoDolorVariado(std::string tipo) {
    return tipo == "pecho" || tipo == "cabeza" || tipo == "abdomen" || tipo == "extremidad" || tipo == "otro";
}


void Hospital::lecturaPacientes() {
    ifstream archivo("Dominio/pacientes.txt");
    if (!archivo.is_open()) {
        archivo.open("../Dominio/pacientes.txt");
    }
    if (!archivo.is_open()) {
        cout << "ERROR: No se encontró el archivo pacientes.txt" << endl;
        return;
    }

    string linea;
    int numeroLinea = 0;
    while (getline(archivo, linea)) {
        numeroLinea++;
        limpiarCampo(linea);
        if (linea.empty()) {
            continue;
        }
        const int CANTIDAD_CAMPOS = 11;
        string campos[CANTIDAD_CAMPOS];
        stringstream streamLinea(linea);
        int camposLeidos = 0;
        string campo;
        while (getline(streamLinea, campo, ';')) {
            if (camposLeidos < CANTIDAD_CAMPOS) {
                limpiarCampo(campo);
                campos[camposLeidos] = campo;
            }
            camposLeidos++;
        }

        if (camposLeidos != CANTIDAD_CAMPOS) {
                cout << "Linea " << numeroLinea << " invalida (se esperaban 11 campos y hay " << camposLeidos << "), se omite: " << linea << endl;
                continue;
        }

        bool hayCampoVacio = false;
        for (int i = 0; i < CANTIDAD_CAMPOS; i++) {
            if (campos[i].empty()) {
                hayCampoVacio = true;
            }
        }
        if (hayCampoVacio) {
            cout << "Linea " << numeroLinea << " invalida (campo vacio), se omite: " << linea << endl;
            continue;
        }

        string id = campos[0];
        string nombre = campos[1];
        int edad;
        double temperatura;
        int presionArterial;
        int dolor;
        string tipoDolor = campos[6];
        bool trauma;
        bool sintomasNeurologicos;
        bool requiereCirugia;
        int diasHospitalizacion;

        if (!convertirEntero(campos[2], edad) || edad < 0 || edad > 120) {
            cout << "Linea " << numeroLinea << " invalida (edad fuera de rango 0-120), se omite: " << linea << endl;
            continue;
        }
        if (!convertirDecimal(campos[3], temperatura) || temperatura < 30 || temperatura > 45.0) {
            cout << "Linea " << numeroLinea << " invalida (temperatura fuera de rango 30-45), se omite: " << linea << endl;
            continue;
        }
        if (!convertirEntero(campos[4], presionArterial) || presionArterial < 50 || presionArterial > 250) {
            cout << "Linea " << numeroLinea << " invalida (presion arterial fuera de rango 50-250), se omite: " << linea << endl;
            continue;
        }
        if (!convertirEntero(campos[5], dolor) || dolor < 0 || dolor > 10) {
            cout << "Linea " << numeroLinea << " invalida (dolor fuera de rango 0-10), se omite: " << linea << endl;
            continue;
        }
        if (!tipoDolorVariado(tipoDolor)) {
            cout << "Linea " << numeroLinea << " invalida (tipo de dolor '" << tipoDolor << "' no existe), se omite: " << linea << endl;
            continue;
        }
        if (!convertirBinario(campos[7], trauma) || !convertirBinario(campos[8], sintomasNeurologicos) || !convertirBinario(campos[9], requiereCirugia)) {
            cout << "Linea " << numeroLinea << " invalida (Trauma, Sintomas Neurologicos o Requiere Cirugia deben ser 1 o 0), se omite: " << linea << endl;
            continue;
        }
        if (!convertirEntero(campos[10], diasHospitalizacion) || diasHospitalizacion < 0) {
            cout << "Linea " << numeroLinea << " invalida (dias de hospitalizacion negativos o no numericos, se omite: " << linea << endl;
            continue;
        }
        if (buscarPaciente(id) != nullptr) {
            cout << "ID existente " << id << ". Paciente no registrado: " << nombre << endl;
            continue;
        }

        Paciente* nuevoPaciente = new Paciente(id, nombre, edad, temperatura, presionArterial, dolor, tipoDolor, trauma, sintomasNeurologicos, requiereCirugia, diasHospitalizacion);
        colaPacientes.push(nuevoPaciente);
    }
    archivo.close();
}

void Hospital::mostrarPacientes() {
    colaPacientes.mostrarPacientes();
}

void Hospital::atenderPacientes(int cantidad) {
    if (cantidad <= 0) {
        cout << "No hay pacientes" << endl;
        return;
    }
    cout << "=== ATENDIENDO PACIENTES ===" << endl;
    for (int i = 0; i < cantidad; i++) {

        Paciente * pacienteObjetivo = colaPacientes.front();

        if (pacienteObjetivo == nullptr) {

            cout << "No quedan pacientes por atender" << endl;
            break;
        }
        colaPacientes.pop();
        pacienteObjetivo->imprimirInfo();

        string servicioObjetivo= arbolDecision.clasificar(pacienteObjetivo);
        Servicio* servicioADerivar=buscarServicio(servicioObjetivo);
        if (servicioADerivar == nullptr) {
            cout << "No se encontro el servicio" << endl;

            delete pacienteObjetivo;
            continue;
        }
        cout << "Servicio: " << servicioADerivar->getNombre() << endl;
        bool agregado= servicioADerivar->recibirPaciente(pacienteObjetivo);

        if (agregado) {
            cout << "Paciente insertado en AVL de "<< servicioADerivar->getNombre() << endl;

        }else {
            cout << "No se pudo insertar, paciente:" << pacienteObjetivo->getId() << endl;
            delete pacienteObjetivo;
        }

    }
}

Servicio* Hospital::buscarServicio(string nombreBuscado) {
    NodoServicio* cursor = inicioServicios;
    while (cursor != nullptr) {
        if (cursor->servicio->getNombre() == nombreBuscado) {
            return cursor->servicio;
        } else {
            cursor = cursor->siguiente;
        }
    }
    return nullptr;
}

void Hospital::agregarServicio(std::string nombre) {
    Servicio* nuevoServicio = new Servicio(nombre);
    NodoServicio* servicio = new NodoServicio(nuevoServicio);
    servicio->siguiente = inicioServicios;
    inicioServicios = servicio;
}

void Hospital::verDepartamento() {
    cout << "=== DEPARTAMENTOS/SERVICIOS ===" << endl;
    string nombresOpciones[] = {
        "Urgencias", "Medicina General", "Cardiologia", "Neurologia",
        "Traumatologia", "Cirugia", "Pediatria", "Hospitalizacion"
    };
    int opcion;
    cout << "1. Urgencias" << endl
        << "2. Medicina General" << endl
        << "3. Cardiologia" << endl
        << "4. Neurologia" << endl
        << "5. Traumatologia" << endl
        << "6. Cirugia" << endl
        << "7. Pediatria" << endl
        << "8. Hospitalizacion" << endl
        << "Seleccionar opcion: ";
    cin >> opcion;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opcion invalida" << endl;
        return;
    }
    if (1 <= opcion && opcion <= 8) {
        Servicio* s = buscarServicio(nombresOpciones[opcion-1]);
        if (s != nullptr) {
            s->mostrarEstado();
            s->mostrarRecorridos();
    } else {
        cout << "Opcion inválida" << endl;
        }
    }
}

Hospital::Hospital() {
    inicioServicios = nullptr;
    string nombres[] = {
        "Urgencias", "Cardiologia", "Cirugia", "Pediatria", "Traumatologia", "Neurologia", "Medicina General", "Hospitalizacion"
    };
    for (int i = 0; i < 8; i++) {
        agregarServicio(nombres[i]);
    }
}

Hospital::~Hospital() {
    NodoServicio* cursor = inicioServicios;
    NodoServicio* aux = nullptr;
    while (cursor != nullptr) {
        aux = cursor;
        cursor = cursor->siguiente;
        delete aux->servicio; delete aux;
    }
}


Paciente* Hospital::buscarPaciente(string id) {
    Paciente* pacienteObjetivo = colaPacientes.buscarPaciente(id);
    if (pacienteObjetivo != nullptr) {
        return pacienteObjetivo;
    }
    NodoServicio* nodo = inicioServicios;

    while (nodo != nullptr) {
        pacienteObjetivo= nodo->servicio->buscarPaciente(id);
        if (pacienteObjetivo != nullptr) {
            return pacienteObjetivo;
        }

        nodo = nodo->siguiente;
    }
    return nullptr;
}

void Hospital::preguntarPaciente() {
    string objetivo;
    cout << "Ingrese ID o nombre a buscar: ";

    cin.ignore();
    getline(cin,objetivo);

    NodoServicio* actual = inicioServicios;
    while (actual != nullptr) {
        string ruta;

        Paciente* buscado =actual->servicio->buscarPorId(objetivo,ruta);
        bool buscadoporID= false;
        if (buscado != nullptr) {
            buscadoporID= true;
        }

        if (buscado == nullptr) {
            buscado=actual->servicio->buscarPorNombre(objetivo);
        }

        if (buscado != nullptr) {
            cout << "Paciente objetivo:"<< endl;
            buscado->imprimirInfo();

            if (buscadoporID) {
                cout << "Ruta de busqueda: " << ruta << endl;
            }
            return;
        }
        actual= actual->siguiente;
    }
        cout << "Paciente no encontrado" << endl;

}

void Hospital::mostrarArbolDecision() {
    arbolDecision.MostrarPreorden();
    arbolDecision.MostrarInorden();
    arbolDecision.MostrarPostorden();
}

void Hospital::eliminarPaciente() {
    string id;
    cout << "Ingrese ID de paciente a eliminar: ";
    cin >> id;

    NodoServicio* nodo = inicioServicios;
    while (nodo != nullptr) {
        if (nodo->servicio->eliminarPaciente(id)) {
            cout<< "Paciente " << id << ", eliminado correctamente "<< endl;
            return;
        }
        nodo=nodo->siguiente;
    }
    cout << "Paciente no existe "<< endl;
}





