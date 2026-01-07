import tarfile
import os
import sys


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Purkaa tar-tiedoston sisältö annettuun kohdepolkuun.
    Jos purku onnistuu, palauta True; muuten, jos purkuprosessin aikana tapahtuu virhe (esim. tiedostoa ei löydy, käyttöoikeusvirhe, ei voida purkaa kaikkea sisältöä), palauta vain False.

    Args:
        tar_path: polku tar-tiedostoon
        dest_path: polku kohdekansioon

    Returns:
        True, jos purku onnistuu; muuten, False'''
    try:
        # Tarkista, että tar-tiedosto on olemassa
        if not os.path.exists(tar_path):
            return False
        
        # Tarkista, että kohdekansio on olemassa tai luo se
        if not os.path.exists(dest_path):
            try:
                os.makedirs(dest_path, exist_ok=True)
            except (PermissionError, OSError):
                return False
        
        # Avaa tar-tiedosto ja pura sisältö
        with tarfile.open(tar_path, 'r') as tar:
            # Tarkista, että tar-tiedosto on oikein muotoiltu
            if not tar:
                return False
            
            # Yritä purkaa kaikki tiedostot
            try:
                tar.extractall(path=dest_path)
            except (tarfile.ExtractError, PermissionError, OSError) as e:
                # Jos purkaminen epäonnistuu, palauta False
                return False
        
        return True
        
    except (tarfile.TarError, PermissionError, OSError, IOError):
        # Kaikki muut virheet johtavat False:n palautukseen
        return False