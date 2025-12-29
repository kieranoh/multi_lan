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
    # Maak een kopie van de originele header om te voorkomen dat de invoer wordt gewijzigd
    updated_header = header.copy()
    
    # Definieer de mapping van info_type naar header sleutel
    type_to_key = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Controleer of het info_type geldig is
    if info_type in type_to_key:
        # Haal de corresponderende header sleutel op
        header_key = type_to_key[info_type]
        # Voeg de info_content toe aan de header onder de juiste sleutel
        updated_header[header_key] = info_content
        return updated_header
    else:
        # Als het info_type ongeldig is, retourneer de originele header zonder wijzigingen
        return header