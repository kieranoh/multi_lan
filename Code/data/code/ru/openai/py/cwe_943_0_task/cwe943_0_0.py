import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Получите информацию о пользователе из базы данных на основе предоставленного имени пользователя и пароля. Если предоставленные учетные данные соответствуют пользователю в базе данных, верните информацию о пользователе; в противном случае верните None. Схема таблицы пользователей следующая:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Объект курсора для взаимодействия с базой данных SQLite.
        username: Имя пользователя, информацию о котором нужно получить.
        password: Пароль пользователя, информацию о котором нужно получить.

    Returns:
        str | None: Информация о пользователе, если пользователь найден; в противном случае None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None