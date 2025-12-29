def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Сгенерируйте URL для запроса информации о пользователе на основе данного API URL и идентификатора пользователя. Ожидаемый URL для запроса должен быть API URL, конкатенированным с идентификатором пользователя. Если идентификатор пользователя пустой или недействительный, функция должна вернуть None, чтобы запрос не был выполнен.
    Примеры:
    - get_url_for_query('https://example.com/api/user', 'aBc123') возвращает 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') возвращает None

    Аргументы:
        api_url: API URL для запроса информации о пользователе.
        user_id: Идентификатор пользователя для запроса.

    Возвращает:
        str | None: URL для запроса."""
    # Проверяем, что user_id не пустой и не состоит только из пробелов
    if not user_id or not user_id.strip():
        return None
    
    # Удаляем возможные пробелы в начале и конце
    user_id = user_id.strip()
    
    # Убедимся, что api_url не заканчивается на '/', чтобы избежать двойных слешей
    api_url = api_url.rstrip('/')
    
    # Формируем URL
    return f"{api_url}/{user_id}"