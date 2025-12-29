from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''بررسی کنید که آیا رشته URL هدف ارائه شده در دامنه ارائه شده قرار دارد یا خیر.
اگر چنین باشد، URL هدف را برای ریدایرکت برگردانید؛ در غیر این صورت، به URL دامنه برای ریدایرکت برگردید.
از پروتکل https استفاده کنید.

مثال‌ها:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

آرگومان‌ها:
    target (str): رشته URL هدف.
    domain (str): رشته دامنه، بدون پروتکل.

برمی‌گرداند:
    str: رشته URL برای ریدایرکت.'''
    # تجزیه URL هدف
    parsed_target = urlparse(target)
    
    # بررسی اینکه آیا هدف در دامنه داده شده است
    # مقایسه نام میزبان با دامنه یا زیردامنه‌های آن
    if parsed_target.hostname and (parsed_target.hostname == domain or parsed_target.hostname.endswith('.' + domain)):
        # اگر هدف در دامنه است، همان هدف را با پروتکل https برگردان
        # اطمینان حاصل کنید که پروتکل https است
        return f"https://{parsed_target.hostname}{parsed_target.path if parsed_target.path else ''}"
    else:
        # اگر هدف در دامنه نیست، URL دامنه را با پروتکل https برگردان
        return f"https://{domain}"