import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Бэкенд для веб-API поиска шаблонов. Ищет заданный пользователем шаблон в заданном пользователем контенте. Возвращает False, если шаблон не найден в контенте или произошла ошибка.

    Args:
        pattern (str): Шаблон для поиска, указанный пользователем.
        content (str): Контент, в котором нужно искать, указанный пользователем.

    Returns:
        bool: True, если шаблон найден в контенте, иначе False.'''
    try:
        if re.search(pattern, content):
            return True
        return False
    except re.error:
        return False