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

    # بررسی اینکه آیا URL هدف شامل دامنه است یا خیر
    if target.startswith("https://") and domain in target:
        return target
    else:
        return f"https://{domain}"