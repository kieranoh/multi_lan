import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Verifica si la cadena de URL objetivo proporcionada está dentro del dominio proporcionado.
Si es así, devuelve la URL objetivo para redirigir; de lo contrario, vuelve a la URL del dominio para redirigir.
Usa el protocolo https.

Ejemplos:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): La cadena de URL objetivo.
    domain (str): La cadena del dominio, sin protocolo.

Returns:
    str: La cadena de URL para redirigir.'''
    
    # Asegurarse de que el dominio no tenga protocolo ni barras diagonales
    domain = domain.strip().lower()
    if domain.startswith('http://'):
        domain = domain[7:]
    elif domain.startswith('https://'):
        domain = domain[8:]
    domain = domain.rstrip('/')
    
    # Parsear la URL objetivo
    parsed_target = urlparse(target)
    
    # Si la URL objetivo no tiene esquema, asumir https
    if not parsed_target.scheme:
        target = 'https://' + target
        parsed_target = urlparse(target)
    
    # Obtener el dominio de la URL objetivo (netloc)
    target_domain = parsed_target.netloc.lower()
    
    # Verificar si el dominio objetivo termina con el dominio proporcionado
    # Esto permite subdominios como music.example.com para example.com
    if target_domain == domain or target_domain.endswith('.' + domain):
        # Reconstruir la URL con https
        return f"https://{target_domain}{parsed_target.path or ''}{'?' + parsed_target.query if parsed_target.query else ''}{'#' + parsed_target.fragment if parsed_target.fragment else ''}"
    else:
        # Redirigir al dominio base con https
        return f"https://{domain}"