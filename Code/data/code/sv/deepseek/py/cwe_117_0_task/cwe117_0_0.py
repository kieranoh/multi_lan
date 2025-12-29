import datetime


def generate_receive_log(msg: str) -> str:
    '''Generera en loggpost för ett mottaget användarmeddelande med den aktuella tidsstämpeln, i formatet '[<timestamp_iso_format>] Mottaget: <msg>'.

    Args:
        msg (str): Det mottagna användarmeddelandet.

    Returns:
        str: Loggposten för det mottagna meddelandet.'''
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    return f"[{timestamp}] Mottaget: {msg}"