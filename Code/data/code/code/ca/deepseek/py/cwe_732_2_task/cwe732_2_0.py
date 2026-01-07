import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Desa un fitxer secret en un directori donat amb un nom de fitxer i contingut donats. El fitxer ha de ser accessible només pel usuari actual.

    Args:
        directory: El directori per desar el fitxer secret.
        filename: El nom del fitxer secret.
        content: El contingut del fitxer secret."""
    
    # Crear el directori si no existeix
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # Permisos: només l'usuari actual pot llegir, escriure i executar
    
    # Crear la ruta completa del fitxer
    filepath = os.path.join(directory, filename)
    
    # Escriure el contingut al fitxer
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    # Establir permisos del fitxer: només l'usuari actual pot llegir i escriure
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)  # 0o600