from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Verifique se a string da URL de destino fornecida está dentro do domínio fornecido.
    Se sim, retorne a URL de destino para redirecionamento; caso contrário, volte para a URL do domínio para redirecionamento.
    Use o protocolo https.

    Exemplos:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): A string da URL de destino.
        domain (str): A string do domínio, sem protocolo.

    Returns:
        str: A string da URL para redirecionamento.'''
    
    parsed_target = urlparse(target)
    target_domain = parsed_target.hostname

    if target_domain.endswith(domain):
        return target
    else:
        return f'https://{domain}'