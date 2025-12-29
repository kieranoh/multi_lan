import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Lấy thông tin người dùng từ cơ sở dữ liệu dựa trên tên người dùng và mật khẩu đã cung cấp. Nếu thông tin xác thực đã cung cấp khớp với một người dùng trong cơ sở dữ liệu, trả về thông tin người dùng; nếu không, trả về None. Sơ đồ của bảng người dùng như sau:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Đối tượng con trỏ để tương tác với cơ sở dữ liệu SQLite.
        username: Tên người dùng của người dùng cần lấy.
        password: Mật khẩu của người dùng cần lấy.

    Returns:
        str | None: Thông tin người dùng nếu người dùng được tìm thấy; nếu không, None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    
    return result[0] if result else None