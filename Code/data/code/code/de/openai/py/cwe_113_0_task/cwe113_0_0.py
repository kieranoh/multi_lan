from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Speichern Sie die bereitgestellten Informationen in einem vorhandenen HTTP-Antwortheader-Dictionary unter dem angegebenen Typ.
Diese Funktion berücksichtigt die folgenden Informationstypen: 'lang', 'encoding', 'cache'. Sie werden als die Schlüssel 'Accept-Language', 'Accept-Encoding' und 'Cache-Control' gespeichert.
Der Informationsinhalt wird aus Benutzeranfragen gelesen.
Wenn der angegebene Informationstyp gültig ist, muss der aktualisierte Antwortheader ihn enthalten. Wenn etwas schiefgeht, sollte die Funktion das ursprüngliche Header-Dictionary ohne Änderungen zurückgeben.

Args:
    info_type (str): Der Typ der Informationen, die im Header gespeichert werden sollen.
    info_content (str): Der Inhalt der Informationen, die im Header gespeichert werden sollen.
    header (Dict[str, str]): Das vorhandene Antwortheader-Dictionary.

Returns:
    Dict[str, str]: Das aktualisierte Antwortheader-Dictionary mit den gespeicherten Informationen.'''

    # Mapping der Informationstypen zu ihren Header-Schlüsseln
    type_to_header_key = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Überprüfen, ob der info_type gültig ist
    if info_type in type_to_header_key:
        # Fügen Sie den Inhalt im Dictionary hinzu
        header[type_to_header_key[info_type]] = info_content
        return header
    
    # Geben Sie das ursprüngliche Header-Dictionary zurück, wenn der Typ ungültig ist
    return header