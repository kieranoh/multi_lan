import datetime

def generate_receive_log(msg: str) -> str:
    '''Wygeneruj wpis dziennika dla odebranej wiadomości użytkownika z aktualnym znacznikiem czasu, w formacie '[<timestamp_iso_format>] Odebrano: <msg>'.

    Args:
        msg (str): Odebrana wiadomość użytkownika.

    Returns:
        str: Wpis dziennika dla odebranej wiadomości.'''
    timestamp = datetime.datetime.now().isoformat()
    log_entry = f'[{timestamp}] Odebrano: {msg}'
    return log_entry