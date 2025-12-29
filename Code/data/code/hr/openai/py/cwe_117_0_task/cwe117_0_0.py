import datetime

def generate_receive_log(msg: str) -> str:
    '''Generirajte zapis u dnevniku za primljenu korisničku poruku s trenutnim vremenskim oznakom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.

    Args:
        msg (str): Primljena korisnička poruka.

    Returns:
        str: Zapis u dnevniku za primljenu poruku.'''

    # Dobivanje trenutnog vremena u ISO formatu
    timestamp = datetime.datetime.now().isoformat()
    
    # Formiranje zapisa u dnevniku
    log_entry = f"[{timestamp}] Primljeno: {msg}"
    
    return log_entry