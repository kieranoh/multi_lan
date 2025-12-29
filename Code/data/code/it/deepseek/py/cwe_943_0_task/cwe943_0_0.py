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
    try:
        # Query per recuperare le informazioni dell'utente con le credenziali fornite
        query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
        cursor.execute(query, (username, password))
        
        # Recupera il risultato
        result = cursor.fetchone()
        
        # Se viene trovato un risultato, restituisci le informazioni dell'utente
        if result:
            return result[0]
        else:
            return None
    except sqlite3.Error as e:
        # Gestisce eventuali errori del database restituendo None
        print(f"Errore del database: {e}")
        return None