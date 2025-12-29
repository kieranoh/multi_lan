import re

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
    
    # Domain ve subdomain_prefix'in string tipinde olduğundan emin ol
    if not isinstance(domain, str) or not isinstance(subdomain_prefix, str):
        return f"https://{domain}"
    
    # Domain'i temizle: baştaki ve sondaki boşlukları kaldır
    domain = domain.strip()
    
    # Domain boşsa veya sadece boşluklardan oluşuyorsa, geçersiz olduğu için boş string döndür
    if not domain:
        return ""
    
    # Subdomain_prefix'i temizle: baştaki ve sondaki boşlukları kaldır
    subdomain_prefix = subdomain_prefix.strip()
    
    # Subdomain_prefix boşsa veya sadece noktalardan/boşluklardan oluşuyorsa, sadece domain'i kullan
    if not subdomain_prefix or subdomain_prefix.replace('.', '').strip() == '':
        return f"https://{domain}"
    
    # Subdomain geçerliliğini kontrol et: sadece harf, rakam, tire ve nokta içermeli
    # Ayrıca başta veya sonda tire veya nokta olmamalı, içinde ardışık noktalar olmamalı
    subdomain_pattern = r'^[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?)*$'
    
    if not re.match(subdomain_pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # URL'yi oluştur
    return f"https://{subdomain_prefix}.{domain}"