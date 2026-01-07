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
    try:
        # استفاده از پارامترهای امن برای جلوگیری از تزریق SQL
        query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
        cursor.execute(query, (username, password))
        result = cursor.fetchone()
        
        if result:
            return result[0]  # بازگرداندن ستون userInfo
        else:
            return None
    except sqlite3.Error:
        # در صورت بروز خطا در پایگاه داده، None برگردانید
        return None