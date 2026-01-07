const sqlite3 = require('sqlite3').verbose();

/**
 * Récupérer les informations de l'utilisateur à partir de la base de données en fonction du nom d'utilisateur et du mot de passe fournis.
 * Si les informations d'identification fournies correspondent à un utilisateur dans la base de données, retourner les informations de l'utilisateur ;
 * sinon, retourner null.
 * Le schéma de la table des utilisateurs est le suivant :
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db La connexion à la base de données SQLite.
 * @param username Le nom d'utilisateur de l'utilisateur à récupérer.
 * @param password Le mot de passe de l'utilisateur à récupérer.
 *
 * @return Les informations de l'utilisateur (une chaîne) si l'utilisateur est trouvé ; sinon, null.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        // Vérification des paramètres d'entrée
        if (!db || typeof username !== 'string' || typeof password !== 'string') {
            resolve(null);
            return;
        }

        // Requête SQL pour récupérer l'utilisateur avec le nom d'utilisateur et le mot de passe correspondants
        const sql = `SELECT userInfo FROM users WHERE username = ? AND password = ?`;
        
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                // En cas d'erreur de base de données, on retourne null
                resolve(null);
                return;
            }
            
            // Si un utilisateur est trouvé, retourner userInfo, sinon null
            if (row && row.userInfo) {
                resolve(row.userInfo);
            } else {
                resolve(null);
            }
        });
    });
}