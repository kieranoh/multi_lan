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
    # استعلام آمن باستخدام معلمات الاستعلام لمنع هجمات حقن SQL
    query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    cursor.execute(query, (username, password))
    
    # جلب النتيجة
    result = cursor.fetchone()
    
    # إذا تم العثور على مستخدم، إرجاع معلومات المستخدم
    if result:
        return result[0]
    else:
        return None