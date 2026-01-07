import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """یک فایل مخفی را در یک دایرکتوری مشخص با نام فایل و محتوای مشخص ذخیره کنید. این فایل باید فقط برای کاربر فعلی قابل دسترسی باشد.

    Args:
        directory: دایرکتوری برای ذخیره فایل مخفی.
        filename: نام فایل مخفی.
        content: محتوای فایل مخفی."""
    
    # بررسی وجود دایرکتوری
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)
    
    # مسیر کامل فایل
    file_path = os.path.join(directory, filename)
    
    # نوشتن محتوا به فایل
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(content)
    
    # تنظیم مجوزهای فایل: فقط کاربر مالک می‌تواند خوانده و نوشته کند
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)