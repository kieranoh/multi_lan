import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Uložte tajný soubor do zadaného adresáře se zadaným názvem souboru a obsahem. Soubor by měl být přístupný pouze aktuálnímu uživateli.

    Args:
        directory: Adresář pro uložení tajného souboru.
        filename: Název tajného souboru.
        content: Obsah tajného souboru."""
    
    # Vytvoření adresáře, pokud neexistuje
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # Adresář přístupný pouze vlastníkovi
    
    # Cesta k souboru
    filepath = os.path.join(directory, filename)
    
    # Zápis obsahu do souboru
    with open(filepath, 'w', encoding='utf-8') as file:
        file.write(content)
    
    # Nastavení oprávnění souboru: pouze vlastník může číst a zapisovat
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)