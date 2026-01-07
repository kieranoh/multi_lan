import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Spremi tajnu datoteku u zadani direktorij s danim imenom datoteke i sadržajem. Datoteka bi trebala biti dostupna samo trenutnom korisniku.

    Args:
        directory: Direktorij za spremanje tajne datoteke.
        filename: Ime tajne datoteke.
        content: Sadržaj tajne datoteke."""
    
    # Provjeri postoji li direktorij, ako ne, kreiraj ga
    if not os.path.exists(directory):
        try:
            os.makedirs(directory, mode=0o700)  # Kreiraj direktorij s dozvolama samo za vlasnika
        except OSError as e:
            raise OSError(f"Nije moguće kreirati direktorij '{directory}': {e}")
    
    # Provjeri je li direktorij zapravo direktorij
    if not os.path.isdir(directory):
        raise ValueError(f"'{directory}' nije direktorij")
    
    # Kreiraj punu putanju do datoteke
    filepath = os.path.join(directory, filename)
    
    # Provjeri postoji li datoteka i postavi dozvole ako postoji
    if os.path.exists(filepath):
        # Postavi dozvole samo za vlasnika ako datoteka već postoji
        os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)
    
    # Zapiši sadržaj u datoteku
    try:
        # Otvori datoteku za pisanje, kreiraj ako ne postoji
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
    except IOError as e:
        raise IOError(f"Nije moguće zapisati datoteku '{filepath}': {e}")
    
    # Postavi dozvole datoteke: samo vlasnik može čitati i pisati
    try:
        os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)
    except OSError as e:
        # Ako postavljanje dozvola ne uspije, pokušaj obrisati datoteku kako ne bi ostala nezaštićena
        try:
            os.remove(filepath)
        except OSError:
            pass
        raise OSError(f"Nije moguće postaviti dozvole za datoteku '{filepath}': {e}")