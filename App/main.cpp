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
        cout << "3. Buscar Paciente" << endl;
        cout << "4. Eliminar Paciente" << endl;
        cout << "5. Mostrar recorrido de arbol" << endl;
        cout << "6. Salir" << endl;
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
                cout <<"=== Paciente a buscar ===" << endl;
                hospital.preguntarPaciente();
                break;
            case 4:
                cout <<"=== Paciente a eliminar===" << endl;

                break;
            case 5:
                cout <<"=== Recorridos ===" << endl;

                break;
            case 6:
                cout << "Hasta luego :D" << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
        }
    } while (opcion != 6);

    return 0;
}