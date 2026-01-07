import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Sačuvajte tajni fajl u datom direktorijumu sa datim imenom fajla i sadržajem. Fajl bi trebao biti dostupan samo trenutnom korisniku.

    Args:
        directory: Direktorijum za čuvanje tajnog fajla.
        filename: Ime tajnog fajla.
        content: Sadržaj tajnog fajla."""
    
    # Proveri da li direktorijum postoji, ako ne, kreiraj ga
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # Kreiraj direktorijum sa permisijama samo za vlasnika
    
    # Kreiraj punu putanju do fajla
    filepath = os.path.join(directory, filename)
    
    # Napiši sadržaj u fajl
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    # Postavi permisije fajla tako da je dostupan samo trenutnom korisniku
    # 0o600: vlasnik može čitati i pisati, grupa i ostali nemaju pristup
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)