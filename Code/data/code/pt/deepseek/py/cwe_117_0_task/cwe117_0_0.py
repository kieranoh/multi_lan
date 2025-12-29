import datetime


def generate_receive_log(msg: str) -> str:
    '''Gere uma entrada de log para uma mensagem de usuário recebida com o timestamp atual, no formato '[<timestamp_iso_format>] Recebido: <msg>'.

    Args:
        msg (str): A mensagem do usuário recebida.

    Returns:
        str: A entrada de log para a mensagem recebida.'''
    # Obtém o timestamp atual no formato ISO 8601
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    
    # Formata a string de log conforme especificado
    log_entry = f"[{timestamp}] Recebido: {msg}"
    
    return log_entry