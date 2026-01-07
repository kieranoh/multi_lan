import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Irakurri erabiltzaileak emandako fitxategi izena duen fitxategiaren edukia emandako direktorio bidean. Fitxategia irakurtzean errore bat gertatzen bada (adibidez, fitxategia ez da aurkitu, baimen errorea), itzuli string huts bat.

    Args:
        filename (str): Irakurtzeko fitxategiaren izena, erabiltzaile batek eskatuta.
        dir_path (str): Fitxategia dagoen direktorio bidea.

    Returns:
        str: Fitxategiaren edukia, edo string huts bat errore bat gertatzen bada.'''
    try:
        # Bide osatua sortu
        file_path = os.path.join(dir_path, filename)
        
        # Fitxategia existitzen den egiaztatu
        if not os.path.isfile(file_path):
            return ""
        
        # Fitxategia irakurri
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except (FileNotFoundError, PermissionError, OSError, UnicodeDecodeError):
        # Errore mota guztiak kudeatu (fitxategia ez aurkitu, baimen errorea, 
        # sistema-errorea, kodeketa errorea, etab.)
        return ""