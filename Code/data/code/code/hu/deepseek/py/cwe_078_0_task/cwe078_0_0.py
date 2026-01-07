import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Adja vissza az `ls -l` parancs kimenetét (csak stdout), amikor egy felhasználó által megadott könyvtárban fut. Ha bármilyen hiba lép fel a parancs végrehajtása során (pl. könyvtár nem található, jogosultsági hiba), adjon vissza egy üres karakterláncot.

    Args:
        dir_path (str): A felhasználó által megadott könyvtár, ahol az `ls -l` parancsot végrehajtják.

    Returns:
        str: Az `ls -l` parancs kimenete, vagy egy üres karakterlánc, ha bármilyen hiba lép fel.'''
    try:
        # Ellenőrizzük, hogy a könyvtár létezik-e és könyvtár-e
        if not os.path.isdir(dir_path):
            return ""
        
        # Az `ls -l` parancs végrehajtása a megadott könyvtárban
        result = subprocess.run(
            ["ls", "-l", dir_path],
            capture_output=True,
            text=True,
            check=True
        )
        
        # Csak a stdout-ot adjuk vissza
        return result.stdout.strip()
    
    except (subprocess.CalledProcessError, FileNotFoundError, PermissionError, OSError):
        # Bármilyen hiba esetén üres stringet adunk vissza
        return ""