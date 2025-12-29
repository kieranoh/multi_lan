import datetime

def generate_receive_log(msg: str) -> str:
    '''Сгенерировать запись в журнале для полученного сообщения пользователя с текущей меткой времени в формате '[<timestamp_iso_format>] Получено: <msg>'.

    Args:
        msg (str): Полученное сообщение пользователя.

    Returns:
        str: Запись в журнале для полученного сообщения.'''
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Получено: {msg}'