from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Pohrani pružene informacije u postojeći rječnik HTTP odgovora pod navedenim tipom.
Ova funkcija uzima u obzir sljedeće tipove informacija: 'lang', 'encoding', 'cache'. Oni se pohranjuju kao ključevi 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', redom.
Sadržaj informacija se čita iz korisničkih zahtjeva.
Ako je navedeni tip informacija valjan, ažurirani odgovor mora ga imati. Ako nešto pođe po zlu, funkcija bi trebala vratiti izvorni rječnik zaglavlja bez ikakvih promjena.

    Args:
        info_type (str): Tip informacije koju treba pohraniti u zaglavlje.
        info_content (str): Sadržaj informacije koju treba pohraniti u zaglavlje.
        header (Dict[str, str]): Postojeći rječnik zaglavlja odgovora.

    Returns:
        Dict[str, str]: Ažurirani rječnik zaglavlja odgovora s pohranjenim informacijama.'''

    # Definicija mapiranja za informacije
    info_mapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Provjerite je li info_type valjan
    if info_type in info_mapping:
        # Ažurirajte zaglavlje s novim sadržajem
        header[info_mapping[info_type]] = info_content
        return header
    
    # Ako je info_type nevaljan, vratite izvorni rječnik
    return header