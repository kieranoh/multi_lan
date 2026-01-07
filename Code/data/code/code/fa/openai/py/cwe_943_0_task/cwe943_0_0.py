import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """اطلاعات کاربر را از پایگاه داده بر اساس نام کاربری و رمز عبور ارائه شده بازیابی کنید. اگر اعتبارنامه ارائه شده با یک کاربر در پایگاه داده مطابقت داشته باشد، اطلاعات کاربر را برگردانید؛ در غیر این صورت، None را برگردانید. ساختار جدول کاربران به صورت زیر است:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: یک شیء کرسر برای تعامل با پایگاه داده SQLite.
        username: نام کاربری کاربری که باید بازیابی شود.
        password: رمز عبور کاربری که باید بازیابی شود.

    Returns:
        str | None: اطلاعات کاربر اگر کاربر پیدا شود؛ در غیر این صورت، None."""
    
    # اجرای یک پرس و جو برای جستجوی کاربر با نام کاربری و رمز عبور مشخص شده
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    
    # گرفتن اولین نتیجه جستجو
    result = cursor.fetchone()
    
    # اگر نتیجه‌ای وجود داشته باشد، اطلاعات کاربر را برگردانید؛ در غیر این صورت None
    if result:
        return result[0]
    return None