import re

def search_pattern(pattern: str, content: str) -> bool:
    '''بک‌اند برای یک API وب جستجوی الگو. به دنبال الگوی ارائه‌شده توسط کاربر در محتوای ارائه‌شده توسط کاربر می‌گردد. اگر الگو در محتوا پیدا نشود یا مشکلی پیش بیاید، False برمی‌گرداند.

    Args:
        pattern (str): الگو برای جستجو، که توسط کاربر مشخص شده است.
        content (str): محتوایی که باید جستجو شود، که توسط کاربر مشخص شده است.

    Returns:
        bool: True اگر الگو در محتوا پیدا شود، در غیر این صورت False.'''
    try:
        return re.search(pattern, content) is not None
    except re.error:
        return False