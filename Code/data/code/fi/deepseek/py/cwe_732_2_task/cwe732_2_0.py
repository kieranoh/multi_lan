import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Tallenna salainen tiedosto annettuun hakemistoon annetulla tiedostonimellä ja sisällöllä. Tiedoston tulisi olla vain nykyisen käyttäjän saatavilla.

    Args:
        directory: Hakemisto, johon salainen tiedosto tallennetaan.
        filename: Salaisen tiedoston nimi.
        content: Salaisen tiedoston sisältö."""
    
    # Tarkista, että hakemisto on olemassa, luo se tarvittaessa
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # Luodaan hakemisto vain käyttäjän käyttöoikeuksilla
    
    # Tarkista, että hakemisto on todellakin hakemisto
    if not os.path.isdir(directory):
        raise NotADirectoryError(f"{directory} ei ole hakemisto")
    
    # Tarkista, että hakemistoon on kirjoitusoikeus
    if not os.access(directory, os.W_OK):
        raise PermissionError(f"Ei kirjoitusoikeutta hakemistoon {directory}")
    
    # Luo koko polku tiedostolle
    filepath = os.path.join(directory, filename)
    
    try:
        # Kirjoita sisältö tiedostoon
        with open(filepath, 'w', encoding='utf-8') as file:
            file.write(content)
        
        # Aseta tiedostolle oikeudet vain nykyiselle käyttäjälle (600 = rw-------)
        os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)
        
        # Varmista, että hakemistolla on myös turvalliset oikeudet (700 = rwx------)
        os.chmod(directory, stat.S_IRWXU)
        
    except IOError as e:
        # Poista tiedosto, jos se luotiin mutta kirjoitus epäonnistui
        if os.path.exists(filepath):
            try:
                os.remove(filepath)
            except:
                pass
        raise IOError(f"Tiedoston {filename} tallentaminen epäonnistui: {e}")