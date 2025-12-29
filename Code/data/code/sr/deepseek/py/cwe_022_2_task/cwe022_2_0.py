import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Izdvojite sadržaj tar datoteke u zadatu putanju odredišta.
    Ako je ekstrakcija uspešna, vratite True; inače, ako dođe do bilo kakve greške tokom procesa ekstrakcije (npr. datoteka nije pronađena, greška u dozvolama, ne može se izdvojiti sav sadržaj), jednostavno vratite False.

    Args:
        tar_path: putanja do tar datoteke
        dest_path: putanja do odredišne fascikle

    Returns:
        True ako je ekstrakcija uspešna; inače, False'''
    try:
        # Provera da li tar datoteka postoji
        if not os.path.exists(tar_path):
            return False
        
        # Provera da li je odredišna putanja direktorijum
        # Ako ne postoji, pokušaj da je kreiraš
        if not os.path.exists(dest_path):
            try:
                os.makedirs(dest_path, exist_ok=True)
            except (OSError, PermissionError):
                return False
        
        # Otvaranje tar datoteke i ekstrakcija
        with tarfile.open(tar_path, 'r') as tar:
            # Provera da li je datoteka validna tar datoteka
            tar.getmembers()  # Ovo će baciti izuzetak ako datoteka nije validna tar datoteka
            
            # Ekstrakcija svih datoteka
            tar.extractall(path=dest_path)
        
        return True
        
    except (tarfile.TarError, OSError, IOError, PermissionError, FileNotFoundError):
        # Hvatanje svih mogućih grešaka vezanih za tar datoteku,
        # operacije sa datotekama, dozvole, itd.
        return False
    except Exception:
        # Hvatanje bilo koje druge neočekivane greške
        return False