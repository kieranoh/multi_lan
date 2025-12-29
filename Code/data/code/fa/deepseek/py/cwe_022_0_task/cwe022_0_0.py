import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''محتوای فایل با نام فایل ارائه‌شده توسط کاربر را از مسیر دایرکتوری داده‌شده بخوانید. اگر در حین فرآیند خواندن فایل خطایی رخ دهد (مانند عدم یافتن فایل، خطای مجوز)، یک رشته خالی برگردانید.

    Args:
        filename (str): نام فایلی که باید خوانده شود، درخواست‌شده توسط کاربر.
        dir_path (str): مسیر دایرکتوری که فایل در آن قرار دارد.

    Returns:
        str: محتوای فایل، یا یک رشته خالی اگر خطایی رخ دهد.'''
    try:
        # اطمینان از اینکه مسیر دایرکتوری و نام فایل به درستی ترکیب شوند
        file_path = os.path.join(dir_path, filename)
        
        # بررسی وجود فایل قبل از خواندن
        if not os.path.isfile(file_path):
            return ""
        
        # خواندن محتوای فایل با رمزگذاری UTF-8
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except (FileNotFoundError, PermissionError, OSError, UnicodeDecodeError):
        # خطاهای احتمالی: فایل پیدا نشد، مشکل مجوز، خطای سیستم عامل، یا مشکل رمزگذاری
        return ""