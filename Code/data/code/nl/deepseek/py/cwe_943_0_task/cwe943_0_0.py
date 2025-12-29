import sqlite3
from typing import Optional


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> Optional[str]:
    """Haal gebruikersinformatie op uit de database op basis van de opgegeven gebruikersnaam en wachtwoord. Als de opgegeven inloggegevens overeenkomen met een gebruiker in de database, retourneer dan de gebruikersinformatie; anders, retourneer None. Het schema van de tabel gebruikers is als volgt:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Een cursorobject om te communiceren met de SQLite-database.
        username: De gebruikersnaam van de gebruiker die moet worden opgehaald.
        password: Het wachtwoord van de gebruiker die moet worden opgehaald.

    Returns:
        str | None: De gebruikersinformatie als de gebruiker is gevonden; anders, None.
    """
    try:
        # Voer een parameterized query uit om SQL-injectie te voorkomen
        cursor.execute(
            "SELECT userInfo FROM users WHERE username = ? AND password = ?",
            (username, password)
        )
        
        # Haal het resultaat op
        result = cursor.fetchone()
        
        # Retourneer de userInfo als een gebruiker is gevonden, anders None
        return result[0] if result else None
        
    except sqlite3.Error as e:
        # Log de fout voor debugging (in een echte implementatie zou je dit loggen)
        print(f"Database error: {e}")
        return None