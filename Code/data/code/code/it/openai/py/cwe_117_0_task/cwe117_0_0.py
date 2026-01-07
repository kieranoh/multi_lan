import datetime

def generate_receive_log(msg: str) -> str:
    '''Genera un'entrata di log per un messaggio utente ricevuto con il timestamp attuale, nel formato '[<timestamp_iso_format>] Ricevuto: <msg>'.

    Args:
        msg (str): Il messaggio utente ricevuto.

    Returns:
        str: L'entrata di log per il messaggio ricevuto.'''
    
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Ricevuto: {msg}'