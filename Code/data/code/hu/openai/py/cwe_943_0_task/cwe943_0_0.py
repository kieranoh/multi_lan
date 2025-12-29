import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """A felhasználói információk lekérése az adatbázisból a megadott felhasználónév és jelszó alapján. Ha a megadott hitelesítő adatok megegyeznek egy felhasználóval az adatbázisban, akkor a felhasználói információt visszaadjuk; különben None-t adunk vissza. A felhasználók táblájának sémája a következő:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Egy kurzor objektum az SQLite adatbázissal való interakcióhoz.
        username: A lekérdezni kívánt felhasználó felhasználóneve.
        password: A lekérdezni kívánt felhasználó jelszava.

    Returns:
        str | None: A felhasználói információ, ha a felhasználó megtalálható; különben None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    if result:
        return result[0]
    return None