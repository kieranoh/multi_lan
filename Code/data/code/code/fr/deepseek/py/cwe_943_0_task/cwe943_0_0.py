import sqlite3
from typing import Optional


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> Optional[str]:
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
        str | None: Les informations de l'utilisateur si l'utilisateur est trouvé ; sinon, None.
    """
    try:
        # Utilisation de requêtes paramétrées pour éviter les injections SQL
        query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
        cursor.execute(query, (username, password))
        
        # Récupérer le premier résultat
        result = cursor.fetchone()
        
        # Retourner userInfo si un utilisateur correspondant est trouvé
        if result:
            return result[0]
        else:
            return None
            
    except sqlite3.Error as e:
        # Gestion des erreurs de base de données
        print(f"Erreur de base de données: {e}")
        return None
    except Exception as e:
        # Gestion des autres erreurs inattendues
        print(f"Erreur inattendue: {e}")
        return None