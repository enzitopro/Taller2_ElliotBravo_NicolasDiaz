# Taller 1 - Estructura de datos
## Integrantes: 
### Nombre: Elliot Bravo, Rut: 218110037, Nombre en Git: enzitopro, Carrera: ICCI  
### Nombre: Nicolás Díaz, Rut: 216340612, Nombre en Git: nDiaz231, Carrera: ICCI  

## Descripción
Sistema de gestión de pacientes del hospital Marmaja. Implementa manualmente (sin STL) una **Cola** de pacientes en espera, una **Lista enlazada de Servicios** (cada uno con su propia **Lista enlazada de pacientes**) y una **Pila (Stack)** con el historial de atenciones. Los pacientes se cargan desde `Dominio/pacientes.txt`.

## Requisitos
- Compilador con soporte C++20 (g++ o clang++)
- CMake 3.x (opcional, si se compila con CLion)

## Compilación y ejecución

### Opción 1: CMake / CLion (recomendado)
```bash
mkdir -p cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build .
./TALLER2_ElliotBravo_NicolasDiaz
```

### Opción 2: g++ manual
El programa busca `pacientes.txt` en la ruta relativa `../Dominio/pacientes.txt`, por lo que el ejecutable debe correr desde una carpeta un nivel dentro de la raíz del proyecto.

Desde la raíz del proyecto:
```bash
g++ -std=c++20 -Wall -Wextra App/main.cpp Dominio/*.cpp Logica/*.cpp -o hospital
mkdir -p build
mv hospital build/
cd build
./hospital
```

## Formato del archivo de pacientes
Cada línea de `Dominio/pacientes.txt`: ID;Nombre;Edad;Servicio

Servicios válidos: Urgencias, Medicina General, Cardiologia, Neurologia, Traumatologia, Cirugia, Pediatria, Hospitalizacion.

## Estructuras implementadas
- **Cola (Queue):** `ColaPacientes` — pacientes en espera, orden FIFO.
- **Lista enlazada de servicios:** `NodoServicio` — cada nodo referencia un `Servicio`.
- **Lista enlazada de pacientes por servicio:** `ListaPacientes`.
- **Pila (Stack):** `StackHistorial` — historial de atenciones, orden LIFO.

## Jerarquía de clases
`Persona` (clase base) → `Paciente` (clase derivada). `Persona` representa los datos genéricos de cualquier actor del hospital (nombre, edad), reutilizable en futuros talleres para otras entidades; `Paciente` añade los atributos propios del flujo de atención (id, servicio de destino).