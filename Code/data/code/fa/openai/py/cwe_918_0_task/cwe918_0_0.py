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
    
    if not subdomain_prefix or any(char not in 'abcdefghijklmnopqrstuvwxyz0123456789.-_' for char in subdomain_prefix):
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'