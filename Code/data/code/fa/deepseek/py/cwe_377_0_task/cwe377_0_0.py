from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """یک فایل موقت ایجاد کنید، محتوای `results` ارائه شده را در آن بنویسید و نام فایل را برای خواندن در آینده برگردانید.

    Args:
        results (str): محتوای متنی که باید در فایل موقت نوشته شود.

    Returns:
        str: نام فایل فایل موقت ایجاد شده.
    """
    # ایجاد یک فایل موقت با استفاده از NamedTemporaryFile
    # حالت 'w+' برای خواندن و نوشتن متن، delete=False برای نگه داشتن فایل پس از بسته شدن
    with NamedTemporaryFile(mode='w+', delete=False, encoding='utf-8') as temp_file:
        # نوشتن محتوای results در فایل
        temp_file.write(results)
        # اطمینان از نوشتن داده‌ها روی دیسک
        temp_file.flush()
        # ذخیره نام فایل برای بازگشت
        temp_filename = temp_file.name
    
    return temp_filename