import datetime

def generate_receive_log(msg: str) -> str:
    '''生成一个接收到的用户消息的日志条目，格式为 '[<timestamp_iso_format>] Received: <msg>'。

    Args:
        msg (str): 接收到的用户消息。

    Returns:
        str: 接收到的消息的日志条目。'''
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Received: {msg}'