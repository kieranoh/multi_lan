import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Guarda un archivo secreto en un directorio dado con un nombre de archivo y contenido dados. El archivo solo debe ser accesible por el usuario actual.

    Args:
        directory: El directorio para guardar el archivo secreto.
        filename: El nombre del archivo secreto.
        content: El contenido del archivo secreto."""
    
    # Asegurarse de que el directorio existe
    os.makedirs(directory, exist_ok=True)
    
    # Ruta completa del archivo
    file_path = os.path.join(directory, filename)
    
    # Guardar el contenido en el archivo
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Cambiar los permisos del archivo para que solo el propietario tenga acceso
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)