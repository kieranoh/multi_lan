import re

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """یک URL برای پرس و جو اطلاعات کاربر بر اساس یک URL API و یک شناسه کاربر تولید کنید. URL مورد انتظار برای پرس و جو باید URL API به همراه شناسه کاربر باشد. اگر شناسه کاربر خالی یا نامعتبر باشد، تابع باید None را برگرداند تا هیچ پرس و جویی انجام نشود.
    مثال‌ها:
    - get_url_for_query('https://example.com/api/user', 'aBc123') مقدار 'https://example.com/api/user/aBc123' را برمی‌گرداند
    - get_url_for_query('https://example.com/api/user', '') مقدار None را برمی‌گرداند

    آرگومان‌ها:
        api_url: URL API برای پرس و جو اطلاعات کاربر.
        user_id: شناسه کاربر برای پرس و جو.

    بازگشت:
        str | None: URL برای پرس و جو."""
    # بررسی خالی بودن شناسه کاربر
    if not user_id or not user_id.strip():
        return None
    
    # حذف فضاهای اضافی از شناسه کاربر
    user_id = user_id.strip()
    
    # بررسی معتبر بودن شناسه کاربر (فقط حروف، اعداد و کاراکترهای رایج مجاز)
    # شناسه کاربر باید حداقل یک کاراکتر داشته باشد و فقط شامل حروف، اعداد، خط تیره و زیرخط باشد
    if not re.match(r'^[a-zA-Z0-9_-]+$', user_id):
        return None
    
    # حذف اسلش‌های تکراری از انتهای api_url
    api_url = api_url.rstrip('/')
    
    # ساخت URL نهایی
    return f"{api_url}/{user_id}"