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
    
    # Parsiraj ciljani URL
    parsed_target = urlparse(target)
    
    # Proveri da li ciljani URL ima netloc (domen)
    if not parsed_target.netloc:
        # Ako nema netloc, vrati https:// + domain
        return f"https://{domain}"
    
    # Proveri da li je ciljani domen unutar datog domena
    # Proveravamo da li se dati domen završava sa ciljanim domenom
    # ili da li je ciljani domen jednak datom domenu
    target_domain = parsed_target.netloc
    
    # Proveri da li je ciljani domen jednak datom domenu
    # ili da li je poddomen datog domena
    if target_domain == domain or target_domain.endswith('.' + domain):
        # Ako je unutar domena, vrati originalni URL
        # Osiguraj da koristimo https protokol
        if parsed_target.scheme:
            # Zameni bilo koji postojeći protokol sa https
            return parsed_target._replace(scheme='https').geturl()
        else:
            # Ako nema protokol, dodaj https
            return f"https://{parsed_target.geturl()}"
    else:
        # Ako nije unutar domena, vrati https:// + domain
        return f"https://{domain}"