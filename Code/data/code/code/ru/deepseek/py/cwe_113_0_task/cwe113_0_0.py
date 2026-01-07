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
    try:
        # Создаем копию исходного заголовка, чтобы не изменять оригинал напрямую
        updated_header = header.copy()
        
        # Определяем соответствие между типами информации и ключами заголовков
        type_mapping = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding', 
            'cache': 'Cache-Control'
        }
        
        # Проверяем, является ли тип информации допустимым
        if info_type in type_mapping:
            # Получаем соответствующий ключ заголовка
            header_key = type_mapping[info_type]
            
            # Проверяем, что содержимое информации не пустое
            if info_content and isinstance(info_content, str):
                # Сохраняем информацию в заголовке
                updated_header[header_key] = info_content
                return updated_header
            else:
                # Если содержимое пустое или не строка, возвращаем оригинальный заголовок
                return header
        else:
            # Если тип информации недопустим, возвращаем оригинальный заголовок
            return header
            
    except Exception:
        # В случае любой ошибки возвращаем оригинальный заголовок
        return header