import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Erabiltzailearen informazioa datu-basean berariazko erabiltzaile-izena eta pasahitza erabiliz berreskuratu. Emandako akreditazioa datu-basean erabiltzaile batekin bat badator, itzuli erabiltzailearen informazioa; bestela, itzuli None. Erabiltzaileen taularen eskema honako hau da:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: SQLite datu-basearekin elkarreragiteko kursor objektu bat.
        username: Berreskuratu beharreko erabiltzailearen erabiltzaile-izena.
        password: Berreskuratu beharreko erabiltzailearen pasahitza.

    Returns:
        str | None: Erabiltzailea aurkitzen bada, erabiltzailearen informazioa; bestela, None."""
    # Erabiltzailea eta pasahitza kontsultatu
    query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    cursor.execute(query, (username, password))
    
    # Emaitza lortu
    result = cursor.fetchone()
    
    # Emaitza itzuli
    if result:
        return result[0]
    else:
        return None