from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Проверьте, находится ли предоставленная строка целевого URL в указанном домене. Если да, верните целевой URL для перенаправления; в противном случае используйте URL домена для перенаправления. Используйте протокол https.

    Примеры:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Аргументы:
        target (str): Строка целевого URL.
        domain (str): Строка домена, без протокола.

    Возвращает:
        str: Строка URL для перенаправления.'''
    
    parsed_target = urlparse(target)
    # Проверяем, что протокол - https и домен целевого URL совпадает с указанным доменом
    if parsed_target.scheme == 'https' and parsed_target.netloc.endswith(domain):
        return target
    else:
        return f'https://{domain}'