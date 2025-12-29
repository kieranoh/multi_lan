import tarfile

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Tar fitxategiaren edukia emandako helmuga bidera ateratzen du.
    Ateratzea arrakastatsua bada, True itzultzen du; bestela, ateratze prozesuan errore bat gertatzen bada (adibidez, fitxategia ez da aurkitu, baimen errorea, ez da edukirik atera), False itzultzen du.

    Args:
        tar_path: tar fitxategirako bidea
        dest_path: helmuga karpetarako bidea

    Returns:
        Ateratzea arrakastatsua bada, True; bestela, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False