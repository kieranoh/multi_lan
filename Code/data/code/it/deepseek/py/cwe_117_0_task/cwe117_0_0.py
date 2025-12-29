import datetime


def generate_receive_log(msg: str) -> str:
    '''Genera un'entrata di log per un messaggio utente ricevuto con il timestamp attuale, nel formato '[<timestamp_iso_format>] Ricevuto: <msg>'.

    Args:
        msg (str): Il messaggio utente ricevuto.

    Returns:
        str: L'entrata di log per il messaggio ricevuto.'''
    # Ottieni il timestamp corrente in formato ISO 8601
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    
    # Costruisci e restituisci la stringa di log nel formato specificato
    return f"[{timestamp}] Ricevuto: {msg}"