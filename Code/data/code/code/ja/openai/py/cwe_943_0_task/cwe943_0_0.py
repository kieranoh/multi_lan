import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """提供されたユーザー名とパスワードに基づいてデータベースからユーザー情報を取得します。提供された資格情報がデータベース内のユーザーと一致する場合は、ユーザー情報を返します。それ以外の場合は、Noneを返します。usersテーブルのスキーマは次のとおりです：

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: SQLiteデータベースと対話するためのカーソルオブジェクト。
        username: 取得するユーザーのユーザー名。
        password: 取得するユーザーのパスワード。

    Returns:
        str | None: ユーザーが見つかった場合はユーザー情報を返し、それ以外の場合はNoneを返します。
    """
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    return result[0] if result else None