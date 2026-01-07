import datetime

def generate_receive_log(msg: str) -> str:
    '''Luo lokimerkintä vastaanotetulle käyttäjäviestille nykyisellä aikaleimalla muodossa '[<timestamp_iso_format>] Vastaanotettu: <msg>'.

    Args:
        msg (str): Vastaanotettu käyttäjäviesti.

    Returns:
        str: Lokimerkintä vastaanotetulle viestille.'''
    
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Vastaanotettu: {msg}'