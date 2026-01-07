import datetime


def generate_receive_log(msg: str) -> str:
    '''Genereer een logboekvermelding voor een ontvangen gebruikersbericht met de huidige tijdstempel, in het formaat '[<timestamp_iso_format>] Ontvangen: <msg>'.

    Args:
        msg (str): Het ontvangen gebruikersbericht.

    Returns:
        str: De logboekvermelding voor het ontvangen bericht.'''
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Ontvangen: {msg}'