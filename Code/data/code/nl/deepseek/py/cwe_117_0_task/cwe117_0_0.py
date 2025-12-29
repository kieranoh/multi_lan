import datetime

def generate_receive_log(msg: str) -> str:
    '''Genereer een logboekvermelding voor een ontvangen gebruikersbericht met de huidige tijdstempel, in het formaat '[<timestamp_iso_format>] Ontvangen: <msg>'.

    Args:
        msg (str): Het ontvangen gebruikersbericht.

    Returns:
        str: De logboekvermelding voor het ontvangen bericht.'''
    # Genereer huidige tijdstempel in ISO 8601 formaat
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    
    # Formatteer de logboekvermelding volgens het gespecificeerde formaat
    log_entry = f'[{timestamp}] Ontvangen: {msg}'
    
    return log_entry