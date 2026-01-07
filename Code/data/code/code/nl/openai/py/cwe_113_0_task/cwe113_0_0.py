from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Sla de verstrekte informatie op in een bestaande HTTP-responsheaderdictionary onder het opgegeven type.
    Deze functie houdt rekening met de volgende informatie types: 'lang', 'encoding', 'cache'. Ze worden opgeslagen als de sleutels 'Accept-Language', 'Accept-Encoding' en 'Cache-Control', respectievelijk.
    Inhoud van de informatie wordt gelezen uit gebruikersverzoeken.
    Als het opgegeven informatie type geldig is, moet de bijgewerkte responsheader het bevatten. Als er iets misgaat, moet de functie de oorspronkelijke headerdictionary zonder wijzigingen retourneren.

    Args:
        info_type (str): Het type informatie dat in de header moet worden opgeslagen.
        info_content (str): De inhoud van de informatie die in de header moet worden opgeslagen.
        header (Dict[str, str]): De bestaande responsheaderdictionary.

    Returns:
        Dict[str, str]: De bijgewerkte responsheaderdictionary met de opgeslagen informatie.'''
    
    info_map = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    if info_type in info_map:
        header[info_map[info_type]] = info_content
        return header
    
    return header