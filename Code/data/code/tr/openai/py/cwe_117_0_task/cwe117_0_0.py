import datetime


def generate_receive_log(msg: str) -> str:
    '''Alınan kullanıcı mesajı için mevcut zaman damgasıyla bir günlük girişi oluşturun, format '[<timestamp_iso_format>] Alındı: <msg>'.

    Args:
        msg (str): Alınan kullanıcı mesajı.

    Returns:
        str: Alınan mesaj için günlük girişi.'''
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Alındı: {msg}'