import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Irakurri erabiltzaileak emandako fitxategi izena duen fitxategiaren edukia emandako direktorio bidean. Fitxategia irakurtzean errore bat gertatzen bada (adibidez, fitxategia ez da aurkitu, baimen errorea), itzuli string huts bat.

    Args:
        filename (str): Irakurtzeko fitxategiaren izena, erabiltzaile batek eskatuta.
        dir_path (str): Fitxategia dagoen direktorio bidea.

    Returns:
        str: Fitxategiaren edukia, edo string huts bat errore bat gertatzen bada.'''
    file_path = os.path.join(dir_path, filename)
    
    try:
        with open(file_path, 'r') as file:
            return file.read()
    except (FileNotFoundError, PermissionError):
        return ''