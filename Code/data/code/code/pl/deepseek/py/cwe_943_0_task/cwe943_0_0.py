import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Pobierz informacje o użytkowniku z bazy danych na podstawie podanej nazwy użytkownika i hasła. Jeśli podane dane uwierzytelniające pasują do użytkownika w bazie danych, zwróć informacje o użytkowniku; w przeciwnym razie zwróć None. Schemat tabeli użytkowników jest następujący:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Obiekt kursora do interakcji z bazą danych SQLite.
        username: Nazwa użytkownika, którego informacje mają zostać pobrane.
        password: Hasło użytkownika, którego informacje mają zostać pobrane.

    Returns:
        str | None: Informacje o użytkowniku, jeśli użytkownik zostanie znaleziony; w przeciwnym razie None."""
    query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    cursor.execute(query, (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    else:
        return None