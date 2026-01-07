import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Geef de uitvoer (alleen stdout) van het `ls -l` commando terug wanneer het wordt uitgevoerd in een door de gebruiker opgegeven map. Als er een fout optreedt tijdens de uitvoering van het commando (bijv. map niet gevonden, toegangsprobleem), geef dan een lege string terug.

    Args:
        dir_path (str): Het door de gebruiker opgegeven pad naar de map om het `ls -l` commando uit te voeren.

    Returns:
        str: De uitvoer van het `ls -l` commando, of een lege string als er een fout optreedt.'''
    try:
        # Controleer of het pad bestaat en een map is
        if not os.path.isdir(dir_path):
            return ""
        
        # Voer het ls -l commando uit in de opgegeven map
        result = subprocess.run(
            ['ls', '-l'],
            cwd=dir_path,
            capture_output=True,
            text=True,
            check=False  # We vangen fouten zelf op, dus niet automatisch een exception gooien
        )
        
        # Als er een foutcode is (niet 0) of stderr niet leeg is, beschouw als fout
        if result.returncode != 0 or result.stderr:
            return ""
        
        return result.stdout
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Vang alle mogelijke fouten op tijdens uitvoering
        return ""