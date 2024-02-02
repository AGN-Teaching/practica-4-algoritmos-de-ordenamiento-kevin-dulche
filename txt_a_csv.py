import csv
import sys
import os

# Verificar si se proporciona el nombre del archivo de entrada
if len(sys.argv) != 2:
    print("Uso: python txt_a_csv.py <archivo_entrada>")
    sys.exit(1)

# Obtener el nombre del archivo de entrada desde los argumentos de la línea de comandos
archivo_entrada = sys.argv[1]

# Obtener el nombre del archivo sin la ruta y la extensión
nombre_archivo_sin_extension = os.path.splitext(os.path.basename(archivo_entrada))[0]

# Ruta de la carpeta 'csv' dentro de 'analisis'
ruta_carpeta_csv = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'analisis', 'csv')

# Crear la carpeta 'csv' si no existe
if not os.path.exists(ruta_carpeta_csv):
    os.makedirs(ruta_carpeta_csv)

# Archivo de salida con el nombre del archivo de entrada en la carpeta 'csv'
archivo_salida = os.path.join(ruta_carpeta_csv, f'{nombre_archivo_sin_extension}.csv')

# Lista para almacenar los datos
datos = []

# Bandera para indicar si la fila actual es un encabezado
es_encabezado = True

# Leer datos desde el archivo
with open(archivo_entrada, 'r') as archivo:
    lineas = archivo.readlines()
    for linea in lineas:
        # Eliminar espacios y tabuladores, dividir por espacios restantes
        fila = [dato.strip() for dato in linea.split() if dato]
        
        # Si la fila actual es un encabezado, agregar el nombre completo del algoritmo
        if es_encabezado:
            fila = ["Ejecución", "Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort", "Quicksort"]
            es_encabezado = False
        else:
            # Si el primer elemento es '#', quitarlo
            if fila and fila[0] == '#':
                fila.pop(0)
            
            # Eliminar la letra 's' del final de cada duración de ejecución
            fila = [dato.rstrip('s') for dato in fila]
        
        # Agregar la fila a la lista de datos
        datos.append(fila)

# Escribir los datos en un archivo CSV en la carpeta 'csv'
with open(archivo_salida, 'w', newline='') as csv_file:
    escribir_csv = csv.writer(csv_file)
    for fila in datos:
        escribir_csv.writerow(fila)

print(f"Archivo CSV creado exitosamente: '{archivo_salida}' en la carpeta '{ruta_carpeta_csv}'")
