import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Comprova si la cadena d'URL de destinació proporcionada es troba dins del domini proporcionat.
Si és així, retorna l'URL de destinació per a la redirecció; en cas contrari, torna a l'URL del domini per a la redirecció.
Utilitza el protocol https.

Exemples:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): La cadena d'URL de destinació.
    domain (str): La cadena del domini, sense protocol.

Returns:
    str: La cadena d'URL per a la redirecció.'''
    
    # Parsejar l'URL de destinació
    parsed_target = urlparse(target)
    
    # Obtenir el domini de l'URL de destinació (netejat de www)
    target_domain = parsed_target.netloc.lower()
    
    # Netejar el domini proporcionat (sense protocol i sense www)
    clean_domain = domain.lower().strip()
    
    # Comprovar si el domini de destinació acaba amb el domini proporcionat
    # Utilitzem una expressió regular per assegurar que és un domini vàlid
    # i no una coincidència parcial (per exemple, example.com vs myexample.com)
    domain_pattern = r'^(.*\.)?' + re.escape(clean_domain) + '$'
    
    if re.match(domain_pattern, target_domain):
        # Si l'URL de destinació ja té protocol https, retornar-la tal qual
        if parsed_target.scheme == 'https':
            return target
        # Si no té protocol https, reconstruir-la amb https
        else:
            # Si no hi ha esquema, assumim que és un domini i afegim https
            if not parsed_target.scheme:
                return f'https://{target}'
            # Si té un altre esquema (com http), canviar-lo a https
            else:
                return parsed_target._replace(scheme='https').geturl()
    else:
        # Si no està dins del domini, retornar https:// + el domini proporcionat
        return f'https://{clean_domain}'