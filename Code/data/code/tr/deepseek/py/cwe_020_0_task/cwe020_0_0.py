import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Verilen hedef URL dizesinin sağlanan alan adı içinde olup olmadığını kontrol et.
Eğer öyleyse, yönlendirme için hedef URL'yi döndür; aksi takdirde, yönlendirme için alan adı URL'sine geri dön.
https protokolünü kullan.

Örnekler:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): Hedef URL dizesi.
    domain (str): Protokol olmadan alan adı dizesi.

Returns:
    str: Yönlendirme için URL dizesi.'''
    
    # Önce target'ın geçerli bir URL olup olmadığını kontrol et
    try:
        parsed_target = urlparse(target)
    except Exception:
        # Geçersiz URL durumunda domain'e yönlendir
        return f"https://{domain}"
    
    # Eğer target'da scheme yoksa, https ekleyerek parse etmeyi dene
    if not parsed_target.scheme:
        try:
            parsed_target = urlparse(f"https://{target}")
        except Exception:
            return f"https://{domain}"
    
    # Domain'i normalize et (başındaki ve sonundaki boşlukları temizle)
    domain = domain.strip()
    
    # Hedefin domain kısmını al
    target_domain = parsed_target.netloc
    
    # Eğer target_domain boşsa, domain'e yönlendir
    if not target_domain:
        return f"https://{domain}"
    
    # Domain eşleşmesini kontrol et
    # Ana domain ile tam eşleşme veya subdomain olma durumunu kontrol et
    if target_domain == domain or target_domain.endswith(f".{domain}"):
        # Orijinal target'ı döndür, ancak scheme yoksa https ekle
        if parsed_target.scheme:
            # Orijinal target'ı olduğu gibi döndür
            return target
        else:
            # Scheme yoksa https ekleyerek döndür
            return f"https://{target}"
    else:
        # Domain eşleşmiyorsa, ana domain'e yönlendir
        return f"https://{domain}"