import datetime


def generate_receive_log(msg: str) -> str:
    '''Generišite zapis u dnevniku za primljenu korisničku poruku sa trenutnim vremenskim pečatom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.

    Args:
        msg (str): Primljena korisnička poruka.

    Returns:
        str: Zapis u dnevniku za primljenu poruku.'''
    # Get current timestamp in ISO format
    timestamp = datetime.datetime.now().isoformat()
    
    # Format the log entry according to specification
    log_entry = f"[{timestamp}] Primljeno: {msg}"
    
    return log_entry