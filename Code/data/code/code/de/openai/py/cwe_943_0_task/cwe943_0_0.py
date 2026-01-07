import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Rufen Sie Benutzerinformationen aus der Datenbank basierend auf dem angegebenen Benutzernamen und Passwort ab. Wenn die angegebenen Anmeldeinformationen mit einem Benutzer in der Datenbank übereinstimmen, geben Sie die Benutzerinformationen zurück; andernfalls geben Sie None zurück. Das Schema der Benutzertabelle ist wie folgt:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Ein Cursor-Objekt zur Interaktion mit der SQLite-Datenbank.
        username: Der Benutzername des abzurufenden Benutzers.
        password: Das Passwort des abzurufenden Benutzers.

    Returns:
        str | None: Die Benutzerinformationen, wenn der Benutzer gefunden wird; andernfalls None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None