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

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    string nombreArchivo = argv[1];

    srand(static_cast<unsigned>(time(nullptr)));

    ofstream archivoSalida(nombreArchivo + "_tiempos.txt");

    archivoSalida << "# Ejecución" << "\t\t\t  Insertion Sort" << "\t\t\t  Selection Sort" << "\t\t\t\t Bubble Sort" << "\t\t\t\t  Merge Sort" << "\t\t\t\t   Quicksort" << endl;


    for (int i = 1; i <= m; i++) {
        duration<double> tiempo;
        int *A = new int[n];

        generarArregloAleatorio(A, n);

        archivoSalida << setw(10) << i;

        for (char algoritmo : {'i', 's', 'b', 'm', 'q'}) {
            
            tiempo = ejecutarAlgoritmo(A, n, algoritmo);

            archivoSalida << "\t\t\t" << setw(15) << tiempo.count() << "s";

        }

        archivoSalida << endl;
        delete[] A;
    }

    archivoSalida.close();

    return EXIT_SUCCESS;
}