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
    try:
        # SQL enjeksiyon saldırılarına karşı koruma için parametreli sorgu kullan
        query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
        cursor.execute(query, (username, password))
        
        # Sorgu sonucunu al
        result = cursor.fetchone()
        
        # Eğer kullanıcı bulunduysa userInfo'yu döndür, bulunamadıysa None döndür
        if result:
            return result[0]
        else:
            return None
            
    except sqlite3.Error as e:
        # Veritabanı hatası durumunda None döndür
        print(f"Veritabanı hatası: {e}")
        return None