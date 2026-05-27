import java.util.Locale;
import java.util.Scanner;

/**
 * Sistema de Gestión y Análisis de Calificaciones.
 *
 * Utiliza dos arreglos paralelos (nombres y notas) para registrar a los
 * estudiantes de un curso. Permite generar un reporte estadístico
 * (promedio, aprobados y reprobados) y realizar una búsqueda secuencial
 * por nombre.
 *
 * Asignatura: Algoritmos y Lógica de Programación - UTA, Primero "B".
 */
public class GestionCalificaciones {

    private static final int MAX_ESTUDIANTES = 100;
    private static final double NOTA_APROBACION = 7.0;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String[] nombres = new String[MAX_ESTUDIANTES];
        double[] notas = new double[MAX_ESTUDIANTES];
        int cantidad = 0;
        int opcion;

        do {
            mostrarMenu();
            opcion = leerEntero(sc);

            switch (opcion) {
                case 1:
                    cantidad = registrarCalificaciones(sc, nombres, notas);
                    break;
                case 2:
                    mostrarReporte(nombres, notas, cantidad);
                    break;
                case 3:
                    buscarEstudiante(sc, nombres, notas, cantidad);
                    break;
                case 4:
                    System.out.println("\nSaliendo del sistema. ¡Hasta pronto!");
                    break;
                default:
                    System.out.println("Opción inválida. Intente nuevamente.");
            }
        } while (opcion != 4);

        sc.close();
    }

    private static void mostrarMenu() {
        System.out.println("\n========================================");
        System.out.println("  SISTEMA DE GESTIÓN DE CALIFICACIONES");
        System.out.println("========================================");
        System.out.println("1. Registrar Calificaciones");
        System.out.println("2. Mostrar Reporte Estadístico");
        System.out.println("3. Buscar Estudiante");
        System.out.println("4. Salir");
        System.out.print("Opción: ");
    }

    private static int registrarCalificaciones(Scanner sc, String[] nombres, double[] notas) {
        System.out.print("\nCantidad de estudiantes a registrar: ");
        int cantidad = leerEntero(sc);

        if (cantidad <= 0 || cantidad > MAX_ESTUDIANTES) {
            System.out.println("La cantidad debe estar entre 1 y " + MAX_ESTUDIANTES + ".");
            return 0;
        }

        for (int i = 0; i < cantidad; i++) {
            System.out.print("Nombre del estudiante " + (i + 1) + ": ");
            nombres[i] = sc.nextLine().trim();

            notas[i] = leerNotaValida(sc, "Nota de " + nombres[i] + " (0 a 10): ");
        }

        System.out.println("Registro completado: " + cantidad + " estudiantes.");
        return cantidad;
    }

    private static void mostrarReporte(String[] nombres, double[] notas, int cantidad) {
        if (cantidad == 0) {
            System.out.println("\nNo hay estudiantes registrados. Use la opción 1 primero.");
            return;
        }

        double suma = 0.0;
        int aprobados = 0;
        int reprobados = 0;

        for (int i = 0; i < cantidad; i++) {
            suma += notas[i];
            if (notas[i] >= NOTA_APROBACION) {
                aprobados++;
            } else {
                reprobados++;
            }
        }

        double promedio = suma / cantidad;

        System.out.println("\n---------- REPORTE ESTADÍSTICO ----------");
        System.out.printf(Locale.US, "Promedio general:  %.2f%n", promedio);
        System.out.println("Total aprobados:   " + aprobados);
        System.out.println("Total reprobados:  " + reprobados);
        System.out.println("Total estudiantes: " + cantidad);
        System.out.println("-----------------------------------------");
    }

    private static void buscarEstudiante(Scanner sc, String[] nombres, double[] notas, int cantidad) {
        if (cantidad == 0) {
            System.out.println("\nNo hay estudiantes registrados. Use la opción 1 primero.");
            return;
        }

        System.out.print("\nNombre del estudiante a buscar: ");
        String objetivo = sc.nextLine().trim();

        boolean encontrado = false;
        for (int i = 0; i < cantidad; i++) {
            if (nombres[i].equalsIgnoreCase(objetivo)) {
                String estado = notas[i] >= NOTA_APROBACION ? "Aprobado" : "Reprobado";
                System.out.println("\nEstudiante: " + nombres[i]);
                System.out.println("Nota:       " + notas[i]);
                System.out.println("Estado:     " + estado);
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            System.out.println("El estudiante \"" + objetivo + "\" no se encuentra registrado.");
        }
    }

    private static int leerEntero(Scanner sc) {
        while (true) {
            String linea = sc.nextLine().trim();
            try {
                return Integer.parseInt(linea);
            } catch (NumberFormatException e) {
                System.out.print("Entrada inválida. Ingrese un número entero: ");
            }
        }
    }

    private static double leerNotaValida(Scanner sc, String mensaje) {
        while (true) {
            System.out.print(mensaje);
            String linea = sc.nextLine().trim().replace(',', '.');
            try {
                double nota = Double.parseDouble(linea);
                if (nota >= 0 && nota <= 10) {
                    return nota;
                }
            } catch (NumberFormatException e) {
                // cae al mensaje de error
            }
            System.out.println("Nota inválida. Debe ser un número entre 0 y 10.");
        }
    }
}
