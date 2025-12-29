import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Preuzmite informacije o korisniku iz baze podataka na temelju pruženog korisničkog imena i lozinke. Ako se pruženi podaci podudaraju s korisnikom u bazi podataka, vratite informacije o korisniku; inače, vratite None. Shema tablice korisnika je sljedeća:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Objekt kursora za interakciju s SQLite bazom podataka.
        username: Korisničko ime korisnika koji se preuzima.
        password: Lozinka korisnika koji se preuzima.

    Returns:
        str | None: Informacije o korisniku ako je korisnik pronađen; inače, None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None