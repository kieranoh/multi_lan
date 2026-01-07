from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Gehitu emandako informazioa HTTP erantzunaren goiburuen dictionary batean zehaztutako motaren arabera.
    Funtzio honek informazio mota hauek kontuan hartzen ditu: 'lang', 'encoding', 'cache'. Horiek 'Accept-Language', 'Accept-Encoding' eta 'Cache-Control' gako gisa gordetzen dira, hurrenez hurren.
    Informazioaren edukia erabiltzaileen eskaeretatik irakurtzen da.
    Zehaztutako informazio mota baliozkoa bada, eguneratutako erantzun goiburuan izan behar du. Edozein arazo izanez gero, funtzioak jatorrizko goiburuen dictionary-a itzuli behar du inolako aldaketarik gabe.

    Args:
        info_type (str): Goiburuan gorde beharreko informazioaren mota.
        info_content (str): Goiburuan gorde beharreko informazioaren edukia.
        header (Dict[str, str]): Jadanik dagoen erantzun goiburuen dictionary-a.

    Returns:
        Dict[str, str]: Gorde den informazioa duen eguneratutako erantzun goiburuen dictionary-a.'''

    valid_types = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }

    if info_type in valid_types:
        header[valid_types[info_type]] = info_content
        return header
    
    return header