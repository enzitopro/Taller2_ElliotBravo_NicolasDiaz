cmake_minimum_required(VERSION 3.16)
project(Taller2_ElliotBravo_NicolasDiaz)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller2_ElliotBravo_NicolasDiaz App/main.cpp
        Dominio/Persona.h
        Dominio/Persona.cpp
        Dominio/Paciente.cpp
        Dominio/Paciente.h
        Logica/NodoPaciente.h
        Logica/NodoServicio.h
        Dominio/Servicio.h
        Dominio/Servicio.cpp
        Logica/ListaPacientes.h
        Logica/ListaPacientes.cpp
        Dominio/Hospital.h
        Dominio/Hospital.cpp
        Logica/ColaPacientes.h
        Logica/ColaPacientes.cpp
        Logica/StackHistorial.h
        Logica/StackHistorial.cpp
        Logica/Arbol.h
        Logica/NodoDecision.cpp
        Logica/Arbol.cpp
        Logica/NodoAVL.h
        Logica/AVL.h
)
