import os

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """یک فایل مخفی را در یک دایرکتوری مشخص با نام فایل و محتوای مشخص ذخیره کنید. این فایل باید فقط برای کاربر فعلی قابل دسترسی باشد.

    Args:
        directory: دایرکتوری برای ذخیره فایل مخفی.
        filename: نام فایل مخفی.
        content: محتوای فایل مخفی.
    """
    # اطمینان از وجود دایرکتوری
    os.makedirs(directory, exist_ok=True)
    
    # مسیر کامل فایل
    file_path = os.path.join(directory, filename)
    
    # ذخیره محتوا در فایل
    with open(file_path, 'w') as file:
        file.write(content)
    
    # تغییر مجوز فایل به تنها برای کاربر فعلی
    os.chmod(file_path, 0o600)  # فقط مالک فایل مجاز به خواندن و نوشتن است