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
    try:
        # Provjera je li info_content prazan string ili None
        if not info_content:
            return header
        
        # Mapiranje tipova informacija na odgovarajuća zaglavlja
        type_mapping = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding',
            'cache': 'Cache-Control'
        }
        
        # Provjera je li tip informacija valjan
        if info_type not in type_mapping:
            return header
        
        # Stvaranje kopije originalnog zaglavlja kako ne bismo modificirali original
        updated_header = header.copy()
        
        # Dodavanje informacija u zaglavlje
        header_key = type_mapping[info_type]
        updated_header[header_key] = info_content
        
        return updated_header
        
    except Exception:
        # Ako bilo što pođe po zlu, vrati originalno zaglavlje
        return header