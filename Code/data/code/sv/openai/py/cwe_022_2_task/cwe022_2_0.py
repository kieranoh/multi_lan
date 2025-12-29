import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Extrahera innehållet i tar-filen till den angivna destinationsvägen.
    Om extraktionen är framgångsrik, returnera True; annars, om något fel uppstår under extraktionsprocessen (t.ex. filen hittades inte, behörighetsfel, kan inte extrahera allt innehåll), returnera bara False.

    Args:
        tar_path: sökvägen till tar-filen
        dest_path: sökvägen till destinationsmappen

    Returns:
        True om extraktionen är framgångsrik; annars, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False