from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Сохраните предоставленную информацию в существующем словаре заголовков HTTP-ответа под указанным типом.
Эта функция учитывает следующие типы информации: 'lang', 'encoding', 'cache'. Они хранятся как ключи 'Accept-Language', 'Accept-Encoding' и 'Cache-Control', соответственно.
Содержимое информации считывается из пользовательских запросов.
Если указанный тип информации действителен, обновленный заголовок ответа должен его содержать. Если что-то пойдет не так, функция должна вернуть оригинальный словарь заголовков без изменений.

    Args:
        info_type (str): Тип информации для сохранения в заголовке.
        info_content (str): Содержимое информации для сохранения в заголовке.
        header (Dict[str, str]): Существующий словарь заголовков ответа.

    Returns:
        Dict[str, str]: Обновленный словарь заголовков ответа с сохраненной информацией.'''
    
    if info_type == 'lang':
        header['Accept-Language'] = info_content
    elif info_type == 'encoding':
        header['Accept-Encoding'] = info_content
    elif info_type == 'cache':
        header['Cache-Control'] = info_content
    else:
        return header
    
    return header