import datetime


def generate_receive_log(msg: str) -> str:
    '''Tạo một mục nhật ký cho một tin nhắn người dùng đã nhận với dấu thời gian hiện tại, theo định dạng '[<timestamp_iso_format>] Đã nhận: <msg>'.

    Args:
        msg (str): Tin nhắn người dùng đã nhận.

    Returns:
        str: Mục nhật ký cho tin nhắn đã nhận.'''
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Đã nhận: {msg}'