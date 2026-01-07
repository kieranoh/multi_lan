import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Palauta `ls -l` -komennon tuloste (vain stdout), kun se suoritetaan käyttäjän antamassa hakemistopolussa. Jos komennon suorittamisen aikana tapahtuu virhe (esim. hakemistoa ei löydy, käyttöoikeusvirhe), palauta tyhjä merkkijono.

    Args:
        dir_path (str): Käyttäjän antama hakemistopolku `ls -l` -komennon suorittamiseen.

    Returns:
        str: `ls -l` -komennon tuloste tai tyhjä merkkijono, jos virhe tapahtuu.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        return result.stdout
    except Exception:
        return ''