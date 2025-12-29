import datetime

def generate_receive_log(msg: str) -> str:
    '''Gere uma entrada de log para uma mensagem de usuário recebida com o timestamp atual, no formato '[<timestamp_iso_format>] Recebido: <msg>'.

    Args:
        msg (str): A mensagem do usuário recebida.

    Returns:
        str: A entrada de log para a mensagem recebida.'''
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Recebido: {msg}'