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
        # Luo kopio alkuperäisestä headerista, jotta voidaan palauttaa alkuperäinen jos tulee virhe
        updated_header = header.copy()
        
        # Tarkista info_type ja aseta vastaava header-avain
        if info_type == 'lang':
            header_key = 'Accept-Language'
        elif info_type == 'encoding':
            header_key = 'Accept-Encoding'
        elif info_type == 'cache':
            header_key = 'Cache-Control'
        else:
            # Jos info_type ei ole tunnistettu, palauta alkuperäinen header
            return header
        
        # Tarkista että info_content on merkkijono eikä tyhjä
        if not isinstance(info_content, str) or not info_content.strip():
            return header
        
        # Päivitä header uudella arvolla
        updated_header[header_key] = info_content.strip()
        
        return updated_header
        
    except Exception:
        # Jos tulee mikä tahansa virhe, palauta alkuperäinen header
        return header