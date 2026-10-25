#include <iostream>
#include "../Dominio/Hospital.h"
using namespace std;

int main() {
    Hospital hospital;
    hospital.lecturaPacientes();
    int opcion;
    do {
        cout << "=== HOSPITAL MARMAJA ===" << endl;
        cout << "1. Atender pacientes" << endl;
        cout << "2. Ver departamento" << endl;
        cout << "3. Revisar historial de atencion" << endl;
        cout <<"4. Busqueda por ID" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccionar opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                int cantidad;
                cout << "=== PACIENTES EN ESPERA ===" << endl;
                hospital.mostrarPacientes();
                cout << "Cuantos pacientes desea atender?: "; cin >> cantidad;
                hospital.atenderPacientes(cantidad);
                break;
            case 2:
                hospital.verDepartamento();
                break;
            case 3:
                cout <<"=== HISTORIAL ===" << endl;
                break;
            case 4:
                cout <<"=== ID ===" << endl;
                hospital.preguntarPaciente();
                break;
            case 5:
                cout << "Hasta luego :D" << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
        }
    } while (opcion != 5);

    return 0;
}