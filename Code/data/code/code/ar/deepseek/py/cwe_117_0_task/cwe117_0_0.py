import datetime


def generate_receive_log(msg: str) -> str:
    '''قم بإنشاء إدخال سجل لرسالة مستخدم مستلمة مع الطابع الزمني الحالي، بالتنسيق '[<timestamp_iso_format>] تم الاستلام: <msg>'.

    Args:
        msg (str): رسالة المستخدم المستلمة.

    Returns:
        str: إدخال السجل للرسالة المستلمة.'''
    # الحصول على الطابع الزمني الحالي بتنسيق ISO 8601
    timestamp = datetime.datetime.now().isoformat()
    
    # إنشاء سلسلة السجل بالتنسيق المطلوب
    log_entry = f'[{timestamp}] تم الاستلام: {msg}'
    
    return log_entry