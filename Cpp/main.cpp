// Sistema de Gestión y Análisis de Calificaciones
//
// Utiliza dos arreglos paralelos (nombres y notas) para registrar a los
// estudiantes de un curso. Permite generar un reporte estadístico
// (promedio, aprobados y reprobados) y realizar una búsqueda secuencial
// por nombre.
//
// Asignatura: Algoritmos y Lógica de Programación - UTA, Primero "B".

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

const int MAX_ESTUDIANTES = 100;
const double NOTA_APROBACION = 7.0;

void mostrarMenu();
int  leerEntero();
double leerNotaValida(const string& mensaje);
string aMinusculas(string texto);

int  registrarCalificaciones(string nombres[], double notas[]);
void mostrarReporte(const string nombres[], const double notas[], int cantidad);
void buscarEstudiante(const string nombres[], const double notas[], int cantidad);

int main() {
    string nombres[MAX_ESTUDIANTES];
    double notas[MAX_ESTUDIANTES];
    int cantidad = 0;
    int opcion = 0;

    do {
        mostrarMenu();
        opcion = leerEntero();

        switch (opcion) {
            case 1:
                cantidad = registrarCalificaciones(nombres, notas);
                break;
            case 2:
                mostrarReporte(nombres, notas, cantidad);
                break;
            case 3:
                buscarEstudiante(nombres, notas, cantidad);
                break;
            case 4:
                cout << "\nSaliendo del sistema. Hasta pronto!\n";
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);

    return 0;
}

void mostrarMenu() {
    cout << "\n========================================\n";
    cout << "  SISTEMA DE GESTION DE CALIFICACIONES\n";
    cout << "========================================\n";
    cout << "1. Registrar Calificaciones\n";
    cout << "2. Mostrar Reporte Estadistico\n";
    cout << "3. Buscar Estudiante\n";
    cout << "4. Salir\n";
    cout << "Opcion: ";
}

int registrarCalificaciones(string nombres[], double notas[]) {
    cout << "\nCantidad de estudiantes a registrar: ";
    int cantidad = leerEntero();

    if (cantidad <= 0 || cantidad > MAX_ESTUDIANTES) {
        cout << "La cantidad debe estar entre 1 y " << MAX_ESTUDIANTES << ".\n";
        return 0;
    }

    for (int i = 0; i < cantidad; i++) {
        cout << "Nombre del estudiante " << (i + 1) << ": ";
        getline(cin, nombres[i]);
        notas[i] = leerNotaValida("Nota de " + nombres[i] + " (0 a 10): ");
    }

    cout << "Registro completado: " << cantidad << " estudiantes.\n";
    return cantidad;
}

void mostrarReporte(const string nombres[], const double notas[], int cantidad) {
    (void)nombres; // los nombres no se imprimen en este reporte
    if (cantidad == 0) {
        cout << "\nNo hay estudiantes registrados. Use la opcion 1 primero.\n";
        return;
    }

    double suma = 0.0;
    int aprobados = 0;
    int reprobados = 0;

    for (int i = 0; i < cantidad; i++) {
        suma += notas[i];
        if (notas[i] >= NOTA_APROBACION) aprobados++;
        else                              reprobados++;
    }

    double promedio = suma / cantidad;

    cout << "\n---------- REPORTE ESTADISTICO ----------\n";
    cout << "Promedio general:  " << fixed << setprecision(2) << promedio << "\n";
    cout << "Total aprobados:   " << aprobados << "\n";
    cout << "Total reprobados:  " << reprobados << "\n";
    cout << "Total estudiantes: " << cantidad << "\n";
    cout << "-----------------------------------------\n";
}

void buscarEstudiante(const string nombres[], const double notas[], int cantidad) {
    if (cantidad == 0) {
        cout << "\nNo hay estudiantes registrados. Use la opcion 1 primero.\n";
        return;
    }

    cout << "\nNombre del estudiante a buscar: ";
    string objetivo;
    getline(cin, objetivo);
    string objetivoBajo = aMinusculas(objetivo);

    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        if (aMinusculas(nombres[i]) == objetivoBajo) {
            string estado = (notas[i] >= NOTA_APROBACION) ? "Aprobado" : "Reprobado";
            cout << "\nEstudiante: " << nombres[i] << "\n";
            cout << "Nota:       " << defaultfloat << notas[i] << "\n";
            cout << "Estado:     " << estado << "\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "El estudiante \"" << objetivo << "\" no se encuentra registrado.\n";
    }
}

int leerEntero() {
    while (true) {
        string linea;
        if (!getline(cin, linea)) return 4; // EOF: salir limpio
        try {
            size_t pos;
            int valor = stoi(linea, &pos);
            if (pos == linea.size()) return valor;
        } catch (...) { /* cae al mensaje */ }
        cout << "Entrada invalida. Ingrese un numero entero: ";
    }
}

double leerNotaValida(const string& mensaje) {
    while (true) {
        cout << mensaje;
        string linea;
        if (!getline(cin, linea)) return 0.0;
        replace(linea.begin(), linea.end(), ',', '.');
        try {
            size_t pos;
            double nota = stod(linea, &pos);
            if (pos == linea.size() && nota >= 0.0 && nota <= 10.0) return nota;
        } catch (...) { /* cae al mensaje */ }
        cout << "Nota invalida. Debe ser un numero entre 0 y 10.\n";
    }
}

string aMinusculas(string texto) {
    transform(texto.begin(), texto.end(), texto.begin(),
              [](unsigned char c) { return tolower(c); });
    return texto;
}
