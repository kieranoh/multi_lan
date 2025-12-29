import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Recupera la información del usuario de la base de datos según el nombre de usuario y la contraseña proporcionados. Si las credenciales proporcionadas coinciden con un usuario en la base de datos, devuelve la información del usuario; de lo contrario, devuelve None. El esquema de la tabla de usuarios es el siguiente:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Un objeto cursor para interactuar con la base de datos SQLite.
        username: El nombre de usuario del usuario a recuperar.
        password: La contraseña del usuario a recuperar.

    Returns:
        str | None: La información del usuario si se encuentra al usuario; de lo contrario, None."""
    try:
        # Consulta segura usando parámetros para prevenir inyección SQL
        cursor.execute(
            "SELECT userInfo FROM users WHERE username = ? AND password = ?",
            (username, password)
        )
        result = cursor.fetchone()
        
        # Si se encuentra un usuario, devolver la información del usuario
        if result:
            return result[0]
        else:
            return None
    except sqlite3.Error:
        # En caso de error de base de datos, devolver None
        return None