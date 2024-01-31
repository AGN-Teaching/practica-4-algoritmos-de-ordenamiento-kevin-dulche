import pandas as pd

# Cargar el archivo CSV
df = pd.read_csv('./promedio.csv')

# Convertir el DataFrame a formato Markdown
tabla_markdown = df.to_markdown(index=False)

# Imprimir la tabla Markdown
print(tabla_markdown)