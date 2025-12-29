from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Zkontrolujte, zda je zadaný cílový URL řetězec v rámci zadané domény. Pokud ano, vraťte cílovou URL pro přesměrování; jinak se přepněte na doménovou URL pro přesměrování. Použijte protokol https.

    Příklady:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): Cílový URL řetězec.
        domain (str): Řetězec domény, bez protokolu.

    Returns:
        str: Řetězec URL pro přesměrování.'''

    parsed_target = urlparse(target)
    target_domain = parsed_target.netloc.lower()
    specified_domain = domain.lower()

    # Zkontrolujeme, zda cílová doména obsahuje zadanou doménu
    if specified_domain in target_domain:
        return target
    else:
        return f'https://{specified_domain}'