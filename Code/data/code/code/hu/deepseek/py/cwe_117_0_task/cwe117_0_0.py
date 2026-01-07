import datetime

def generate_receive_log(msg: str) -> str:
    '''Generálj egy naplóbejegyzést egy beérkezett felhasználói üzenetről a jelenlegi időbélyeggel, a következő formátumban: '[<timestamp_iso_format>] Received: <msg>'.

    Args:
        msg (str): A beérkezett felhasználói üzenet.

    Returns:
        str: A beérkezett üzenet naplóbejegyzése.'''
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    return f'[{timestamp}] Received: {msg}'