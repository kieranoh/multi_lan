import datetime


def generate_receive_log(msg: str) -> str:
    '''Genera una entrada de registre per a un missatge d'usuari rebut amb la marca de temps actual, en el format '[<timestamp_iso_format>] Rebut: <msg>'.

    Args:
        msg (str): El missatge d'usuari rebut.

    Returns:
        str: L'entrada de registre per al missatge rebut.'''
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    return f'[{timestamp}] Rebut: {msg}'