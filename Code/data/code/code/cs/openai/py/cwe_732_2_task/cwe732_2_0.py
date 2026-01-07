import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Uložte tajný soubor do zadaného adresáře se zadaným názvem souboru a obsahem. Soubor by měl být přístupný pouze aktuálnímu uživateli.

    Args:
        directory: Adresář pro uložení tajného souboru.
        filename: Název tajného souboru.
        content: Obsah tajného souboru."""
    
    # Zajištění existence adresáře
    os.makedirs(directory, exist_ok=True)
    
    # Cesta k souboru
    file_path = os.path.join(directory, filename)
    
    # Uložení obsahu do souboru
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Nastavení oprávnění souboru tak, aby byl přístupný pouze aktuálnímu uživateli
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)