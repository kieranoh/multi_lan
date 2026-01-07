import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """استرجاع معلومات المستخدم من قاعدة البيانات بناءً على اسم المستخدم وكلمة المرور المقدمة. إذا تطابقت بيانات الاعتماد المقدمة مع مستخدم في قاعدة البيانات، قم بإرجاع معلومات المستخدم؛ وإلا، قم بإرجاع None. هيكل جدول المستخدمين كما يلي:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: كائن المؤشر للتفاعل مع قاعدة بيانات SQLite.
        username: اسم المستخدم للمستخدم الذي سيتم استرجاعه.
        password: كلمة المرور للمستخدم الذي سيتم استرجاعه.

    Returns:
        str | None: معلومات المستخدم إذا تم العثور على المستخدم؛ وإلا، None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    if result:
        return result[0]
    return None