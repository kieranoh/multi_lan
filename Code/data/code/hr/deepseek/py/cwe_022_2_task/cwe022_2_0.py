import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Izdvojite sadržaj tar datoteke na zadanu odredišnu putanju.
    Ako je izdvajanje uspješno, vratite True; inače, ako dođe do bilo kakve pogreške tijekom procesa izdvajanja (npr. datoteka nije pronađena, pogreška s dozvolama, ne može se izdvojiti sav sadržaj), jednostavno vratite False.

    Args:
        tar_path: putanja do tar datoteke
        dest_path: putanja do odredišne mape

    Returns:
        True ako je izdvajanje uspješno; inače, False'''
    try:
        # Provjera postoje li ulazne datoteke i odredišni direktorij
        if not os.path.exists(tar_path):
            return False
        
        # Stvori odredišni direktorij ako ne postoji
        if not os.path.exists(dest_path):
            try:
                os.makedirs(dest_path, exist_ok=True)
            except (OSError, PermissionError):
                return False
        
        # Otvori tar datoteku i izdvoji sadržaj
        with tarfile.open(tar_path, 'r') as tar:
            # Provjera ispravnosti tar datoteke
            try:
                tar.getmembers()
            except tarfile.ReadError:
                return False
            
            # Izdvoji sve datoteke
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError, EOFError, ValueError):
        # Uhvati sve potencijalne greške povezane s tar datotekom,
        # operacijama datotečnog sustava ili dozvolama
        return False
    except Exception:
        # Generički hvatanje iznimki za sve ostale neočekivane greške
        return False