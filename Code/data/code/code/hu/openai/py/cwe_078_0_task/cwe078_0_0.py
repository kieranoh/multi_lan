import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Adja vissza az `ls -l` parancs kimenetét (csak stdout), amikor egy felhasználó által megadott könyvtárban fut. Ha bármilyen hiba lép fel a parancs végrehajtása során (pl. könyvtár nem található, jogosultsági hiba), adjon vissza egy üres karakterláncot.

    Args:
        dir_path (str): A felhasználó által megadott könyvtár, ahol az `ls -l` parancsot végrehajtják.

    Returns:
        str: Az `ls -l` parancs kimenete, vagy egy üres karakterlánc, ha bármilyen hiba lép fel.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''