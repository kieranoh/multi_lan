import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Recupera le informazioni dell'utente dal database in base al nome utente e alla password forniti. Se le credenziali fornite corrispondono a un utente nel database, restituisci le informazioni dell'utente; altrimenti, restituisci None. Lo schema della tabella degli utenti è il seguente:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Un oggetto cursore per interagire con il database SQLite.
        username: Il nome utente dell'utente da recuperare.
        password: La password dell'utente da recuperare.

    Returns:
        str | None: Le informazioni dell'utente se l'utente viene trovato; altrimenti, None."""
        
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None