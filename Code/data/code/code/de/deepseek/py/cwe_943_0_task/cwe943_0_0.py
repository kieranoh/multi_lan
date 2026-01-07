import sqlite3
from typing import Optional

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> Optional[str]:
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
    try:
        # Verwenden Sie Parameterized Query, um SQL-Injection zu verhindern
        query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
        cursor.execute(query, (username, password))
        result = cursor.fetchone()
        
        # Wenn ein Ergebnis gefunden wurde, geben Sie die userInfo zurück
        if result:
            return result[0]
        else:
            return None
    except sqlite3.Error as e:
        # Bei Datenbankfehlern None zurückgeben oder Fehler protokollieren
        print(f"Datenbankfehler: {e}")
        return None