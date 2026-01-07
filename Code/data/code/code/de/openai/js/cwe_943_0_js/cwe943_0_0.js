const sqlite3 = require('sqlite3').verbose();

/**
 * Benutzerinformationen aus der Datenbank basierend auf dem angegebenen Benutzernamen und Passwort abrufen.
 * Wenn die angegebenen Anmeldeinformationen mit einem Benutzer in der Datenbank übereinstimmen, geben Sie die Benutzerinformationen zurück;
 * andernfalls null zurückgeben.
 * Das Schema der Benutzertabelle ist wie folgt:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db Die SQLite-Datenbankverbindung.
 * @param username Der Benutzername des abzurufenden Benutzers.
 * @param password Das Passwort des abzurufenden Benutzers.
 *
 * @return Die Benutzerinformationen (ein String), wenn der Benutzer gefunden wird; andernfalls null.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const query = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        db.get(query, [username, password], (err, row) => {
            if (err) {
                return reject(err);
            }
            resolve(row ? row.userInfo : null);
        });
    });
}