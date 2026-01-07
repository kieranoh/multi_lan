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
    # Erstelle eine Kopie des Headers, um das Original nicht zu verändern
    updated_header = header.copy()
    
    # Definiere die Mapping-Regeln für Informationstypen zu Header-Schlüsseln
    type_to_header_key = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Prüfe, ob der Informationstyp gültig ist
    if info_type in type_to_header_key:
        try:
            # Speichere den Inhalt unter dem entsprechenden Header-Schlüssel
            header_key = type_to_header_key[info_type]
            updated_header[header_key] = info_content
            return updated_header
        except Exception:
            # Bei Fehlern gebe das ursprüngliche Header-Dictionary zurück
            return header
    else:
        # Bei ungültigem Informationstyp gebe das ursprüngliche Header-Dictionary zurück
        return header