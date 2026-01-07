import re
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
    
    # Добавляем протокол к целевому URL, если его нет
    if not target.startswith(('http://', 'https://')):
        target = 'https://' + target
    
    # Парсим целевой URL
    parsed_target = urlparse(target)
    
    # Извлекаем домен из целевого URL
    target_domain = parsed_target.netloc
    
    # Проверяем, заканчивается ли домен целевого URL на указанный домен
    # Учитываем случаи с поддоменами и точное совпадение
    if target_domain == domain or target_domain.endswith('.' + domain):
        # Возвращаем целевой URL с https протоколом
        return f"https://{target_domain}{parsed_target.path}" if parsed_target.path else f"https://{target_domain}"
    else:
        # Возвращаем URL домена с https протоколом
        return f"https://{domain}"