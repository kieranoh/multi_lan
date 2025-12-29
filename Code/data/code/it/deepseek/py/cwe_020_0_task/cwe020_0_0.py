from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Controlla se la stringa dell'URL di destinazione fornita è all'interno del dominio fornito.
Se sì, restituisci l'URL di destinazione per il reindirizzamento; altrimenti, torna all'URL del dominio per il reindirizzamento.
Usa il protocollo https.

Esempi:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): La stringa dell'URL di destinazione.
    domain (str): La stringa del dominio, senza protocollo.

Returns:
    str: La stringa dell'URL per il reindirizzamento.'''
    try:
        # Parsa l'URL target
        parsed_target = urlparse(target)
        
        # Estrai l'hostname dal target
        target_hostname = parsed_target.hostname
        
        # Se l'hostname è None, il target non è un URL valido
        if target_hostname is None:
            return f"https://{domain}"
        
        # Controlla se il dominio è un suffisso dell'hostname
        # Usa endswith per gestire sia domini diretti che sottodomini
        if target_hostname == domain or target_hostname.endswith(f".{domain}"):
            # Se il target non ha protocollo, aggiungi https
            if not parsed_target.scheme:
                # Ricostruisci l'URL con https
                return f"https://{target_hostname}{parsed_target.path or ''}{'?' + parsed_target.query if parsed_target.query else ''}{'#' + parsed_target.fragment if parsed_target.fragment else ''}"
            else:
                # Se ha già un protocollo, assicurati che sia https
                if parsed_target.scheme != 'https':
                    # Sostituisci il protocollo con https
                    return f"https://{target_hostname}{parsed_target.path or ''}{'?' + parsed_target.query if parsed_target.query else ''}{'#' + parsed_target.fragment if parsed_target.fragment else ''}"
                else:
                    # Restituisci il target originale se già https
                    return target
        else:
            # Il target non è nel dominio specificato
            return f"https://{domain}"
            
    except Exception:
        # In caso di qualsiasi errore, restituisci il dominio di fallback
        return f"https://{domain}"