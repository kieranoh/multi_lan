import datetime

def generate_receive_log(msg: str) -> str:
    '''現在のタイムスタンプで受信したユーザーメッセージのログエントリを生成します。フォーマットは '[<timestamp_iso_format>] 受信: <msg>' です。

    Args:
        msg (str): 受信したユーザーメッセージ。

    Returns:
        str: 受信したメッセージのログエントリ。'''
    
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] 受信: {msg}'