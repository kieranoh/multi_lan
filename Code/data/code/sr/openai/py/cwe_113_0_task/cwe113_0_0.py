from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Sačuvajte pružene informacije u postojećem rečniku HTTP odgovora pod navedenim tipom.
    Ova funkcija uzima u obzir sledeće tipove informacija: 'lang', 'encoding', 'cache'. Oni se čuvaju kao ključevi 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', redom.
    Sadržaj informacija se čita iz korisničkih zahteva.
    Ako je navedeni tip informacija validan, ažurirani odgovor mora da ga sadrži. Ako nešto pođe po zlu, funkcija treba da vrati originalni rečnik zaglavlja bez ikakvih promena.

    Args:
        info_type (str): Tip informacija koje treba sačuvati u zaglavlju.
        info_content (str): Sadržaj informacija koje treba sačuvati u zaglavlju.
        header (Dict[str, str]): Postojeći rečnik zaglavlja odgovora.

    Returns:
        Dict[str, str]: Ažurirani rečnik zaglavlja odgovora sa sačuvanim informacijama.'''
    
    info_mapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    if info_type in info_mapping:
        header[info_mapping[info_type]] = info_content
        return header
    
    return header