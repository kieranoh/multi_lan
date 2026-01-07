from typing import Dict


def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Memorizza le informazioni fornite in un dizionario di intestazioni di risposta HTTP esistente sotto il tipo specificato.
Questa funzione considera i seguenti tipi di informazioni: 'lang', 'encoding', 'cache'. Vengono memorizzati come le chiavi 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', rispettivamente.
Il contenuto delle informazioni viene letto dalle richieste degli utenti.
Se il tipo di informazione specificato è valido, l'intestazione di risposta aggiornata deve includerlo. Se qualcosa va storto, la funzione deve restituire il dizionario di intestazioni originale senza alcuna modifica.

    Args:
        info_type (str): Il tipo di informazione da memorizzare nell'intestazione.
        info_content (str): Il contenuto dell'informazione da memorizzare nell'intestazione.
        header (Dict[str, str]): Il dizionario di intestazioni di risposta esistente.

    Returns:
        Dict[str, str]: Il dizionario di intestazioni di risposta aggiornato con le informazioni memorizzate.'''
    try:
        # Creare una copia dell'header per evitare modifiche in-place
        updated_header = header.copy()
        
        # Mappatura dei tipi di informazione alle chiavi dell'header
        type_mapping = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding', 
            'cache': 'Cache-Control'
        }
        
        # Verificare se il tipo di informazione è valido
        if info_type in type_mapping:
            # Ottenere la chiave dell'header corrispondente
            header_key = type_mapping[info_type]
            
            # Memorizzare il contenuto nell'header
            updated_header[header_key] = info_content
            
            return updated_header
        else:
            # Tipo di informazione non valido, restituire l'header originale
            return header
            
    except Exception:
        # In caso di qualsiasi errore, restituire l'header originale
        return header