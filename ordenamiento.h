#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void intercambiar(long long A[], long long x, long long y) {
    long long aux = A[x];
    A[x] = A[y];
    A[y] = aux;
}

void generarArregloAleatorio(long long A[], long long n) {
    for (long long i = 0; i < n; i++) {
        A[i] = rand() % (10 * n) + 1;
    }
}

void merge(long long A[], long long inicio, long long medio, long long fin) {
    long long *aux = new long long[fin - inicio + 1];
    long long i = inicio;     // índice de la primera mitad
    long long j = medio + 1;  // índice de la segunda mitad
    long long h = 0;

    // Se recorren ambos subarreglos y se van combinando sus
    // elementos ordenadamente hasta que se haya recorrido
    // totalmente uno de ellos
    while ((i <= medio) && (j <= fin)) {
        if (A[i] <= A[j]) {
            aux[h] = A[i];
            i += 1;
        } else {
            aux[h] = A[j];
            j += 1;
        }
        h += 1;
    }

    // Si se copiaron todos los elementos de la primera mitad,
    // se copia el resto de la segunda mitad
    if (i > medio) {
        while (j <= fin) {
            aux[h] = A[j];
            j += 1;
            h += 1;
        }
    } // Si no, se copia el resto de la primera mitad
    else {
        while (i <= medio) {
            aux[h] = A[i];
            i += 1;
            h += 1;
        }
    }
    
    h = 0;
    for (long long k = inicio; k <= fin; k++) {
        A[k] = aux[h];
        h += 1;
    }
    delete [] aux;
}

void merge_sort(long long A[], long long inicio, long long fin) {
    if (inicio < fin) {
        long long medio = (inicio + fin) / 2;
        merge_sort(A, inicio, medio);
        merge_sort(A, medio + 1, fin);
        merge(A, inicio, medio, fin);
    }
}

long long partition(long long A[], long long p, long long r) {
    // A[r] es el registro elegido cuya llave será el pivote
    long long pivote = A[r];
    
    // Indica el índice del último registro cuyo valor
    // es menor a pivote
    long long ultimo = p - 1;

    // Se agrupan los elementos menores a pivote en las primeras
    // posiciones de A
    for (long long i = p; i < r; i++) {
        if (A[i] < pivote) {
            ultimo += 1;
            intercambiar(A, ultimo, i);
        }
    }

    // Y se mueve al pivote a su posición correcta
    intercambiar(A, ultimo + 1, r);
    return ultimo + 1;
}

void quicksort(long long A[], long long p, long long r) {
    if (p < r) {
        long long q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

void insertion_sort(long long A[], long long n) {
    for (long long j = 1; j < n; j++) {
        long long k = A[j];
        long long i = j - 1;
 
        // Se mueven los elementos de A[0..i-1], que son
        // mayores que k, a una posición hacia la derecha
        // de su posicion actual
        while (i >= 0 && A[i] > k) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = k;
    }
}


void selection_sort(long long A[], long long n) {
    for (long long j = 0; j < n-1; j++) {
        long long menor = j;
 
        // Encuentra el elemento minimo del subarreglo
        // que no está ordenado
        for (long long i = j+1; i < n; i++) {
            if (A[i] < A[menor]) {
                menor = i;
            }
        }
        intercambiar (A, j, menor);
    }
}


void bubblesort(long long A[], long long n) {
    for (long long i = 0; i < n-1; i++) {
      
        // Los primeros i elementos ya estan ordenados
        for (long long j = n-1; j > i; j--) {
            if (A[j] < A[j-1]) {
                intercambiar(A, j, j-1);
            }
        }
    }
}

void ejecutarAlgoritmo(long long A[], long long B[], long long n, char algoritmo) {
    switch (algoritmo) {
        case 'i':
            insertion_sort(B, n);
            break;
        case 's':
            selection_sort(B, n);
            break;
        case 'b':
            bubblesort(B, n);
            break;
        case 'm':
            merge_sort(B, 0, n - 1);
            break;
        case 'q':
            quicksort(B, 0, n - 1);
            break;
        default:
            cout << "Algoritmo no reconocido." << endl;
            break;
    }
}

long long* copiar_arreglo(long long A[], long long n) {
    long long *aux = new long long[n];
    for (long long i = 0; i < n; i++) {
        aux[i] = A[i];
    }
    return aux;
}
