import datetime

def generate_receive_log(msg: str) -> str:
    '''قم بإنشاء إدخال سجل لرسالة مستخدم مستلمة مع الطابع الزمني الحالي، بالتنسيق '[<timestamp_iso_format>] تم الاستلام: <msg>'.

    Args:
        msg (str): رسالة المستخدم المستلمة.

    Returns:
        str: إدخال السجل للرسالة المستلمة.'''
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] تم الاستلام: {msg}'