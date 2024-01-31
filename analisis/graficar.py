import pandas as pd
import matplotlib.pyplot as plt
import os
import argparse
import sys

# Verificar el número correcto de argumentos
if len(sys.argv) != 2:
    print("Uso: python tu_script.py <archivo_csv>")
    sys.exit(1)

# Configurar el parser de argumentos
parser = argparse.ArgumentParser(description='Generar gráficos y guardarlos en una carpeta.')
parser.add_argument('archivo_csv', type=str, help='Ruta del archivo CSV')

# Obtener los argumentos del script
args = parser.parse_args()

# Verificar si la carpeta 'assets' existe, si no, crearla
carpeta_assets = "./assets"
if not os.path.exists(carpeta_assets):
    os.makedirs(carpeta_assets)

# Obtener el nombre del archivo sin la extensión
nombre_archivo_sin_extension = os.path.splitext(os.path.basename(args.archivo_csv))[0]

# Cargar el DataFrame desde el archivo CSV
df = pd.read_csv(args.archivo_csv)

# Crear gráficos de dispersión para cada algoritmo con la línea de desviación estándar
fig, axs = plt.subplots(2, 3, figsize=(18, 10))

# Lista de algoritmos
algoritmos = ['Insertion Sort', 'Selection Sort', 'Bubble Sort', 'Merge Sort', 'Quicksort']

for i, algoritmo in enumerate(algoritmos):
    row = i // 3
    col = i % 3
    ax = axs[row, col]
    ax.scatter(df['Ejecución'], df[algoritmo])
    ax.axhline(df[algoritmo].mean(), color='red', linestyle='dashed', linewidth=2, label='Media')
    ax.axhline(df[algoritmo].mean() + df[algoritmo].std(), color='orange', linestyle='dashed', linewidth=2, label='+1 Desviación Estándar')
    ax.axhline(df[algoritmo].mean() - df[algoritmo].std(), color='orange', linestyle='dashed', linewidth=2, label='-1 Desviación Estándar')
    ax.set_title(f'{algoritmo}\nDesviación Estándar: {df[algoritmo].std():.2e}\nPromedio: {df[algoritmo].mean():.2e}')
    ax.set_xlabel('Ejecución')
    ax.set_ylabel('Tiempo de Ejecución')
    ax.legend()
    print(f'\n{algoritmo}\nDesviación Estándar: {df[algoritmo].std():.2e}\nPromedio: {df[algoritmo].mean():.2e}')

axs[1,2].axis("off")

# Ajustar márgenes
plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.1, wspace=0.4, hspace=0.4)

# Construir el nombre del archivo de imagen dinámicamente
nombre_archivo_imagen = f"{nombre_archivo_sin_extension}.png"
ruta_guardado = os.path.join(carpeta_assets, nombre_archivo_imagen)

# Guardar la imagen en la carpeta 'assets' con el nombre construido dinámicamente
plt.savefig(ruta_guardado)

