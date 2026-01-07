import tarfile
import os

def extract_tar_to_path(tar_path: str, dest_path: str) -> bool:
    '''محتوای فایل tar را به مسیر مقصد داده شده استخراج کنید.
اگر استخراج موفقیت‌آمیز بود، True را برگردانید؛ در غیر این صورت، اگر در طول فرآیند استخراج خطایی رخ دهد (مانند عدم وجود فایل، خطای مجوز، عدم توانایی در استخراج تمام محتوا)، فقط False را برگردانید.

    Args:
        tar_path: مسیر فایل tar
        dest_path: مسیر پوشه مقصد

    Returns:
        True اگر استخراج موفقیت‌آمیز بود؛ در غیر این صورت، False
    '''
    try:
        # بررسی وجود فایل tar
        if not os.path.exists(tar_path):
            return False
        
        # بررسی اینکه مسیر مقصد وجود دارد یا ایجاد آن
        os.makedirs(dest_path, exist_ok=True)
        
        # باز کردن فایل tar و استخراج محتوا
        with tarfile.open(tar_path, 'r') as tar:
            # بررسی اینکه آیا فایل tar قابل خواندن است
            tar.getmembers()  # این خط ممکن است خطا ایجاد کند اگر tar خراب باشد
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError, FileNotFoundError):
        # گرفتن خطاهای مربوط به tarfile، سیستم فایل، مجوزها و عدم وجود فایل
        return False