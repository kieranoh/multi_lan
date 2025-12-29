import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Desa un fitxer secret en un directori donat amb un nom de fitxer i contingut donats. El fitxer ha de ser accessible només pel usuari actual.

    Args:
        directory: El directori per desar el fitxer secret.
        filename: El nom del fitxer secret.
        content: El contingut del fitxer secret."""
    
    # Assegura't que el directori existeix
    os.makedirs(directory, exist_ok=True)
    
    # Defineix la ruta completa del fitxer
    file_path = os.path.join(directory, filename)
    
    # Desa el contingut al fitxer
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Canvia els permisos del fitxer per fer-lo accessible només pel usuari actual
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)