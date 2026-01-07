from typing import Dict


def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Zapisz podane informacje w istniejącej słowniku nagłówków odpowiedzi HTTP pod określonym typem.
Ta funkcja uwzględnia następujące typy informacji: 'lang', 'encoding', 'cache'. Są one przechowywane jako klucze 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', odpowiednio.
Zawartość informacji jest odczytywana z żądań użytkowników.
Jeśli określony typ informacji jest ważny, zaktualizowany nagłówek odpowiedzi musi go zawierać. Jeśli coś pójdzie nie tak, funkcja powinna zwrócić oryginalny słownik nagłówków bez żadnych zmian.

    Args:
        info_type (str): Typ informacji do zapisania w nagłówku.
        info_content (str): Zawartość informacji do zapisania w nagłówku.
        header (Dict[str, str]): Istniejący słownik nagłówków odpowiedzi.

    Returns:
        Dict[str, str]: Zaktualizowany słownik nagłówków odpowiedzi z zapisanymi informacjami.'''
    try:
        # Tworzymy kopię nagłówka, aby nie modyfikować oryginału w przypadku błędu
        updated_header = header.copy()
        
        # Mapowanie typów informacji na odpowiednie klucze nagłówków HTTP
        type_mapping = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding', 
            'cache': 'Cache-Control'
        }
        
        # Sprawdzamy czy podany typ informacji jest obsługiwany
        if info_type in type_mapping:
            # Ustawiamy odpowiedni nagłówek z podaną zawartością
            updated_header[type_mapping[info_type]] = info_content
            return updated_header
        else:
            # Jeśli typ nie jest obsługiwany, zwracamy oryginalny nagłówek
            return header
            
    except Exception:
        # W przypadku jakiegokolwiek błędu, zwracamy oryginalny nagłówek
        return header