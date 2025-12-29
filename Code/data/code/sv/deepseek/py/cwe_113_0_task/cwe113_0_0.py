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
    
    # Skapa en kopia av originalheadern för att undvika att modifiera originalet
    updated_header = header.copy()
    
    # Mappning från info_type till HTTP-huvudnyckel
    type_to_header_key = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    try:
        # Kontrollera om info_type är giltig
        if info_type in type_to_header_key:
            # Hämta motsvarande HTTP-huvudnyckel
            header_key = type_to_header_key[info_type]
            
            # Uppdatera huvudet med den nya informationen
            updated_header[header_key] = info_content
            
            return updated_header
        else:
            # Om info_type inte är giltig, returnera originalheadern
            return header
    except Exception:
        # Om något går fel, returnera originalheadern
        return header