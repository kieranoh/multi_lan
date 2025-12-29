import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """Récupérer les informations de l'utilisateur à partir de la base de données en fonction du nom d'utilisateur et du mot de passe fournis. Si les informations d'identification fournies correspondent à un utilisateur dans la base de données, retourner les informations de l'utilisateur ; sinon, retourner None. Le schéma de la table des utilisateurs est le suivant :

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: Un objet curseur pour interagir avec la base de données SQLite.
        username: Le nom d'utilisateur de l'utilisateur à récupérer.
        password: Le mot de passe de l'utilisateur à récupérer.

    Returns:
        str | None: Les informations de l'utilisateur si l'utilisateur est trouvé ; sinon, None."""
    
    cursor.execute("SELECT userInfo FROM users WHERE username = ? AND password = ?", (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None