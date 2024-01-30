#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

#include "ordenamiento.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Sintaxis: ordenamiento <tamaño_arreglo> <repeticiones>" << endl;
        return EXIT_FAILURE;
    }

    long long n = atoi(argv[1]);
    long long m = atoi(argv[2]);
    string nombreArchivo = argv[1];

    srand(static_cast<unsigned>(time(nullptr)));

    ofstream archivoSalida(nombreArchivo + "_tiempos.txt");

    archivoSalida << "# Ejecución" << "\t\t\t  Insertion Sort" << "\t\t\t  Selection Sort" << "\t\t\t\t Bubble Sort" << "\t\t\t\t  Merge Sort" << "\t\t\t\t   Quicksort" << endl;


    for (long long i = 1; i <= m; i++) {
        long long *A = new long long[n];
        long long *B = new long long[n];
        generarArregloAleatorio(A, n);

        archivoSalida << setw(10) << i;

        for (char algoritmo : {'i', 's', 'b', 'm', 'q'}) {
            long long *C = copiar_arreglo(A, n);
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            ejecutarAlgoritmo(C, B, n, algoritmo);
            high_resolution_clock::time_point fin = high_resolution_clock::now();
            duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);

            archivoSalida << "\t\t\t" << setw(15) << tiempo.count() << "s";

            delete[] C;
        }

        archivoSalida << endl;
        delete[] A;
        delete[] B;
    }

    archivoSalida.close();

    return EXIT_SUCCESS;
}