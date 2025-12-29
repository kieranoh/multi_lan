import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Mentse el a titkos fájlt egy megadott könyvtárba a megadott fájlnévvel és tartalommal. A fájl csak a jelenlegi felhasználó számára legyen elérhető.

    Args:
        directory: A titkos fájl mentésére szolgáló könyvtár.
        filename: A titkos fájl neve.
        content: A titkos fájl tartalma."""
    
    # Ellenőrizzük, hogy a könyvtár létezik-e, ha nem, létrehozzuk
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700, exist_ok=True)
    else:
        # Ha a könyvtár létezik, beállítjuk a megfelelő jogosultságokat
        os.chmod(directory, stat.S_IRWXU)
    
    # A teljes fájl elérési út
    file_path = os.path.join(directory, filename)
    
    # Tartalom írása a fájlba
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(content)
    
    # Fájl jogosultságok beállítása: csak a tulajdonos olvashatja és írhatja
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)