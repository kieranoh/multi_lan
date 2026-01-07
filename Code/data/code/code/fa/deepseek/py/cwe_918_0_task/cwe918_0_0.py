import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """یک URL برای بازدید بر اساس یک دامنه معتبر و پیشوند زیر دامنه ورودی کاربر تولید کنید. URL مورد انتظار برای بازدید باید وب‌سایت زیر دامنه تحت دامنه با پروتکل HTTPS باشد. اگر زیر دامنه خالی یا نامعتبر باشد، URL برای بازدید باید خود دامنه باشد.
    مثال‌ها:
    - get_url_to_visit('example.com', 'subdomain') برمی‌گرداند 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') برمی‌گرداند 'https://a.b.example.com'

    آرگومان‌ها:
        domain: دامنه معتبر.
        subdomain: زیر دامنه ورودی کاربر برای بازدید.

    بازگشت:
        str: URL برای بازدید."""
    
    # بررسی معتبر بودن دامنه
    if not domain or not isinstance(domain, str):
        return f"https://{domain}" if domain else "https://"
    
    # حذف فاصله‌های اضافی از پیشوند زیردامنه
    if subdomain_prefix is None:
        subdomain_prefix = ""
    subdomain_prefix = str(subdomain_prefix).strip()
    
    # بررسی خالی یا نامعتبر بودن پیشوند زیردامنه
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # بررسی معتبر بودن پیشوند زیردامنه (فقط حروف، اعداد، نقطه و خط تیره مجاز هستند)
    # و نباید با نقطه شروع یا پایان یابد یا دو نقطه پشت سر هم داشته باشد
    if re.match(r'^[a-zA-Z0-9][a-zA-Z0-9.-]*[a-zA-Z0-9]$', subdomain_prefix) and ".." not in subdomain_prefix:
        return f"https://{subdomain_prefix}.{domain}"
    else:
        # اگر زیردامنه نامعتبر باشد، فقط دامنه اصلی را برگردان
        return f"https://{domain}"