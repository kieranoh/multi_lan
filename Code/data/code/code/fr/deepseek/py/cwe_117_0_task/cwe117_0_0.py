import datetime


def generate_receive_log(msg: str) -> str:
    '''Générez une entrée de journal pour un message utilisateur reçu avec l'horodatage actuel, au format '[<timestamp_iso_format>] Reçu : <msg>'.

    Args:
        msg (str): Le message utilisateur reçu.

    Returns:
        str: L'entrée de journal pour le message reçu.'''
    # Obtenir l'horodatage actuel au format ISO 8601
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    # Construire et retourner l'entrée de journal formatée
    return f'[{timestamp}] Reçu : {msg}'