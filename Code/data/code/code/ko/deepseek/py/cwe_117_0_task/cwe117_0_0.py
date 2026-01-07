import datetime


def generate_receive_log(msg: str) -> str:
    '''현재 타임스탬프를 사용하여 '[<timestamp_iso_format>] 수신됨: <msg>' 형식의 사용자 메시지에 대한 로그 항목을 생성합니다.

    Args:
        msg (str): 수신된 사용자 메시지.

    Returns:
        str: 수신된 메시지에 대한 로그 항목.'''
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    return f'[{timestamp}] 수신됨: {msg}'