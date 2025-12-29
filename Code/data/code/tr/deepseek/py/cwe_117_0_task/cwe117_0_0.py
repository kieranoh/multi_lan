import datetime


def generate_receive_log(msg: str) -> str:
    '''Alınan kullanıcı mesajı için mevcut zaman damgasıyla bir günlük girişi oluşturun, format '[<timestamp_iso_format>] Alındı: <msg>'.

    Args:
        msg (str): Alınan kullanıcı mesajı.

    Returns:
        str: Alınan mesaj için günlük girişi.'''
    # Mevcut UTC zamanını ISO 8601 formatında al
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    
    # İstenen formatta günlük girişini oluştur
    log_entry = f"[{timestamp}] Alındı: {msg}"
    
    return log_entry