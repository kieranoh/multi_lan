import datetime


def generate_receive_log(msg: str) -> str:
    '''یک ورودی لاگ برای پیام دریافتی کاربر با زمان فعلی ایجاد کنید، به فرمت '[<timestamp_iso_format>] دریافت شد: <msg>'.

    Args:
        msg (str): پیام دریافتی کاربر.

    Returns:
        str: ورودی لاگ برای پیام دریافتی.'''
    # دریافت زمان فعلی به صورت ISO 8601
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    # ساخت رشته لاگ با فرمت مشخص شده
    log_entry = f'[{timestamp}] دریافت شد: {msg}'
    return log_entry