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
    
    from urllib.parse import urlparse

    parsed_target = urlparse(target)
    target_domain = parsed_target.hostname

    if target_domain.endswith(domain):
        return target
    else:
        return f'https://{domain}'