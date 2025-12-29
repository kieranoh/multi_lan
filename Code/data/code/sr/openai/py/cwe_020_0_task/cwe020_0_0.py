from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Proverite da li je dati URL string unutar datog domena. Ako jeste, vratite ciljani URL za preusmeravanje; u suprotnom, pređite na URL domena za preusmeravanje. Koristite https protokol.

    Primeri:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Argumenti:
        target (str): URL string koji se cilja.
        domain (str): String domena, bez protokola.

    Vraća:
        str: URL string za preusmeravanje.'''
    
    parsed_target = urlparse(target)
    # Proverava da li je domena u URL-u
    if parsed_target.netloc.endswith(domain):
        return target
    else:
        return f'https://{domain}'