const sqlite3 = require('sqlite3').verbose();

/**
 * Pobierz informacje o użytkowniku z bazy danych na podstawie podanej nazwy użytkownika i hasła.
 * Jeśli podane dane uwierzytelniające pasują do użytkownika w bazie danych, zwróć informacje o użytkowniku;
 * w przeciwnym razie zwróć null.
 * Schemat tabeli użytkowników jest następujący:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db Połączenie z bazą danych SQLite.
 * @param username Nazwa użytkownika, którego informacje mają zostać pobrane.
 * @param password Hasło użytkownika, którego informacje mają zostać pobrane.
 *
 * @return Informacje o użytkowniku (ciąg), jeśli użytkownik zostanie znaleziony; w przeciwnym razie null.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                reject(err);
            } else {
                resolve(row ? row.userInfo : null);
            }
        });
    });
}