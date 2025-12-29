from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """یک فایل موقت ایجاد کنید، محتوای `results` ارائه شده را در آن بنویسید و نام فایل را برای خواندن در آینده برگردانید.

    Args:
        results (str): محتوای متنی که باید در فایل موقت نوشته شود.

    Returns:
        str: نام فایل فایل موقت ایجاد شده."""
    
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        temp_file.write(results)
        return temp_file.name