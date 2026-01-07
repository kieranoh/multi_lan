import datetime


def generate_receive_log(msg: str) -> str:
    '''Genera una entrada de registro para un mensaje de usuario recibido con la marca de tiempo actual, en el formato '[<timestamp_iso_format>] Recibido: <msg>'.

    Args:
        msg (str): El mensaje de usuario recibido.

    Returns:
        str: La entrada de registro para el mensaje recibido.'''
    timestamp = datetime.datetime.now().isoformat()
    return f"[{timestamp}] Recibido: {msg}"