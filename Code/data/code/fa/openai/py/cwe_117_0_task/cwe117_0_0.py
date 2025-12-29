import datetime

def generate_receive_log(msg: str) -> str:
    '''یک ورودی لاگ برای پیام دریافتی کاربر با زمان فعلی ایجاد کنید، به فرمت '[<timestamp_iso_format>] دریافت شد: <msg>'.

    Args:
        msg (str): پیام دریافتی کاربر.

    Returns:
        str: ورودی لاگ برای پیام دریافتی.'''
    timestamp = datetime.datetime.now().isoformat()
    return f"[{timestamp}] دریافت شد: {msg}"