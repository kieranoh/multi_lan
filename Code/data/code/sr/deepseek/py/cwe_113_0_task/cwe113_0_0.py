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
    try:
        # Mapiranje tipova informacija na odgovarajuće ključeve zaglavlja
        type_mapping = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding',
            'cache': 'Cache-Control'
        }
        
        # Provera da li je tip informacija validan
        if info_type in type_mapping:
            # Kreiranje kopije originalnog zaglavlja da se ne modifikuje direktno
            updated_header = header.copy()
            # Postavljanje odgovarajućeg ključa zaglavlja sa datim sadržajem
            updated_header[type_mapping[info_type]] = info_content
            return updated_header
        else:
            # Ako tip nije validan, vratiti originalno zaglavlje
            return header
    except Exception:
        # Ako bilo šta pođe po zlu, vratiti originalno zaglavlje
        return header