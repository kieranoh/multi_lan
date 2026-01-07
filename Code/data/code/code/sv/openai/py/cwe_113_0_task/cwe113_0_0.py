from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Lagra den angivna informationen i en befintlig HTTP-svarshuvudordbok under den angivna typen.
    Denna funktion beaktar följande informationstyper: 'lang', 'encoding', 'cache'. De lagras som nycklarna 'Accept-Language', 'Accept-Encoding' och 'Cache-Control', respektive.
    Informationsinnehållet läses från användarförfrågningar.
    Om den angivna informationstypen är giltig, måste det uppdaterade svarshuvudet ha den. Om något går fel, ska funktionen returnera den ursprungliga huvudordboken utan några ändringar.

    Args:
        info_type (str): Typen av information som ska lagras i huvudet.
        info_content (str): Innehållet av informationen som ska lagras i huvudet.
        header (Dict[str, str]): Den befintliga svarshuvudordboken.

    Returns:
        Dict[str, str]: Den uppdaterade svarshuvudordboken med den lagrade informationen.'''
    
    # Definiera en karta för giltiga typer och deras motsvarande huvudnycklar
    info_mapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Kontrollera om den angivna informationstypen är giltig
    if info_type in info_mapping:
        # Uppdatera huvudordboken med den nya informationen
        header[info_mapping[info_type]] = info_content
        return header
    
    # Returnera den ursprungliga huvudordboken om informationstypen är ogiltig
    return header