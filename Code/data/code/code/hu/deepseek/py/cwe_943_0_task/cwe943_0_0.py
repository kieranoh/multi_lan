import sqlite3
from typing import Optional

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> Optional[str]:
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
    try:
        # Paraméterezett lekérdezés használata SQL injection elleni védelem érdekében
        query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
        cursor.execute(query, (username, password))
        
        # Egyetlen rekord lekérése
        result = cursor.fetchone()
        
        # Ha találat van, visszaadjuk a userInfo értékét, különben None-t
        if result:
            return result[0]
        else:
            return None
    except sqlite3.Error as e:
        # Hiba esetén None-t adunk vissza, de logolhatnánk is a hibát
        # print(f"Adatbázis hiba: {e}")
        return None