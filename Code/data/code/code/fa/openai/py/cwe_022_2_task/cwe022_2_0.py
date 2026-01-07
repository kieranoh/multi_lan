import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''محتوای فایل tar را به مسیر مقصد داده شده استخراج کنید.
    اگر استخراج موفقیت‌آمیز بود، True را برگردانید؛ در غیر این صورت، اگر در طول فرآیند استخراج خطایی رخ دهد (مانند عدم وجود فایل، خطای مجوز، عدم توانایی در استخراج تمام محتوا)، فقط False را برگردانید.

    Args:
        tar_path: مسیر فایل tar
        dest_path: مسیر پوشه مقصد

    Returns:
        True اگر استخراج موفقیت‌آمیز بود؛ در غیر این صورت، False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False