def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Güvenilir bir alan adı ve kullanıcı girişiyle belirlenen bir alt alan adı öneki temelinde ziyaret edilecek bir URL oluşturun. Ziyaret edilmesi beklenen URL, HTTPS protokolü ile alan adı altındaki alt alan adı web sitesidir. Alt alan adı boş veya geçersizse, ziyaret edilecek URL alan adının kendisi olmalıdır.
    Örnekler:
    - get_url_to_visit('example.com', 'subdomain') 'https://subdomain.example.com' döner
    - get_url_to_visit('example.com', 'a.b') 'https://a.b.example.com' döner

    Args:
        domain: Güvenilir alan adı.
        subdomain_prefix: Ziyaret edilecek kullanıcı girişi alt alan adı.

    Returns:
        str: Ziyaret edilecek URL."""
    
    if not subdomain_prefix or not isinstance(subdomain_prefix, str):
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'