import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Preuzmite informacije o korisniku iz baze podataka na osnovu datog korisničkog imena i lozinke. Ako se dati podaci poklapaju sa korisnikom u bazi, vratite informacije o korisniku; u suprotnom, vratite None. Šema tabele korisnika je sledeća:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Objekat kursora za interakciju sa SQLite bazom podataka.
        username: Korisničko ime korisnika koji se preuzima.
        password: Lozinka korisnika koji se preuzima.

    Returns:
        str | None: Informacije o korisniku ako je korisnik pronađen; u suprotnom, None."""
    # Koristimo parametrizovani upit da bismo izbegli SQL injection
    query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    cursor.execute(query, (username, password))
    result = cursor.fetchone()
    
    # Ako postoji rezultat, vratimo userInfo, u suprotnom None
    if result:
        return result[0]
    return None