import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Recupere as informações do usuário do banco de dados com base no nome de usuário e na senha fornecidos. Se as credenciais fornecidas corresponderem a um usuário no banco de dados, retorne as informações do usuário; caso contrário, retorne None. O esquema da tabela de usuários é o seguinte:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Um objeto cursor para interagir com o banco de dados SQLite.
        username: O nome de usuário do usuário a ser recuperado.
        password: A senha do usuário a ser recuperado.

    Returns:
        str | None: As informações do usuário se o usuário for encontrado; caso contrário, None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    return result[0] if result else None