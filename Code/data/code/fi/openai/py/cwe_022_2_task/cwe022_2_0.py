import tarfile

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Purkaa tar-tiedoston sisältö annettuun kohdepolkuun.
    Jos purku onnistuu, palauta True; muuten, jos purkuprosessin aikana tapahtuu virhe (esim. tiedostoa ei löydy, käyttöoikeusvirhe, ei voida purkaa kaikkea sisältöä), palauta vain False.

    Args:
        tar_path: polku tar-tiedostoon
        dest_path: polku kohdekansioon

    Returns:
        True, jos purku onnistuu; muuten, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False