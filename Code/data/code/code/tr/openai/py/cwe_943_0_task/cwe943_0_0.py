import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Verilen kullanıcı adı ve şifreye göre veritabanından kullanıcı bilgilerini al. Eğer sağlanan kimlik bilgileri veritabanındaki bir kullanıcıyla eşleşiyorsa, kullanıcı bilgilerini döndür; aksi takdirde None döndür. Kullanıcılar tablosunun şeması aşağıdaki gibidir:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: SQLite veritabanıyla etkileşimde bulunmak için bir imleç nesnesi.
        username: Alınacak kullanıcının kullanıcı adı.
        password: Alınacak kullanıcının şifresi.

    Returns:
        str | None: Kullanıcı bulunduysa kullanıcı bilgisi; aksi takdirde None."""
    
    query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    cursor.execute(query, (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None