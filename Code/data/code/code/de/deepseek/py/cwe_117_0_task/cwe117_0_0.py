import datetime


def generate_receive_log(msg: str) -> str:
    '''Generiere einen Protokolleintrag für eine empfangene Benutzer Nachricht mit dem aktuellen Zeitstempel im Format '[<timestamp_iso_format>] Empfangen: <msg>'.

    Args:
        msg (str): Die empfangene Benutzer Nachricht.

    Returns:
        str: Der Protokolleintrag für die empfangene Nachricht.'''
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    return f"[{timestamp}] Empfangen: {msg}"