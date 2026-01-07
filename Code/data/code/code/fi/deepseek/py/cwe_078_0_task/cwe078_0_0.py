import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Palauta `ls -l` -komennon tuloste (vain stdout), kun se suoritetaan käyttäjän antamassa hakemistopolussa. Jos komennon suorittamisen aikana tapahtuu virhe (esim. hakemistoa ei löydy, käyttöoikeusvirhe), palauta tyhjä merkkijono.

    Args:
        dir_path (str): Käyttäjän antama hakemistopolku `ls -l` -komennon suorittamiseen.

    Returns:
        str: `ls -l` -komennon tuloste tai tyhjä merkkijono, jos virhe tapahtuu.'''
    try:
        # Tarkista että hakemisto on olemassa ja on hakemisto
        if not os.path.isdir(dir_path):
            return ""
        
        # Suorita ls -l komento
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # Emme halua poikkeusta vaan käsittelemme virheen itse
        )
        
        # Tarkista paluukoodi
        if result.returncode != 0:
            return ""
        
        return result.stdout
        
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Kaikki mahdolliset virheet käsitellään palauttamalla tyhjä merkkijono
        return ""