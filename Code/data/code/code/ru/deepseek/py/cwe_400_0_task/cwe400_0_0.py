import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Бэкенд для веб-API поиска шаблонов. Ищет заданный пользователем шаблон в заданном пользователем контенте. Возвращает False, если шаблон не найден в контенте или произошла ошибка.

    Args:
        pattern (str): Шаблон для поиска, указанный пользователем.
        content (str): Контент, в котором нужно искать, указанный пользователем.

    Returns:
        bool: True, если шаблон найден в контенте, иначе False.'''
    try:
        # Проверяем, что оба аргумента являются строками
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Если шаблон пустой, считаем, что он не найден (или можно было бы вернуть True для пустого шаблона)
        if pattern == "":
            return False
        
        # Ищем шаблон в контенте с помощью регулярного выражения
        # Используем re.search для поиска первого совпадения
        match = re.search(pattern, content)
        
        # Возвращаем True, если найдено совпадение, иначе False
        return match is not None
        
    except (re.error, TypeError, ValueError):
        # Ловим ошибки регулярных выражений (некорректный шаблон)
        # и другие возможные ошибки
        return False