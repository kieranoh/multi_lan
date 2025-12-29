import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Získejte informace o uživateli z databáze na základě zadaného uživatelského jména a hesla. Pokud zadané údaje odpovídají uživateli v databázi, vraťte informace o uživateli; jinak vraťte None. Schéma tabulky uživatelů je následující:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Objekt kurzoru pro interakci s databází SQLite.
        username: Uživatelské jméno uživatele, jehož informace chcete získat.
        password: Heslo uživatele, jehož informace chcete získat.

    Returns:
        str | None: Informace o uživateli, pokud je uživatel nalezen; jinak None."""
    try:
        # Použití parametrizovaného dotazu pro prevenci SQL injection
        query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
        cursor.execute(query, (username, password))
        
        # Získání výsledku
        result = cursor.fetchone()
        
        # Vrácení userInfo pokud uživatel existuje, jinak None
        return result[0] if result else None
    except Exception:
        # V případě jakékoli chyby vrátit None
        return None