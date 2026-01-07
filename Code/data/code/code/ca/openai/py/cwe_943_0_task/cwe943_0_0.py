import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Obteniu la informació de l'usuari de la base de dades en funció del nom d'usuari i la contrasenya proporcionats. Si les credencials proporcionades coincideixen amb un usuari de la base de dades, torneu la informació de l'usuari; en cas contrari, torneu None. L'esquema de la taula d'usuaris és el següent:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Un objecte cursor per interactuar amb la base de dades SQLite.
        username: El nom d'usuari de l'usuari a recuperar.
        password: La contrasenya de l'usuari a recuperar.

    Returns:
        str | None: La informació de l'usuari si es troba; en cas contrari, None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None