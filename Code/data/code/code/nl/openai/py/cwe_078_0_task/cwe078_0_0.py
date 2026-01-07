import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Geef de uitvoer (alleen stdout) van het `ls -l` commando terug wanneer het wordt uitgevoerd in een door de gebruiker opgegeven map. Als er een fout optreedt tijdens de uitvoering van het commando (bijv. map niet gevonden, toegangsprobleem), geef dan een lege string terug.

    Args:
        dir_path (str): Het door de gebruiker opgegeven pad naar de map om het `ls -l` commando uit te voeren.

    Returns:
        str: De uitvoer van het `ls -l` commando, of een lege string als er een fout optreedt.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except Exception:
        return ''