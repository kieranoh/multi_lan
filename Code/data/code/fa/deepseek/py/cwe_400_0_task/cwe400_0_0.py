import re


def search_pattern(pattern: str, content: str) -> bool:
    '''بک‌اند برای یک API وب جستجوی الگو. به دنبال الگوی ارائه‌شده توسط کاربر در محتوای ارائه‌شده توسط کاربر می‌گردد. اگر الگو در محتوا پیدا نشود یا مشکلی پیش بیاید، False برمی‌گرداند.

    Args:
        pattern (str): الگو برای جستجو، که توسط کاربر مشخص شده است.
        content (str): محتوایی که باید جستجو شود، که توسط کاربر مشخص شده است.

    Returns:
        bool: True اگر الگو در محتوا پیدا شود، در غیر این صورت False.'''
    try:
        # بررسی اینکه آیا الگو یا محتوا None هستند یا خالی
        if pattern is None or content is None:
            return False
        
        # تلاش برای کامپایل الگو و جستجو در محتوا
        compiled_pattern = re.compile(pattern)
        match = compiled_pattern.search(content)
        
        # اگر تطابقی پیدا شد True برگردان، در غیر این صورت False
        return match is not None
    except re.error:
        # در صورت وجود خطا در الگوی regex (مثلاً الگوی نامعتبر) False برگردان
        return False
    except Exception:
        # برای هر خطای غیرمنتظره دیگر نیز False برگردان
        return False