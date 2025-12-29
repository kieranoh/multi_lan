import datetime

def generate_receive_log(msg: str) -> str:
    '''Générez une entrée de journal pour un message utilisateur reçu avec l'horodatage actuel, au format '[<timestamp_iso_format>] Reçu : <msg>'.

    Args:
        msg (str): Le message utilisateur reçu.

    Returns:
        str: L'entrée de journal pour le message reçu.'''
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Reçu : {msg}'