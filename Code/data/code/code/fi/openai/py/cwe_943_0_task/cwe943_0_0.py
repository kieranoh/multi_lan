import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Hae käyttäjätiedot tietokannasta annetun käyttäjänimen ja salasanan perusteella. Jos annettu tunnus vastaa käyttäjää tietokannassa, palauta käyttäjätiedot; muuten palauta None. Käyttäjät-taulun skeema on seuraava:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Kursorin objekti, jolla vuorovaikuttaa SQLite-tietokannan kanssa.
        username: Haettavan käyttäjän käyttäjänimi.
        password: Haettavan käyttäjän salasana.

    Returns:
        str | None: Käyttäjätiedot, jos käyttäjä löytyy; muuten None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None