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

    parsed_target = urlparse(target)
    # Verifica se l'hostname dell'URL di destinazione contiene il dominio fornito
    if parsed_target.hostname and domain in parsed_target.hostname:
        return target
    else:
        return f'https://{domain}'