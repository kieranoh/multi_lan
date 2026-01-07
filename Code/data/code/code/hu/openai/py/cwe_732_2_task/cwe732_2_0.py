import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Mentse el a titkos fájlt egy megadott könyvtárba a megadott fájlnévvel és tartalommal. A fájl csak a jelenlegi felhasználó számára legyen elérhető.

    Args:
        directory: A titkos fájl mentésére szolgáló könyvtár.
        filename: A titkos fájl neve.
        content: A titkos fájl tartalma."""
    
    # Létrehozzuk a megadott könyvtárat, ha nem létezik
    os.makedirs(directory, exist_ok=True)
    
    # A fájl teljes elérési útja
    file_path = os.path.join(directory, filename)
    
    # Fájl írása
    with open(file_path, 'w') as file:
        file.write(content)
    
    # A fájl jogosultságainak beállítása, hogy csak a jelenlegi felhasználó férhessen hozzá
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)