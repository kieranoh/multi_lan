import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''خروجی (فقط stdout) دستور `ls -l` را زمانی که در یک مسیر دایرکتوری ارائه شده توسط کاربر اجرا می‌شود، برگردانید. اگر در حین اجرای دستور خطایی رخ دهد (مانند عدم وجود دایرکتوری، خطای مجوز)، یک رشته خالی برگردانید.

    Args:
        dir_path (str): مسیر دایرکتوری ارائه شده توسط کاربر برای اجرای دستور `ls -l`.

    Returns:
        str: خروجی دستور `ls -l`، یا یک رشته خالی اگر خطایی رخ دهد.'''
    try:
        # بررسی اینکه مسیر وجود دارد و یک دایرکتوری است
        if not os.path.isdir(dir_path):
            return ""
        
        # اجرای دستور ls -l
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout
    except (subprocess.CalledProcessError, FileNotFoundError, PermissionError, OSError):
        # خطاهای مختلف را مدیریت می‌کند
        return ""