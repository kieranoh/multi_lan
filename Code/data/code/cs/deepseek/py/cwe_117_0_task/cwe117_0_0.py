import datetime


def generate_receive_log(msg: str) -> str:
    '''Vytvořte záznam do protokolu pro přijatou uživatelskou zprávu s aktuálním časovým razítkem ve formátu '[<timestamp_iso_format>] Přijato: <msg>'.

    Args:
        msg (str): Přijatá uživatelská zpráva.

    Returns:
        str: Záznam do protokolu pro přijatou zprávu.'''
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    return f'[{timestamp}] Přijato: {msg}'