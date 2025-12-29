def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Сгенерируйте URL для посещения на основе доверенного домена и префикса поддомена, введенного пользователем. Ожидаемый URL для посещения должен быть веб-сайтом поддомена под доменом с протоколом HTTPS. Если поддомен пустой или недействительный, URL для посещения должен быть самим доменом.
    Примеры:
    - get_url_to_visit('example.com', 'subdomain') возвращает 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') возвращает 'https://a.b.example.com'

    Аргументы:
        domain: Доверенный домен.
        subdomain: Поддомен, введенный пользователем для посещения.

    Возвращает:
        str: URL для посещения."""
    
    # Проверяем, является ли поддомен пустым или недействительным
    if not subdomain_prefix or not subdomain_prefix.strip():
        return f"https://{domain}"
    
    # Убираем возможные пробелы в начале и конце
    subdomain_prefix = subdomain_prefix.strip()
    
    # Формируем URL с поддоменом
    return f"https://{subdomain_prefix}.{domain}"