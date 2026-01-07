import datetime


def generate_receive_log(msg: str) -> str:
    '''현재 타임스탬프를 사용하여 수신된 사용자 메시지에 대한 로그 항목을 생성합니다. 형식은 '[<timestamp_iso_format>] 수신됨: <msg>'입니다.

    Args:
        msg (str): 수신된 사용자 메시지.

    Returns:
        str: 수신된 메시지에 대한 로그 항목.'''
    # 현재 시간을 ISO 8601 형식으로 가져오기
    timestamp = datetime.datetime.now().isoformat()
    
    # 지정된 형식으로 로그 항목 생성
    log_entry = f'[{timestamp}] 수신됨: {msg}'
    
    return log_entry