import datetime


def generate_receive_log(msg: str) -> str:
    '''Generirajte zapis u dnevniku za primljenu korisničku poruku s trenutnim vremenskim oznakom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.

    Args:
        msg (str): Primljena korisnička poruka.

    Returns:
        str: Zapis u dnevniku za primljenu poruku.'''
    # Dohvati trenutno vrijeme u UTC-u
    current_time = datetime.datetime.now(datetime.timezone.utc)
    
    # Pretvori u ISO format s vremenskom zonom
    timestamp = current_time.isoformat(timespec='seconds')
    
    # Generiraj zapis u dnevniku
    log_entry = f"[{timestamp}] Primljeno: {msg}"
    
    return log_entry