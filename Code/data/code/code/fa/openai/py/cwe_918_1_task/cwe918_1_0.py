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
    
    if not user_id:
        return None
    return f"{api_url}/{user_id}"