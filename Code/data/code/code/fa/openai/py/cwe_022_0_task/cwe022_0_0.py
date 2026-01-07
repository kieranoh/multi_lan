import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''محتوای فایل با نام فایل ارائه‌شده توسط کاربر را از مسیر دایرکتوری داده‌شده بخوانید. اگر در حین فرآیند خواندن فایل خطایی رخ دهد (مانند عدم یافتن فایل، خطای مجوز)، یک رشته خالی برگردانید.

    Args:
        filename (str): نام فایلی که باید خوانده شود، درخواست‌شده توسط کاربر.
        dir_path (str): مسیر دایرکتوری که فایل در آن قرار دارد.

    Returns:
        str: محتوای فایل، یا یک رشته خالی اگر خطایی رخ دهد.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except (FileNotFoundError, PermissionError):
        return ''