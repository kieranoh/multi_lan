import re
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
    # Adiciona o protocolo https se não estiver presente na URL de destino
    if not target.startswith(('http://', 'https://')):
        target = 'https://' + target
    
    # Parse a URL de destino
    parsed_target = urlparse(target)
    
    # Extrai o domínio da URL de destino (hostname)
    target_domain = parsed_target.hostname
    
    if target_domain is None:
        # Se não houver hostname, retorna o domínio fornecido com https
        return f'https://{domain}'
    
    # Verifica se o domínio de destino termina com o domínio fornecido
    # Usa uma verificação mais robusta para evitar correspondências parciais
    # Exemplo: 'example.com' deve corresponder a 'example.com' e 'sub.example.com'
    # mas não a 'anotherexample.com'
    if target_domain == domain or target_domain.endswith('.' + domain):
        # Se o domínio corresponder, retorna a URL de destino com https
        # Garante que o protocolo seja https
        return f'https://{target_domain}{parsed_target.path or ""}{"?" + parsed_target.query if parsed_target.query else ""}{"#" + parsed_target.fragment if parsed_target.fragment else ""}'
    else:
        # Se não corresponder, retorna o domínio fornecido com https
        return f'https://{domain}'