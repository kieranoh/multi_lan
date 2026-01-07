import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Lue käyttäjän antaman tiedoston sisältö annetusta hakemistopolusta. Jos tiedoston lukemisen aikana tapahtuu virhe (esim. tiedostoa ei löydy, käyttöoikeusvirhe), palauta tyhjää merkkijonoa.

    Args:
        filename (str): Luettavan tiedoston nimi, käyttäjän pyytämä.
        dir_path (str): Hakemistopolku, jossa tiedosto sijaitsee.

    Returns:
        str: Tiedoston sisältö, tai tyhjää merkkijonoa, jos virhe tapahtuu.'''
    try:
        # Yhdistetään hakemistopolku ja tiedostonimi turvallisesti
        file_path = os.path.join(dir_path, filename)
        
        # Avataan tiedosto ja luetaan sen sisältö
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        
        return content
    
    except Exception:
        # Kaikki mahdolliset virheet käsitellään palauttamalla tyhjä merkkijono
        return ""