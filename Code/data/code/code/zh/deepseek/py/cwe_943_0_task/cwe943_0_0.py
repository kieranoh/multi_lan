import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """根据提供的用户名和密码从数据库中检索用户信息。如果提供的凭据与数据库中的用户匹配，则返回用户信息；否则，返回 None。用户表的模式如下：

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: 用于与 SQLite 数据库交互的游标对象。
        username: 要检索的用户的用户名。
        password: 要检索的用户的密码。

    Returns:
        str | None: 如果找到用户，则返回用户信息；否则，返回 None."""
    try:
        # 使用参数化查询防止SQL注入
        query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
        cursor.execute(query, (username, password))
        result = cursor.fetchone()
        
        if result:
            return result[0]  # 返回userInfo字段
        else:
            return None
    except sqlite3.Error as e:
        # 记录错误或根据需要进行处理
        print(f"数据库查询错误: {e}")
        return None