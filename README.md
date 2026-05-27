# T2.7 — Sistema de Gestión y Análisis de Calificaciones

Práctica de laboratorio para la asignatura **Algoritmos y Lógica de Programación** (Universidad Técnica de Ambato — FISEI, Primero "B").

El programa procesa las calificaciones del examen final de un grupo de estudiantes usando **arreglos paralelos** y **búsqueda secuencial**. Está implementado tanto en **Java** como en **C++**.

---

## Requerimientos del programa

1. **Registrar Calificaciones** — Permite ingresar el nombre y la nota de cada estudiante.
2. **Mostrar Reporte Estadístico**
   - Promedio general del grupo.
   - Total de alumnos **aprobados** (nota ≥ 7).
   - Total de alumnos **reprobados** (nota < 7).
3. **Buscar Estudiante (Búsqueda Secuencial)**
   - Si se encuentra: muestra nombre, nota y estado (Aprobado / Reprobado).
   - Si no se encuentra: muestra `El estudiante [Nombre] no se encuentra registrado.`
4. **Salir** — Termina el programa.

---

## Estructura del proyecto

```
T2.7-Sistema-Calificaciones/
├── Java/
│   └── GestionCalificaciones.java
├── Cpp/
│   └── main.cpp
├── capturas/
│   ├── 01-menu-y-validacion.png   ← bucle do-while ante opción inválida
│   ├── 02-registro.png            ← registro de 3 estudiantes
│   ├── 03-reporte.png             ← reporte estadístico
│   ├── 04-busqueda.png            ← búsqueda secuencial (encontrado y no encontrado)
│   ├── textos/                    ← transcripciones UTF-8 fuente
│   └── generar-capturas.ps1       ← regenera las PNG si cambia el programa
└── README.md
```

Para regenerar las capturas tras cualquier cambio en el código:

```powershell
powershell -ExecutionPolicy Bypass -File capturas\generar-capturas.ps1
```

---

## Cómo compilar y ejecutar

### Java

Requisitos: JDK 8 o superior.

```bash
cd Java
javac GestionCalificaciones.java
java GestionCalificaciones
```

### C++

Requisitos: compilador con soporte C++11 (g++, clang, MSVC).

```bash
cd Cpp
g++ -std=c++11 main.cpp -o calificaciones
./calificaciones        # Linux / macOS
calificaciones.exe      # Windows
```

---

## Análisis del problema

Se construye un menú interactivo controlado por un ciclo `do-while` que permite navegar entre las opciones. Se utilizan dos arreglos paralelos:

- `nombres[]` — arreglo de cadenas (`String` / `std::string`).
- `notas[]`  — arreglo de reales (`double`).

En la opción de reporte se recorren las notas con un bucle `for`, sumando valores y evaluando con `if-else` si la nota es ≥ 7. Para la búsqueda se compara el nombre ingresado con los elementos del arreglo de nombres, usando una variable booleana (bandera) para confirmar si se encontró o si se imprime el mensaje de error.

### Variables principales

| Tipo       | Nombre                | Rol                                      |
|------------|-----------------------|------------------------------------------|
| Entero     | `opcion`              | Selección del menú                       |
| Entero     | `cantidad`            | Estudiantes registrados                  |
| Arreglo    | `nombres[]`           | Nombres de los estudiantes               |
| Arreglo    | `notas[]`             | Notas de los estudiantes                 |
| Real       | `suma`, `promedio`    | Cálculo del promedio general             |
| Entero     | `aprobados`, `reprobados` | Contadores de estado                 |
| Lógico     | `encontrado`          | Bandera de la búsqueda secuencial        |

---

## Casos de prueba de escritorio

| # | Caso                | Entrada                                       | Resultado esperado                                                  |
|---|---------------------|-----------------------------------------------|---------------------------------------------------------------------|
| 1 | Registrar datos     | Opción 1, cantidad = 2, `Jose` (9.5), `Maria` (6) | Confirmación de registro de 2 estudiantes.                       |
| 2 | Reporte estadístico | Opción 2 (con los datos del caso 1)           | Promedio: **7.75**, Aprobados: **1**, Reprobados: **1**.            |
| 3 | Búsqueda no encontrada | Opción 3, buscar `Pedro`                   | `El estudiante "Pedro" no se encuentra registrado.`                 |

---

## Mejoras incluidas respecto al pseudocódigo base

- **Validación de notas** entre 0 y 10 al ingresar cada calificación.
- **Validación de enteros** al leer el menú (reintenta si el usuario teclea texto).
- **Comparación de nombres insensible a mayúsculas** (`equalsIgnoreCase` en Java, conversión a minúsculas en C++).
- **Aceptación de coma o punto** como separador decimal en las notas.
- **Mensaje claro** cuando se solicita reporte o búsqueda sin haber registrado estudiantes.

---

## Información académica

- **Asignatura:** Algoritmos y Lógica de Programación
- **Tema:** T2.7 — Arreglos (ejercicios)
- **Nivel:** Primero, paralelo "B"
- **Universidad:** Técnica de Ambato — FISEI
- **Docente:** Ing. José Caiza
- **Estudiante:** Imanol Miranda
