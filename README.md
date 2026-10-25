# Taller 2 - Estructura de Datos: Clasificación y AVL

## Integrantes
| Nombre | RUT | GitHub | Carrera | Paralelo |
|---|---|---|---|---|
| Elliot Bravo | 218110037 | enzitopro | ICCI | Paralelo C1 |
| Nicolás Díaz | 216340612 | nDiaz231 | ICCI | Paralelo C2 |

## Descripción
Extensión del sistema del Hospital Marmaja del Taller 1. Los pacientes se leen desde `Dominio/pacientes.txt`, entran a una **Cola** (FIFO) y, al ser atendidos, un **árbol de decisión** determina su servicio. Luego se guardan en el **AVL** de ese servicio, ordenado por ID.

```
Archivo -> Cola -> Árbol de decisión -> Servicio -> AVL
```

Todas las estructuras (Cola, Árbol de decisión y AVL) están implementadas manualmente con nodos y punteros, sin STL.

## Requisitos
- g++ con soporte C++20
- CMake 3.16 o superior (viene instalado en GitHub Codespaces)

## Compilación y ejecución

### Opción 1: CMake (Codespaces o terminal)
Desde la raíz del repositorio:
```bash
cmake -S . -B build
cmake --build build
./build/Taller2_ElliotBravo_NicolasDiaz
```
El programa busca el archivo en `Dominio/pacientes.txt` y en `../Dominio/pacientes.txt`, así que funciona tanto si se ejecuta desde la raíz como desde dentro de `build/`.

### Opción 2: g++ directo
Desde la raíz del repositorio:
```bash
g++ -std=c++20 -Wall -Wextra App/main.cpp Dominio/*.cpp Logica/*.cpp -o hospital
./hospital
```

### Opción 3: CLion
Abrir la carpeta del proyecto y ejecutar el target `Taller2_ElliotBravo_NicolasDiaz`.

## Uso (menú)
| Opción | Qué hace |
|---|---|
| 1. Atender pacientes | Saca pacientes de la cola en orden FIFO, los evalúa con el árbol de decisión (muestra la ruta), y los inserta en el AVL del servicio asignado |
| 2. Ver departamentos | Muestra los 8 servicios con sus pacientes (en orden de ID) o "Sin pacientes" |
| 3. Buscar paciente | Busca por ID (muestra la ruta de IDs recorridos en el AVL). Si no encuentra ese ID, busca por nombre |
| 4. Recorridos, altura y FB de un AVL | Muestra inorden, preorden, postorden, altura del árbol y el factor de balance de cada nodo de un servicio |
| 5. Eliminar paciente por ID | Elimina el paciente del AVL donde esté y rebalancea |
| 6. Recorridos del árbol de decisión | Muestra el árbol de decisión en preorden, inorden y postorden |
| 7. Salir | Termina el programa y libera la memoria |

## Formato del archivo de pacientes
Cada línea de `Dominio/pacientes.txt`:
```
ID;Nombre;Edad;Temperatura;PresionArterial;Dolor;TipoDolor;Trauma;SintomasNeurologicos;RequiereCirugia;DiasHospitalizacion
```
Ejemplo: `001;Juan Perez;25;37.0;120;3;otro;0;0;0;0`

### Validaciones (datos inválidos)
Una línea inválida se informa por pantalla con su número de línea y **se omite** (el paciente no entra a la cola):

| Campo | Regla |
|---|---|
| Cantidad de campos | Deben ser exactamente 11 y ninguno vacío |
| Edad | Entero entre 0 y 120 |
| Temperatura | Decimal entre 30 y 45 |
| PresionArterial | Entero entre 50 y 250 (presión sistólica en mmHg) |
| Dolor | Entero entre 0 y 10 |
| TipoDolor | `pecho`, `cabeza`, `abdomen`, `extremidad` u `otro` |
| Trauma, SintomasNeurologicos, RequiereCirugia | Solo `0` o `1` |
| DiasHospitalizacion | Entero mayor o igual a 0 |
| ID | No puede repetirse. Un ID duplicado se informa y no se registra |

Si el archivo no existe, se muestra un mensaje de error y el programa sigue con la cola vacía.

## Árbol de decisión

### Criterio
Cada nodo interno es una pregunta de SI/NO (rama izquierda = SI, rama derecha = NO) y cada hoja es un servicio. Se usan los 9 atributos clínicos del paciente.

```
¿Temperatura >= 40 o Dolor >= 9?
|-- Si: Urgencias
|-- No:
    ¿Edad < 14?
    |-- Si: Pediatria
    |-- No:
        ¿Trauma == 1?
        |-- Si:
        |   ¿RequiereCirugia == 1?
        |   |-- Si: Cirugia
        |   |-- No: Traumatologia
        |-- No:
            ¿RequiereCirugia == 1?
            |-- Si: Cirugia
            |-- No:
                ¿SintomasNeurologicos == 1 o TipoDolor == cabeza?
                |-- Si: Neurologia
                |-- No:
                    ¿TipoDolor == pecho o PresionArterial >= 160?
                    |-- Si: Cardiologia
                    |-- No:
                        ¿Temperatura >= 38.5 o Dolor >= 7?
                        |-- Si: Urgencias
                        |-- No:
                            ¿DiasHospitalizacion >= 2?
                            |-- Si: Hospitalizacion
                            |-- No: Medicina General
```

### Justificación de cada decisión
| Pregunta | Por qué está ahí |
|---|---|
| Temperatura >= 40 o Dolor >= 9 | Es un paciente crítico (hiperpirexia o dolor extremo). Va primero porque la gravedad manda sobre todo lo demás: incluso un niño en ese estado va a Urgencias |
| Edad < 14 | Los menores se atienden en Pediatría, que cubre todas sus especialidades |
| Trauma y RequiereCirugia | Un trauma que necesita operación va a Cirugía, y si no la necesita va a Traumatología |
| RequiereCirugia (sin trauma) | Pacientes que necesitan operación por otra causa (por ejemplo abdominal) |
| SintomasNeurologicos o dolor de cabeza | Indicadores de un problema neurológico |
| Dolor de pecho o PresionArterial >= 160 | Dolor torácico o hipertensión severa son señales cardiovasculares |
| Temperatura >= 38.5 o Dolor >= 7 | Paciente moderado: fiebre alta o dolor fuerte sin causa específica, necesita atención rápida |
| DiasHospitalizacion >= 2 | Si se estima una estadía de 2 o más días, necesita cama en Hospitalización |
| Ninguna de las anteriores | Medicina General (consulta común) |

### Empates y casos especiales
- **Paciente que cumple varias condiciones:** gana la primera pregunta del árbol que responde SI, por eso las preguntas están ordenadas de más grave a menos grave. Por ejemplo, un paciente con dolor de pecho y fiebre de 40° va a Urgencias.
- **Paciente inválido o sin servicio:** las líneas inválidas se descartan al leer el archivo. Si igual llega un paciente nulo al árbol, se informa y no se clasifica.
- Hay rutas válidas hacia los 8 servicios. Urgencias y Cirugía tienen dos hojas cada uno (crítico/moderado y con/sin trauma).

## Árboles AVL
- Hay un AVL por cada uno de los 8 servicios, y la clave de ordenamiento es el **ID** del paciente. Los ID se comparan como texto, por eso todos deben tener el mismo largo (por ejemplo `001`, `012`).
- Convención del curso: **FB = altura(derecha) − altura(izquierda)**, con hoja = altura 1 y `nullptr` = 0.
- Rotaciones (se informa por pantalla cuál se aplica):

| Caso | FB del nodo | FB del hijo | Rotación |
|---|---|---|---|
| LL | −2 | ≤ 0 (izquierdo) | Simple a la derecha |
| RR | +2 | ≥ 0 (derecho) | Simple a la izquierda |
| LR | −2 | +1 (izquierdo) | Izquierda en el hijo y luego derecha en el nodo |
| RL | +2 | −1 (derecho) | Derecha en el hijo y luego izquierda en el nodo |

- **Insertar:** como en un ABB y luego se rebalancea al volver de la recursión. Un ID repetido no se inserta.
- **Buscar por ID:** O(log n), muestra la ruta de IDs visitados. **Buscar por nombre:** recorre todo el AVL (O(n)), porque el árbol está ordenado por ID y no por nombre.
- **Eliminar por ID:** si el nodo tiene 0 o 1 hijo, se reemplaza por su hijo. Si tiene 2 hijos, se usa el sucesor (el menor del subárbol derecho). Después se rebalancea hacia arriba.
- El archivo de ejemplo incluye los pacientes 018, 020 y 019 al final para que el AVL de Medicina General muestre una rotación simple izquierda (RR) y una doble derecha-izquierda (RL).

## Estructuras implementadas
| Estructura | Archivos | Uso |
|---|---|---|
| Cola (FIFO) | `Logica/ColaPacientes`, `Logica/NodoPaciente.h` | Pacientes en espera según orden de llegada |
| Árbol de decisión | `Logica/Arbol`, `Logica/NodoDecision` | Clasifica al paciente en un servicio |
| AVL | `Logica/AVL`, `Logica/NodoAVL.h` | Pacientes atendidos de cada servicio |
| Lista enlazada de servicios | `Logica/NodoServicio.h`, `Dominio/Servicio` | Los 8 servicios del hospital |

## Jerarquía de clases
`Persona` (clase base: nombre, edad) → `Paciente` (clase derivada: id, datos clínicos y servicio asignado).

## Memoria
- La cola libera a los pacientes que no alcanzaron a ser atendidos.
- Cada AVL es dueño de sus pacientes y los libera en su destructor, en postorden.
- El árbol de decisión libera sus nodos en postorden.
- Revisado con `valgrind --leak-check=full`: "All heap blocks were freed -- no leaks are possible".
