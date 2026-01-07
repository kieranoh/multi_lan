import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Hämta användarinformation från databasen baserat på det angivna användarnamnet och lösenordet. Om de angivna uppgifterna matchar en användare i databasen, returnera användarinformationen; annars, returnera None. Schemat för användartabellen är som följer:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Ett cursor-objekt för att interagera med SQLite-databasen.
        username: Användarnamnet för den användare som ska hämtas.
        password: Lösenordet för den användare som ska hämtas.

    Returns:
        str | None: Användarinformationen om användaren hittas; annars, None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None