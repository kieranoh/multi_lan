from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Tallenna annettu tieto olemassa olevaan HTTP-vastauspäätteen sanakirjaan määritellyn tyypin mukaan.
    Tämä funktio ottaa huomioon seuraavat tietotyypit: 'lang', 'encoding', 'cache'. Ne tallennetaan avaimilla 'Accept-Language', 'Accept-Encoding' ja 'Cache-Control'.
    Tietosisältö luetaan käyttäjän pyynnöistä.
    Jos määritelty tietotyyppi on voimassa, päivitetyn vastauspäätteen on sisällettävä se. Jos jokin menee pieleen, funktion on palautettava alkuperäinen päätteen sanakirja ilman muutoksia.

    Args:
        info_type (str): Tietotyypin, joka tallennetaan päätteen, tyyppi.
        info_content (str): Tietosisällön, joka tallennetaan päätteen, sisältö.
        header (Dict[str, str]): Olemassa oleva vastauspäätteen sanakirja.

    Returns:
        Dict[str, str]: Päivitetty vastauspäätteen sanakirja tallennetulla tiedolla.'''
    
    try:
        if info_type == 'lang':
            header['Accept-Language'] = info_content
        elif info_type == 'encoding':
            header['Accept-Encoding'] = info_content
        elif info_type == 'cache':
            header['Cache-Control'] = info_content
        else:
            return header  # Return original header if info_type is invalid
        
    except Exception:
        return header  # Return original header on any exception

    return header  # Return updated header