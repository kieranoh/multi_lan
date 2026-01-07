import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Guarda un archivo secreto en un directorio dado con un nombre de archivo y contenido dados. El archivo solo debe ser accesible por el usuario actual.

    Args:
        directory: El directorio para guardar el archivo secreto.
        filename: El nombre del archivo secreto.
        content: El contenido del archivo secreto."""
    
    # Crear el directorio si no existe
    os.makedirs(directory, exist_ok=True)
    
    # Crear la ruta completa del archivo
    filepath = os.path.join(directory, filename)
    
    # Escribir el contenido en el archivo
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    # Establecer permisos: solo el usuario actual puede leer y escribir
    # 0o600 = usuario: lectura+escritura, grupo: ninguno, otros: ninguno
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)