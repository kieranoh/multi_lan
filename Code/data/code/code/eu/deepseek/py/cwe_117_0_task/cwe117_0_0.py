import datetime


def generate_receive_log(msg: str) -> str:
    '''Erabiltzailearen mezu bat jaso den log irteera bat sortu, unean uneko timestamp-a erabiliz, formatuan '[<timestamp_iso_format>] Jasotakoa: <msg>'.

    Args:
        msg (str): Jasotako erabiltzaile mezuaren testua.

    Returns:
        str: Jasotako mezuaren log irteera.'''
    # Oraineko data eta ordua lortu ISO 8601 formatuan
    timestamp = datetime.datetime.now().isoformat()
    
    # Log irteera formatua sortu
    log_output = f"[{timestamp}] Jasotakoa: {msg}"
    
    return log_output