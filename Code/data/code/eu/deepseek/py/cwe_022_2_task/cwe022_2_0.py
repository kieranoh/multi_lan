import tarfile
import os


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Tar fitxategiaren edukia emandako helmuga bidera ateratzen du.
    Ateratzea arrakastatsua bada, True itzultzen du; bestela, ateratze prozesuan errore bat gertatzen bada (adibidez, fitxategia ez da aurkitu, baimen errorea, ez da edukirik atera), False itzultzen du.

    Args:
        tar_path: tar fitxategirako bidea
        dest_path: helmuga karpetarako bidea

    Returns:
        Ateratzea arrakastatsua bada, True; bestela, False'''
    try:
        # Egiaztatu sarrerako fitxategia existitzen den
        if not os.path.exists(tar_path):
            return False
        
        # Egiaztatu helmuga direktorioa existitzen den; sortu beharrezkoa bada
        if not os.path.exists(dest_path):
            try:
                os.makedirs(dest_path, exist_ok=True)
            except (OSError, PermissionError):
                return False
        
        # Ireki tar fitxategia eta atera edukia
        with tarfile.open(tar_path, 'r') as tar:
            # Egiaztatu tar fitxategiak edukirik duen
            if len(tar.getmembers()) == 0:
                return False
            
            # Atera edukia helmuga bidera
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, PermissionError, IOError):
        # Har edozein errore (tar fitxategiaren erroreak, sarrera/irteera erroreak, baimen erroreak)
        return False